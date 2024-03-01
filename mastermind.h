#ifndef GAME_H
#define GAME_H

int my_strlen(char* str);
int str_char(char* str, char letter);
void my_str_cpy(char* dest, char* source);
int my_strcmp(char* p1, char* p2);
int is_digit(char letter);
int check_for_digit(char* input);
int chech_for_dupl(char* input);
int well_placed(char* str, char* secret_code);
int mis_placed(char* input, char* secret_code);
char* my_scanf();
int* check_for_wi(char* input, char* secret_code);
char* random_code_generate();
void game_round(int index);
void game_func(char* secret_code, int attempts);

#endif 