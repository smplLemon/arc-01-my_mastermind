#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10

size_t my_strlen(char *str)
{
    size_t len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

int my_strcmp(char *str1, char *str2)
{
    size_t len1 = my_strlen(str1);
    size_t len2 = my_strlen(str2);
    if (len1 != len2)
        return 1;
    for (size_t i = 0; i < len1; i++)
    {
        if (str1[i] != str2[i])
        {
            return 1;
        }
    }
    return 0;
}

char *my_strcpy(char *dest, char *src)
{
    size_t i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    return dest;
}

int my_atoi(char *str)
{
    int res = 0, i = 0;
    while (str[i])
    {
        res *= 10;
        res += (int)str[i] - '0';
        i++;
    }
    return res;
}

int check_character(char *str, char c)
{
    size_t i = 0;
    while (str[i])
    {
        if (str[i] == c)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

char *generate_secret_code()
{
    char *secret_code = calloc(sizeof(char), CODE_LENGTH + 1);
    char c;
    srand(time(NULL));
    size_t i = 0;
    while (i < CODE_LENGTH)
    {
        c = (rand() % 9) + '0';
        if (!check_character(secret_code, c))
        {
            secret_code[i++] = c;
        }
    }
    return secret_code;
}

char *get_user_input()
{
    char *user_input = calloc(sizeof(char), CODE_LENGTH + 1);
    char c;
    size_t i = 0;
    printf(">");
    fflush(stdout);
    while (read(0, &c, 1))
    {
        if (c == '\n' || i == 5)
        {
            user_input[i] = '\0';
            return user_input;
        }
        user_input[i++] = c;
    }
    return user_input;
}

int repetition_check(char *user_input)
{
    for (size_t i = 0; i < CODE_LENGTH - 1; i++)
    {
        for (size_t j = i + 1; j < CODE_LENGTH; j++)
        {
            if (user_input[i] == user_input[j])
            {
                return 0;
            }
        }
    }
    return 1;
}

int valid_input_check(char *user_input)
{
    size_t len = my_strlen(user_input);
    if (len != CODE_LENGTH)
    {
        return 0;
    }
    for (size_t i = 0; i < CODE_LENGTH; i++)
    {
        if (user_input[i] < '0' || user_input[i] > '8')
        {
            return 0;
        }
    }
    return repetition_check(user_input);
}

int count_well_placed(char *secret_code, char *user_input)
{
    int well_placed = 0;
    for (size_t i = 0; i < CODE_LENGTH; i++)
    {
        if (secret_code[i] == user_input[i])
        {
            well_placed++;
        }
    }
    return well_placed;
}

int count_misplaced(char *secret_code, char *user_input)
{
    int misplaced = 0;
    for (size_t i = 0; i < CODE_LENGTH; i++)
    {
        if (secret_code[i] != user_input[i] && check_character(secret_code, user_input[i]))
        {
            misplaced++;
        }
    }
    return misplaced;
}

void print_placement_results(int well_placed, int misplaced)
{
    if (well_placed == CODE_LENGTH)
    {
        printf("Congratulations! You did it!\n");
        exit(0);
    }
    else
    {
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, misplaced);
    }
}

void check_placement(char *secret_code, char *user_input)
{
    int well_placed = count_well_placed(secret_code, user_input);
    int misplaced = count_misplaced(secret_code, user_input);
    print_placement_results(well_placed, misplaced);
}

void print_round_header(size_t round)
{
    printf("---\nRound %zu\n", round);
}

void play_mastermind_round(int *remaining_attempts, char *secret_code)
{
    char *user_input = get_user_input();

    while (!valid_input_check(user_input))
    {
        printf("wrong input\n");
        user_input = get_user_input();
    }

    check_placement(secret_code, user_input);
    (*remaining_attempts)--;
}

void play_mastermind(int attempts, char *secret_code)
{
    int remaining_attempts = attempts;
    size_t round = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    while (remaining_attempts > 0)
    {
        print_round_header(round++);
        play_mastermind_round(&remaining_attempts, secret_code);
    }

    printf("You didn't find the secret code. Try again!\n");
}

int main(int argc, char **argv)
{
    char *user_specified_code = NULL;
    int max_attempts = MAX_ATTEMPTS;
    for (int i = 1; i < argc; i += 2)
    {
        if (my_strcmp(argv[i], "-c") == 0)
        {
            user_specified_code = argv[i + 1];
        }
        else if (my_strcmp(argv[i], "-t") == 0)
        {
            max_attempts = my_atoi(argv[i + 1]);
        }
    }
    char *secret_code = (user_specified_code == NULL) ? generate_secret_code() : user_specified_code;
    play_mastermind(max_attempts, secret_code);
    return 0;
}
