#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

bool func_Rand_check(char* p_1, char p_2);

int func_check_continuum(char* leng) {
    int i = 0;
    while (leng[i] != '\0') {
        i++;
    }
    return i;
}

int for_game_miss_place(char* t1, char* t2) {
    int result_mp = 0;
    for (int w = 0; t1[w] != '\0'; w++) {
        if (!func_Rand_check(t1, t2[w]) && t1[w] != t2[w])
            result_mp++;
    }
    return result_mp;
}

int for_game_well_place(char* param, char* param2) {
    int result_wp = 0;
    for (int a = 0; a < func_check_continuum(param); a++) {
        if (param[a] == param2[a])
            result_wp++;
    }
    return result_wp;
}

int func_reload(char* num) {
    for (int w = 0; w < func_check_continuum(num) - 1; w++) {
        for (int h = w + 1; h < func_check_continuum(num); h++) {
            if (num[w] == num[h])
                return 1;
        }
    }
    return 0;
}

bool func_Rand_check(char* p_1, char p_2) {
    int r = 0;
    while (r < func_check_continuum(p_1)) {
        if (p_1[r] == p_2)
            return false;
        r++;
    }
    return true;
}

char* New_scanf() {
    char* scan_code = malloc(500);
    int z = 0, game_information = 0;
    char x;
    while ((game_information = read(0, &x, 1)) > 0) {
        if (x != '\n') {
            scan_code[z] = x;
            z++;
        } else {
            return scan_code;
        }
    }
    if (game_information == 0)
        exit(1);
    return scan_code;
}

int for_wronginput_function(char* my_array) {
    if (func_check_continuum(my_array) != 4)
        return 1;
    int w = 0;
    while (w < func_check_continuum(my_array)) {
        if (my_array[w] > '8'  my_array[w] < '0'  func_reload(my_array))
            return 1;
        w++;
    }
    return 0;
}

int func_for_check(char* par1, char* par2) {
    if (func_check_continuum(par1) != func_check_continuum(par2)) {
        return 0;
    }
    if (par1[1] == par2[1]) {
        return 1;
    }
    return 0;
}

void for_Rand(char* code_Skip) {
    srand(time(NULL));
    int l = 0;
    while (l < 4) {
        char randm = rand() % 8 + '0';
        if (func_Rand_check(code_Skip, randm))
            code_Skip[l++] = randm;
    }
    code_Skip[l] = '\0';
}

int func_Round_Num(int qw, char** qe) {
    int myRound_Num = 10;
    for (int i = 1; i < qw; i++) {
        if (func_for_check(qe[i], "-t") == 1) {
            i++;
            myRound_Num = atoi(qe[i]);
        }
    }
    return myRound_Num;
}
char* func_secred_code(int qw, char** qe) {
    char* secred_code = NULL;
    for (int i = 1; i < qw; i++) {
        int len = strlen(qe[i]);
        if (len == 2 && strcmp(qe[i], "-c") == 0 && i+1 < qw) {
            secred_code = qe[i+1];
            break;
        }
    }
    return secred_code;
}int main(int qw, char** qe)
{
    int myRound_Num = func_Round_Num(qw,qe);
    int game_round = 0;
    char* secred_code = func_secred_code(qw, qe); 
    char *game_input_code = (char*)malloc(19*sizeof(char));
    if (secred_code == NULL) 
    {
        secred_code = (char*)malloc(5*sizeof(char));
        for_Rand(secred_code);
    }
        printf("Will you find the secret code? \nPlease enter a valid guess");   
        while (game_round < myRound_Num)
        {
            printf("\n---\nRound %d\n", game_round); 
            write(1, ">", 1);
            game_input_code = New_scanf();
                if (for_wronginput_function(game_input_code))
                {
                    printf("\nWrong input!"); 
                    continue;
                }
            int game_well_place = for_game_well_place(secred_code, game_input_code);
            int game_miss_place = for_game_miss_place(secred_code, game_input_code);
            if (game_well_place == 4)
            { 
                printf("Congratz! You did it!"); 
                break;
            }
            else 
            {
                  printf("Well placed pieces: %d\nMisplaced pieces: %d\n", game_well_place, game_miss_place);
            } 
            game_round++;
        } 
    return 0; 
}