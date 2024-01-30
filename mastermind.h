#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10

void generateSecretCode(char *secretCode);
void printWelcomeMessage();
void printRound(int round);
void printResult(int wellPlaced, int misplaced);
int isValidInput(const char *input);
void checkGuess(const char *secretCode, const char *guess, int *wellPlaced, int *misplaced);

#endif