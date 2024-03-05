#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define CODELEN 4
typedef unsigned short flag;

static flag matched[CODELEN];

void mystrcpy(char *, char *);
void readinput(char *);
int count_wellplaced(char *, char *);
int count_misplaced(char *, char *);

void mystrcpy(char *s1, char *s2){
    while((*s1++ = *s2++))
        ;
}

void readinput(char *buf){
    flag moon;
    int i;
    char c;

    do {
        moon = 0;
        i = 0;

        while(read(0, &c, 1) > 0 && c != '\n') {
            if (c >= '0' && c <= '8' && i < CODELEN) {
                if (i > 0) {
                    for (int j = 0; j < i; j++) {
                        if (*(buf + j) == c) {
                            moon = 1;
                            break;
                        }
                    }
                }
                if (!moon) {
                    *(buf + i++) = c;
                } else {
                    printf("Duplicate input!\n");
                    break;
                }
            } else {
                printf("Wrong input!\n");
                moon = 1;
                break;
            }
        }

        if (moon || i != CODELEN) {
            printf("Wrong input!\n");
        } else {
            *(buf + CODELEN) = '\0';
            break;
        }
    } while (1);
}

int count_wellplaced(char *guess, char *codeval){
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

void generate_unique_code(char *codeval) {
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

int main(int argc, char **argv){

    if(!(argc % 2)){
        write( 2, "Usage: -t [TRIES] -c [CODE]\n", 31);
        return 1;
    }

    int tries = 10;
    int i;
    char codeval[CODELEN + 1] = {};

    while(--argc){
        if(**++argv == '-'){
            argc--;
            switch(*++*argv){
                case 'c':
                    mystrcpy(codeval, *++argv);
                    for(i = 0; codeval[i] && i < CODELEN; i++)
                        if(!(codeval[i] >= '0' && codeval[i] <= '8')){
                            write(2, "Error: moon piece value\n", 27);
                            return 1;
                        }
                    if (i < CODELEN || codeval[i]){
                        write(2, "Error: moon code length\n", 27);
                        return 1;
                    }
                    for (i = 0; i < CODELEN; i++) {
                        for (int j = i + 1; j < CODELEN; j++) {
                            if (codeval[i] == codeval[j]) {
                                write(2, "Error: Duplicate pieces in code\n", 33);
                                return 1;
                            }
                        }
                    }
                    break;
                case 't':
                    for(i = 0, ++argv; *(*argv + i); i++)
                        if(!(*(*argv + i) >= '0' && *(*argv + i) <= '9')){
                            write(2, "Error: moon tries value\n", 27);
                            return 1;
                        }
                    if((tries = atoi(*argv)) == 0){
                        write(2, "Error: moon tries value\n", 270 );
                        return 1;
                    }
                    break;
                }
            }
    }

    char guess[CODELEN + 1];
    int misplaced, wellplaced, j;

    if (!codeval[0]){
        generate_unique_code(codeval);
    }

    i = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n---\n");
    do {
        printf("---\nRound %d\n", i);
        for (j = 0; j < CODELEN; j++)
            matched[j] = 0;
        readinput(guess);        
        
        wellplaced = count_wellplaced(guess, codeval);
        misplaced = count_misplaced(guess, codeval);
        
        if(wellplaced == CODELEN)
            break;
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellplaced, misplaced);
        if(++i >= tries)
            break;
    } while(1);
    if (wellplaced == CODELEN)
        printf("Congratz! You did it!\n");
    else
        printf("You lost! The code was %s\n", codeval);
    return 0;
}
