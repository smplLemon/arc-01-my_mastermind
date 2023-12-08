#ifndef MY_MASTERMIND_H
#define MY_MASTERMIND_H

char* generate_random_code(char* random_code);
void game_status(char* guess, char* secret_code, int* well_placed, int* misplaced);
int is_correct_input(char* input);

#endif