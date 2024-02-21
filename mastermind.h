#ifndef MASTERMIND_H
#define MASTERMIND_H

void init(void);
void display(int well, int misd);
int checkGuess(char *gues, char *code, int LEN);
void play(int atm, char *code, int LEN);

#endif
