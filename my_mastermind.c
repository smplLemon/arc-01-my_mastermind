#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

bool step(int argc, char *argv[], int *code, int *round);
bool inputC(int argc, char *argv[], int *code);
bool inputT(int argc, char *argv[], int *round);
int generate(int *code);
int play(int code[], int *round);
int inputCheck(int guess);
int check(int code[], int guess);
void congrats();
int playRound(int code[], int guess);
int getGuessFromUser(int round);
int countDigits(int guess);
bool containsInvalidDigit(int guess);
bool containsRepeatedDigits(int guess);
int countWellPlacedPieces(int code[], int guess);
int countMisplacedPieces(int code[], int guess );

int main(int argc, char *argv[])
{
    int code[4];
    int round = 10;
    if (!step(argc, argv, code, &round))
        return 1;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    return play(code, &round);
}

bool step(int argc, char *argv[], int *code, int *round) {
    bool codeProvided = false;
    bool roundProvided = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            char *codeStr = argv[i + 1];
            for (int j = 0; j < 4; j++) {
                code[j] = codeStr[j] - '0';}
            codeProvided = true;
            i++;
            } else if (strcmp(argv[i], "-t") == 0) {
            *round = (i + 1 < argc) ? atoi(argv[i + 1]) : 10;
            roundProvided = true;
            if (i + 1 < argc)
                i++;}
    }if (!codeProvided) {
        generate(code);
    }if (!roundProvided) {
        *round = 10;}
    return true;
}

bool inputT(int argc, char *argv[], int *round)
{
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-t") == 0){
            *round = (i + 1 < argc) ? atoi(argv[i + 1]) : 10;
            return true;
        }
    return false;
}

bool inputC(int argc, char *argv[], int *code)
{
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc){
            char *codeStr = argv[i + 1];
            for (int j = 0; j < 4; j++){
                code[j] = codeStr[j] - '0';
            }
            return true;
        }
    return false;
}

int generate(int *code)
{
    srand(time(NULL));
    bool unique = false;
    while (!unique){
        unique = true;
        for (int i = 0; i < 4; i++)
            code[i] = rand() % 8;
        for (int i = 0; i < 4; i++)
            for (int j = i + 1; j < 4; j++)
                if (code[i] == code[j]){
                    unique = false;
                    break;
                }
    }
    return 0;
}

int play(int code[], int *roundI) {
    int round = 0;
    while (round < *roundI && round < 10) {
        int guess = getGuessFromUser(round);
        if (guess == EOF) {
            return 0; 
        } else if (guess == -1) { continue;} else {
            int result = playRound(code, guess);
            if (result == 1) {
                congrats();
                return 1; 
            } else if (result == 0) {
                round++;
            } else if (result == -1) {
                continue;}
        }
    }if (round == *roundI) {
        printf("You didn't find the code!\n");
    }
    return 0; 
}


int countDigits(int guess)
{
    int numDigits = 0;
    int temp = guess;
    while (temp != 0){
        temp /= 10;
        numDigits++;
    }
    return numDigits;
}

bool containsInvalidDigit(int guess)
{
    int temp = guess;
    while (temp != 0){
        int digit = temp % 10;
        if (digit < 0 || digit > 8)
            return true;
        temp /= 10;
    }
    return false;
}

bool containsRepeatedDigits(int guess)
{
    int digits[10] = {0};
    while (guess != 0){
        int digit = guess % 10;
        if (digits[digit] == 1)
            return true;
        digits[digit] = 1;
        guess /= 10;
    }
    return false;
}

int inputCheck(int guess)
{
    int numDigits = countDigits(guess);
    if (numDigits != 4 || containsInvalidDigit(guess)){
        printf("Wrong input!\n");
        return -1;
    }
    if (containsRepeatedDigits(guess)){
        printf("Wrong input!\n");
        return -1;
    }
    return 0;
}

int check(int code[], int guess)
{
    int mp = countWellPlacedPieces(code, guess);
    int wp = countMisplacedPieces(code, guess);

    if (mp == 4)
        return 1;

    printf("Well placed pieces: %d\n", mp);
    printf("Misplaced pieces: %d\n", wp);
    return 0;
}

int countWellPlacedPieces(int code[], int guess)
{
    int mp = 0;
    int guess_digits[4];
    guess_digits[0] = guess / 1000;
    guess_digits[1] = (guess / 100) % 10;
    guess_digits[2] = (guess / 10) % 10;
    guess_digits[3] = guess % 10;

    for (int i = 0; i < 4; i++){
        if (code[i] == guess_digits[i])
            mp++;
    }
    return mp;
}

int countMisplacedPieces(int code[], int guess)
{
    int wp = 0;
    int guess_digits[4];
    guess_digits[0] = guess / 1000;
    guess_digits[1] = (guess / 100) % 10;
    guess_digits[2] = (guess / 10) % 10;
    guess_digits[3] = guess % 10;
    for (int i = 0; i < 4; i++){
        if (code[i] != guess_digits[i]){
            for (int j = 0; j < 4; j++){
                if (j != i && code[j] == guess_digits[i]){
                    wp++;
                    break;
                }
            }
        }
    }
    return wp;
}

int playRound(int code[], int guess)
{
    if (inputCheck(guess) == -1)
        return -1;
    else if (check(code, guess) == 1)
        return 1;
    else
        return 0;
}

void congrats()
{
    printf("Congratz! You did it!\n");
}

int getGuessFromUser(int round)
{
    char buffer[6];
    printf("---\nRound %d \n>", round);
    ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
    if (bytes_read == -1){
        perror("Error reading input");
        exit(EXIT_FAILURE);
    }else if (bytes_read == 0){
        return EOF;
    }else if (bytes_read == 1 && buffer[0] == '\n'){
        printf("Invalid input. Please enter a valid number.\n");
        return -1;
    }else{
        buffer[bytes_read - 1] = '\0';
        return atoi(buffer);
    }
}


