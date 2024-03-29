#ifndef MYSTERIOUS_H
#define MYSTERIOUS_H 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#define Len 4
void decrpt(char decryption[]);

int preStrlen(char *string);
int preGtr(char *string);
void strCpy(char *destination, char *source);
void generateCod(char hidden_code[], char *encoded);
void getDescryption(char decryption[]);
void compareCod(char hidden_code[], char decryption[], int *accuratelyPlaced, int *inaccuratelyPlaced);

int preGtr(char *string){
    int index = 0;
    char letter;
    write(1, ">", 1);
    while(read(STDIN_FILENO, &letter, 1) > 0){
        if(letter == '\n' || index == Len + 1){
            string[index] = '\0';
            return 1;
        } string[index++] = letter; }
    if(index == 0){
        exit(0); }
    return 0; }

void strCpy(char *destination, char *source){
    while(*source != '\0'){
        *destination = *source;
        destination++;
        source++; }
    *destination = '\0'; }

int preStrlen(char *string){
    int length = 0;
    while(string[length] != '\0'){
        length++; } return length; }

void generateCod(char hidden_code[], char *encoded){
    if(encoded != NULL && preStrlen(encoded) == Len){
        strCpy(hidden_code, encoded); } 
        else{
        int used_digits[9] ={0}; 
        srand(time(NULL));
        for(int i = 0; i < Len; i++){
            int digit;
            digit = rand() % 9;
            while(used_digits[digit]){
                digit = rand() % 9; }
            used_digits[digit] = 1;
            hidden_code[i] = digit + '0'; } } }

void decrpt(char decryption[]){
    int visited[10] = {0}; 
    int invalid_guess = 0; 
    
    if(preStrlen(decryption) != Len){
        invalid_guess = 1;
    }

    for(int i = 0; i < Len; i++){
        if(decryption[i] == '9' || decryption[i] < '0' || decryption[i] > '8'){
            invalid_guess = 1;
            break; }

        if(visited[decryption[i] - '0']){
            invalid_guess = 1;
            break; }
        visited[decryption[i] - '0'] = 1; }

    if(invalid_guess){
        printf("Wrong input\n");
        preGtr(decryption); 
        decrpt(decryption); } }

void compareCod(char hidden_code[], char decryption[], int *accuratelyPlaced, int *inaccuratelyPlaced){
    *accuratelyPlaced = 0;
    *inaccuratelyPlaced = 0;

    for(int i = 0; i < Len; i++){
        if(decryption[i] == hidden_code[i]){
          (*accuratelyPlaced)++; }
          else{
            for(int j = 0; j < Len; j++){
                if(i != j && decryption[i] == hidden_code[j]){
                  (*inaccuratelyPlaced)++;
                    break; } } } } } 

void getDescryption(char decryption[]){
    preGtr(decryption);
    decrpt(decryption); }
#endif