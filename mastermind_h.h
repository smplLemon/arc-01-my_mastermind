#ifndef MASTERMIND_H
#define MASTERMIND_H

void guess(char* gues, char* scrt_cd, int* well_plcd, int* misplcd);
char* randit(char* random_code);
int validation(char* input);
int rd_input(char* user_guess);
int is_correct(int well_placed);
void prnt_res(int well_placed, int misplaced);
#endif
