#ifndef MY_MASTERMIND_H
#define MY_MASTERMIND_H

#include <stdbool.h>

int read_input(char *buffer);
int check_guess(const char *guess, const char *secret_code);

#endif
