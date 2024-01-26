#ifndef MASTERMIND_H
#define MASTERMIND_H

void init(char *kod);
void display(int well, int misd);
int checkgess(char *gess, char *kod);
void play(int atm);

#endif
