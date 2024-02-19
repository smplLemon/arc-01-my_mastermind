#ifndef my_mastermind_functions_H  // Include guards to prevent multiple inclusion
#define my_mastermind_functions_H

// Include necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "../include/my_ngram_functions.h"

// define constants
#define SECRET_CODE_LENGTH 4
#define MAX_ATTEMPTS 10
#define VALID_NUMBERS 8

// Define structs
typedef struct{
    char flag_secret_code_representation;
    bool flag_secret_code_on;
    int flag_secret_code_position;
    char flag_attempts_representation;
    bool flag_attempts_on;
    int flag_attempts_position;
}flag_struct;

// Function declaration
void create_random_secret_code(char *secret_code_array);
void check_for_flags(int argc, char *argv[], flag_struct *flags);
flag_struct init_flag_struct();
bool is_user_secret_code_valid(char *user_secret_code);
bool is_user_attempt_count_valid(char *user_attempt_count);
bool is_user_guess_correct(char *user_guess, char *secret_code_array);
void evaluate_user_guess(char *user_guess, char *secret_code_array);
bool read_user_input(char *user_guess, int user_guess_length);
bool is_user_guess_valid(char *user_guess);



bool is_str_a_number(char *str);
bool is_char_a_number(char character);

// Variable declaration
// char* boolean[2] = {"false", "true"};


#endif  // End of include guards