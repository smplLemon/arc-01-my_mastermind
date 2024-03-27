#ifndef MYSTERIOUS_H
#define MYSTERIOUS_H 

#define Len 4
void decrpt(char decryption[]);

int preStrlen(char *string);
int preGtr(char *string);
void strCpy(char *destination, char *source);

void generateCod(char hidden_code[], char *encoded);
void getDescryption(char decryption[]);
void compareCod(char hidden_code[], char decryption[], int *accuratelyPlaced, int *inaccuratelyPlaced);

#endif