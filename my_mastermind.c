#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define CD_LEN 4

int MX_ATMT = 10;

char* initialize_game(int ac, char** av, int* MX_ATMT);
int play_game(char* scrt_cd, int MX_ATMT);
void play_game_loop(char* scrt_cd, int MX_ATMT);
void guess(char* gues, char* scrt_cd, int* well_plcd, int* misplcd);
char* randit(char* rndm_cd);
int validation(char* inpt);
int rd_input(char* user_guess);
int is_correct(int wlplcd);
void prnt_res(int wlplcd, int misd);
unsigned int my_strlen(const char* str);
char* my_strcpy(char* dest, const char* src);

// strlen funksiyasi
unsigned int my_strlen(const char* str) {
    unsigned int len = 0;
    while(str[len] != '\0') {
        len++;
    }
    return len;
}

// strcpy funksiyasi 
char* my_strcpy(char* dest, const char* src) {
    char* start = dest;
    while((*dest++ = *src++) != '\0');
    return start;
}

void print_wrong(){
    printf("Wrong input!\n");
}

// logikasi 
int play_game(char* scrt_cd, int MX_ATMT) {
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    if (my_strlen(scrt_cd) != CD_LEN) {
        srand(time(NULL));
        randit(scrt_cd);
    }
    play_game_loop(scrt_cd, MX_ATMT);
    return EXIT_FAILURE;
}

int get_round_input(char* guess) {
    printf(">");
    fflush(stdout);
    return rd_input(guess);
}

void handle_round_result(int wel_plcd, int misplcd) {
    if (is_correct(wel_plcd)) {
        printf("Congratz! You did it!\n");
    } else {
        prnt_res(wel_plcd, misplcd);
    }
}

void play_round(char* scrt_cd, int* wel_plcd, int* misplcd, int* round, int* input_terminated) {
    char user_guess[CD_LEN + 1];
    int input_result = get_round_input(user_guess);
    if (input_result == -1) {
        *input_terminated = 1;
        return;
    } else if (input_result != 0) {
        print_wrong();
        return;
    }
    user_guess[CD_LEN] = '\0';
    if (!validation(user_guess)) {
        return;
    }
    guess(user_guess, scrt_cd, wel_plcd, misplcd);
    handle_round_result(*wel_plcd, *misplcd);
    (*round)++;
}

void play_game_loop(char* scrt_cd, int MX_ATMT) {
    int wel_plcd = 0, misplcd = 0, round = 0, input_terminated = 0;
    while (round < MX_ATMT && !input_terminated) {
        printf("---\nRound %d\n", round);
        play_round(scrt_cd, &wel_plcd, &misplcd, &round, &input_terminated);
        if (is_correct(wel_plcd) || input_terminated) {
            break;
        }
    }
    if (!input_terminated && round == MX_ATMT) {
        printf("Sorry, you couldn't find the secret code.\n");
    }
}

//errorlari
int rd_input(char* guess) {
    int chars_read = 0, count;
    char result;
    while ((count = read(STDIN_FILENO, &result, 1)) != -1) {
        if (count == 0) {
            return -1;
        }
        if (result == '\n') {
            guess[chars_read] = '\0';
            return 0; 
        } else if (chars_read >= CD_LEN || result < '0' || result > '9') {
            while (read(STDIN_FILENO, &result, 1) && result != '\n');
            return 1; 
        }
        guess[chars_read++] = result;
    }
    return 1; 
}

int is_correct(int wlplcd) {
    return (wlplcd == CD_LEN);
}

void prnt_res(int wlplcd, int misd) {
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wlplcd, misd);
}

// funksiyalari
void guess(char* gues, char* scrt_cd, int* well_plcd, int* misplcd) {
    *well_plcd = 0;
    *misplcd = 0;
    int gues_hist[10] = {0};
    int secret_hist[10] = {0};

    for (int i = 0; i < CD_LEN; i++) {
        if (gues[i] == scrt_cd[i]) {
            (*well_plcd)++;
        } else {
            gues_hist[gues[i] - '0']++;
            secret_hist[scrt_cd[i] - '0']++;
        }
    }
    for (int i = 0; i < 10; i++) {
        *misplcd += gues_hist[i] < secret_hist[i] ? gues_hist[i] : secret_hist[i];
    }
}

char* randit(char* rndm_cd) {
    const char num[] = "012345678";
    for (int i = 0; i < CD_LEN; i++) {
        rndm_cd[i] = num[rand() % 10];
    }
    rndm_cd[CD_LEN] = '\0';
    return rndm_cd;
}

int validation(char* inpt) {
    if (my_strlen(inpt) != CD_LEN) {
        print_wrong();
        return 0;
    }
    int dig[10] = {0};

    for (int i = 0; i < CD_LEN; i++) {
        if (inpt[i] < '0' || inpt[i] > '9' || inpt[i] == '9') {
            print_wrong();
            return 0;
        }
        dig[inpt[i] - '0']++;

        if (dig[inpt[i] - '0'] > 1) {
            print_wrong();
            return 0;
        }
    }
    return 1;
}

// -c va -t larni ishga tushirilishi
char* initialize_game(int ac, char** av, int* MX_ATMT) {
    char* scrt_cd = calloc(sizeof(char), CD_LEN + 1);
    if (scrt_cd == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 1; i < ac; i++) {
        if (strcmp(av[i], "-c") == 0 && i + 1 < ac) {
            my_strcpy(scrt_cd, av[i + 1]);
            scrt_cd[CD_LEN] = '\0';
        } else if (strcmp(av[i], "-t") == 0 && i + 1 < ac) {
            *MX_ATMT = atoi(av[i + 1]);
        }
    }
    return scrt_cd;
}

int main(int ac, char** av) {
    char* scrt_cd = initialize_game(ac, av, &MX_ATMT);
    if (scrt_cd == NULL) {
        return EXIT_FAILURE;
    }
    int result = play_game(scrt_cd, MX_ATMT);

    free(scrt_cd);
    return result;
}
