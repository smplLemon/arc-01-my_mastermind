//Men bu kodni yordam sorab yozdim
//Sal qiyin bolgani uchun
//Lekin hamma narsasiga tushundim
//Etiboringiz uchun rahmat
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CODE_LENGTH 4
#define MAX_GUESSES 10
#define NUM_PIECES 9

// Ko'dni tasodifiy generatsiya qilish
void generateCode(int code[]) {
    srand(time(NULL));
    for (int i = 0; i < CODE_LENGTH; i++) {
        code[i] = rand() % NUM_PIECES;
    }
}

// O'yinchiga kiritilgan ko'prikodni tekshirish
void checkGuess(int code[], int guess[], int result[]) {
    int codePieces[NUM_PIECES] = {0};
    int guessPieces[NUM_PIECES] = {0};
    
    int wellPlaced = 0;
    int misplaced = 0;
    
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (code[i] == guess[i]) {
            wellPlaced++;
        } else {
            codePieces[code[i]]++;
            guessPieces[guess[i]]++;
        }
    }
    
    for (int i = 0; i < NUM_PIECES; i++) {
        misplaced += (codePieces[i] < guessPieces[i]) ? codePieces[i] : guessPieces[i];
    }
    
    result[0] = wellPlaced; // yaxshi joylashtirilgan qismlar soni
    result[1] = misplaced; // noto'g'ri joylashtirilgan qismlar soni
}

int main(int argc, char *argv[]) {
    // Maxfiy kodni belgilash uchun parametrni qabul qilish
    int code[CODE_LENGTH] = {0};
    if (argc > 1 && strlen(argv[1]) == CODE_LENGTH) 
    {
        for (int i = 0; i < CODE_LENGTH; i++) {

            code[i] = atoi(argv[1] + i);
        }
    } else {
        generateCode(code);
    }
    

    int guesses = 0;
    
    int allGuesses[MAX_GUESSES][CODE_LENGTH] = {{0}};

    
    // O'yinchi kiritishni kuzatib borish
    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");
    
    while (guesses < MAX_GUESSES) {
        // Urinishni qabul qilish
        char input[10];
        printf("---\nRound %d\n>", guesses);
        fgets(input, sizeof(input), stdin);
        
        // Kiritilgan urinishni tekshirish va natijani chiqarish
        int guess[CODE_LENGTH] = {0};
        if (strlen(input) == CODE_LENGTH + 1) {
            for (int i = 0; i < CODE_LENGTH; i++) {
                guess[i] = input[i] - '0';
            }
            
            int result[2] = {0};
            checkGuess(code, guess, result);
            
            printf("Well placed pieces: %d\n", result[0]);
            printf("Misplaced pieces: %d\n", result[1]);
            
            // Agar kod topilsa
            if (result[0] == CODE_LENGTH) {
                printf("Congratz! You did it!\n");
                break;
            }
        } else {

            
            printf("Wrong input!\n");
        }


        
        guesses++;
    }
    


    return 0;
}
