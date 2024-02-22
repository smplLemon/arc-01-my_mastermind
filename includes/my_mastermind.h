#ifndef MY_MASTERMIND_H
# define MY_MASTERMIND_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define ONGOING 0
#define LOSE -1
#define WIN 1

/*
** My_Mastermind core control
*/
int main(int argc, char **argv);
void play_mastermind(int attempts, char *code);

/*
** Functions to handle options
*/
char check_option(char *str);
int set_option_c(char **code, char *str);
int set_option_t(int *attempts, char *str);
int handle_option(char option, int *attempts, char **code, char *str);
int handle_flags(int *attempts, char **code, char **argv);

/*
** Functions to handle game logic
*/
char *random_code();
char *get_input();
int check_code(char *code);
char *get_valid_input();
void end_game_message(int game_status);
int well_placed(char *input, char *code);
int misplaced(char *input, char *code, int well);
void print_well_mis(int well, int mis);
int mastermind_logic(char *player_input, char *code);

/*
** Misc. useful functions
*/
int my_strlen(char *str);
int check_nbr(char *str);
char *my_strdup(char *str);
void str_fill(char *str, char fill, int len);
int my_strcmp(char *str1, char *str2);

#endif