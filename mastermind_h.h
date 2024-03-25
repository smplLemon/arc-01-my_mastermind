#ifndef MASTERMIND_H
#define MASTERMIND_H

char* initialize_game(int ac, char** av, int* MX_ATMT);
int play_game(char* scrt_cd, int MX_ATMT);
void guess(char* gues, char* scrt_cd, int* well_plcd, int* misplcd);
char* randit(char* rndm_cd);
int validation(char* inpt);
int rd_input(char* user_guess);
int is_correct(int wlpcd);
void prnt_res(int wlpcd, int misd);
#endif