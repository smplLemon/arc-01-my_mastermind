
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define kodning_uzunligi 4
void tekshirish_funksiyasi(char* taxmin, char* maxviy_kod, int* tugri, int* no_tugri)
{
    int i = 0; *tugri=0,*no_tugri=0;   
    int taxmin_taxmin[10] = {0};
    int c1[10] = {0};
    for (int i = 0; i < kodning_uzunligi; i++){
        if (taxmin[i] == maxviy_kod[i]){
            (*tugri)++;
        } else {
            taxmin_taxmin[taxmin[i] - '0']++;
            c1[maxviy_kod[i] - '0']++;
        }
    }
    while(i<10){
        if (c1[i] < taxmin_taxmin[i]){
            *no_tugri += c1[i];
        } else {
            *no_tugri += taxmin_taxmin[i];
        }
        i++;
    }
}

char* Randomiser(char* random_kod)
{
    const char raqamlar[] = "0123456789";
    int a1 = 0;
    while(a1<kodning_uzunligi){
        random_kod[a1] = raqamlar[rand() % 10];
        a1++;
    }
    random_kod[kodning_uzunligi] = '\0';
    return random_kod;
}

int kiritilgan_kodni_tekshirish_funksiyasi(char* kiritilgan_raqam)
{
    int i = 0;
    if (strlen(kiritilgan_raqam) != kodning_uzunligi){
        return 0;
    }
    
    while(i<kodning_uzunligi){
        if (kiritilgan_raqam[i] < '0' || kiritilgan_raqam[i] > '9'){
            return 0;
        }
        i++;
    }
    return 1;
}

int main(int argc, char** argv)
{
    char* maxviy_kod = calloc(sizeof(char), kodning_uzunligi + 1);
    int maksimal_urinishlar = 10;
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc){
            strncpy(maxviy_kod, argv[i + 1], kodning_uzunligi);
            maxviy_kod[kodning_uzunligi] = '\0';
        }else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc){
            maksimal_urinishlar = atoi(argv[i + 1]);
        }
    }
    if (strlen(maxviy_kod) == 0){
        srand(time(NULL));
        Randomiser(maxviy_kod);
    }
    char foydalanuvchi_taxmini[kodning_uzunligi + 1];
    int tugri, no_tugri;
    int rounds = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while (rounds < maksimal_urinishlar){
        printf("---\nRound %d\n>", rounds);
        if (read(0, foydalanuvchi_taxmini, kodning_uzunligi + 1) == -1){
            printf("Error reading input.\n");
            return 1;
        }
        foydalanuvchi_taxmini[kodning_uzunligi] = '\0';
        if (!kiritilgan_kodni_tekshirish_funksiyasi(foydalanuvchi_taxmini)){
            printf("Wrong input!\n");
            continue;
        }
        tekshirish_funksiyasi(foydalanuvchi_taxmini, maxviy_kod, &tugri, &no_tugri);
        if (tugri == kodning_uzunligi){
            printf("Congratz! You did it!\n");
            return 0;
        }
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", tugri, no_tugri);
        rounds++;
    }
    printf("---\nGame over. You didn't find the secret code.\n");
    return 0;
}