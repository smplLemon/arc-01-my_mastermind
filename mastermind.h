#ifndef MASTERMIND_H
#define MASTERMIND_H

void init(void);
void display(int well, int misd);
int checkGuess(char *guess, char *code); 
void play(int atm);

#endif
