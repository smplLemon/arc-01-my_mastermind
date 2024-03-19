#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define CODELEN 4
typedef unsigned short flag;

static flag matched[CODELEN];
static flag eof_encountered = 0;

void mystrcpy(char *, char *);
void readinput(char *);
int count_wellplaced(char *, char *);
int count_misplaced(char *, char *);
int check_code(char *);

void mystrcpy(char *s1, char *s2){
    while((*s1++ = *s2++));
}

void reader(char *buf, flag *moon, int *i, ssize_t *bytes_read, char *c) {
    while (((*bytes_read = read(0, c, 1)) > 0) && (*c != '\n')) {
        if (*c >= '0' && *c <= '8' && *i < CODELEN) {
            if (*i > 0) {
                for (int j = 0; j < *i; j++) {
                    if (*(buf + j) == *c) {
                        *moon = 1;
                        break;
                    }
                }
            }
            if (!(*moon)) 
                *(buf + (*i)++) = *c;
            else 
                break;
        } else {
            *moon = 1;
            break;
        }
    }
}

void readinput(char *buf) {
    flag moon;
    int i;
    char c;
    ssize_t bytes_read;
    do {
        moon = 0, i = 0;
        reader(buf, &moon, &i, &bytes_read, &c);
        if (moon || i != CODELEN) {
            if (bytes_read == 0) {
                eof_encountered = 1;
                break;
            }
            printf("Wrong input!\n");
        } else {
            *(buf + CODELEN) = '\0';
            break;
        }
        while (read(0, &c, 1) > 0 && c != '\n') {}
    } while (1);
}

void generate_unique_code(char *codeval) { //10
    int i, j;
    char digits[] = "012345678";
    srand((unsigned)time(NULL));
    for (i = 0; i < CODELEN; i++) {
        j = rand() % (9 - i);
        codeval[i] = digits[j];
        digits[j] = digits[8 - i];
    }
    codeval[CODELEN] = '\0';
}

int count_wellplaced(char *guess, char *codeval){ //9
    int wellplaced, i;
    for(wellplaced = 0, i = 0; i < CODELEN; i++, guess++, codeval++)
        if(*guess == *codeval){
            matched[i] = 1;
            *guess = -1;
            wellplaced++;
        }
    return wellplaced;
}

int count_misplaced(char *guess, char *codeval){
    int misplaced, i;
    for(misplaced = 0; *guess != '\0'; guess++)
        for(i = 0; i < CODELEN; i++)
            if(!matched[i] && *(codeval + i) == *guess){
                matched[i] = 1;
                misplaced++;
                break;
            }
    return misplaced;
}

int second_main(char* codeval, int tries){
    char guess[CODELEN + 1];
    int misplaced, wellplaced;
    if (!codeval[0]) generate_unique_code(codeval);
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for (int i = 1; i <= tries; ++i){
        if (eof_encountered) break;
        printf("---\nRound %d\n", i);
        for (int j = 0; j < CODELEN; j++) matched[j] = 0;
        readinput(guess);
        wellplaced = count_wellplaced(guess, codeval);
        misplaced = count_misplaced(guess, codeval);
        if(wellplaced == CODELEN)break;
        if (!eof_encountered) printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellplaced, misplaced);
    }
    if (wellplaced == CODELEN) printf("Congratz! You did it!\n");
    return 0;
}

int check_code(char* codeval) {
    int i, j;
    for(i = 0; codeval[i] && i < CODELEN; i++)
        if(!(codeval[i] >= '0' && codeval[i] <= '8')) return 1;
    if (i < CODELEN || codeval[i]) return 1;
    for (i = 0; i < CODELEN; i++) {
        for (j = i + 1; j < CODELEN; j++) {
            if (codeval[i] == codeval[j]) return 1;
        }
    }
    return 0;
}

int check_users_input(int argc, char** argv, char* codeval, int* tries) {
    while(argc > 1) {
        if(**argv == '-'){
            switch(*++*argv){
                case 'c':
                    mystrcpy(codeval, *++argv);
                    if (check_code(codeval)) return 1;
                    argc--;
                    break;
                case 't':
                    *tries = atoi(*++argv);
                    argc--;
                    break;
            }
        }
        argv++, argc--;
    }
    return 0;
}

int main(int argc, char **argv){
    if(!(argc % 2)) return 1;
    int tries = 10;
    char codeval[CODELEN + 1] = {};
    int result = check_users_input(argc, argv, codeval, &tries);
    if (result == 1) return 1;
    second_main(codeval, tries);
    return 0;
}