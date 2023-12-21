#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generateRandomCode(char *code);
int readInput(char guess[4 + 1]);
int countWellPlaced(char *code, char *guess);
int countMisplaced(char *code, char *guess);

#endif
