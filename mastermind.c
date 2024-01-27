#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

int my_atoi(char *str)
{
    int res = 0, sign = 1;
    if (str[0] == '-'){
        sign = -1;
    }
    for (int i = 0; str[i] != '\0'; i++){
        if ((str[i] > 47) && (str[i] < 58)) {
            res = res * 10 + str[i] - '0';
        }                  
    }                 
    return res * sign;
}

// this is need we for check about user's key "is it wrong answer"
bool checker_char(char a[])
{
    bool ans = false;
    int sum = 0;
    if (strlen(a) == 4)
    {
        for (int i = 0; i < 4; i++)
        {
            if ((a[i] > 47) && (a[i] < 57))
            {
                sum++;
            }
        }
        if ((sum == 4) && (a[0] != a[1]) && (a[0] != a[2]) && (a[0] != a[3]) && (a[1] != a[2]) && (a[1] != a[3]) && (a[2] != a[3]))
        {
            ans = true;
        }
    }
    return ans;
}

// this function helps us  to take random numbers
char *my_random()
{
    char *answer = (char *)malloc(4 * sizeof(char));
    srand(time(NULL));
    int n;
start:
    for (int n = 0; n < 4; n++)
        answer[n] = (int)(rand() % 9) + 48;

    for (n = 0; n < 4; n++)
    {
        for (int z = n + 1; z < 4; z++){
            if (answer[n] == answer[z])
                goto start;
        }
    }

    return answer;
}

// this is checker of wellplace
int wellplace(char *a, char *b)
{
    int t = 0;
    for (int i = 0; i < 4; i++)
    {
        if (a[i] == b[i])
        {
            t++;
        }
    }
    return t;
}

// this is checker of missplace function
int missplace(char *a, char *b)
{
    int ans;
    int asci[127] = {0};
    int sum = 0;
    for (int i = 0; i < 4; i++)
    {
        asci[a[i]] = 1;
        asci[b[i]] = 1;
        if (a[i] == b[i])
            sum += 1;
    }
    for (int i = 48; i < 57; i++)
        sum += asci[i];
    ans = 8 - sum;
    return ans;
}

int my_strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str1 == *str2)
    {
        str1++;
        str2++;
    }
    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}
int my_Round(int argc, char *argv[])
{
    int round = 10;
    for (int i = 0; i < argc; i++)
    {
        if (my_strcmp(argv[i], "-t") == 0)
        {
            round = my_atoi(argv[i + 1]);
            i = argc;
        }
    }
    return round;
}

char *my_Key(int argc, char *argv[])
{
    char *key;
    int flag = 0;
    for (int i = 0; i < argc; i++)
    {
        if (my_strcmp(argv[i], "-c") == 0)
        {
            key = argv[i + 1];
            i = argc;
            flag = 1;
        }
    }
    if (flag == 0)
    {
        key = my_random();
    }
    return key;
}

void play(int w, int m, int maxRound, int *nowRound, char *secretKey, char *userKey)
{
    if ((*nowRound < maxRound) && (w != 4) && (checker_char(userKey)))
    {                   
        printf("Well placed pieces: %i\nMiss placed pieces: %i\n", w, m);
    }                                                    
    if (!(checker_char(userKey)))
    {
        printf("Wrong input\n");
        *nowRound -= 1;
    }
    if (w == 4)
    {
        printf("Congratz! You did it!");
        *nowRound = maxRound;
    }
}

char *my_scanf(int round)
{
    int i = 0;
    char c;
    char *codem = malloc(sizeof(char) * 6);
    printf("---\nRound %i\n", round);
    write(1, ">", 1);
    while (read(0, &c, 1))
    {
        if (i == 0 && c == '\n'){
            write(1, ">", 1);
            continue;
        }
        else if (c == '\n'){
            return codem;
        }
        else{
            codem[i++] = c;
        }
    }
    return "EOT";
}


int main(int argc, char *argv[])
{
    char *key = my_Key(argc, argv),*userKey; 
    int round = my_Round(argc, argv);
    printf("Will you find the secret code?  \nPlease enter a valid guess\n");

    for (int i = 0; i < round; i++)
    {
        userKey = my_scanf(i);
        if (my_strcmp(userKey, "EOT") == 0){
            break;
        }
        play(wellplace(userKey, key), missplace(userKey, key), round, &i, key, userKey);
    }
    return 0;
}