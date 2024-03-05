# My Mastermind
This code is an implementation of the digital version of the famous board game from back in 1970, called *Mastermind*.

The code was written by [Abdussamad Turdixojayev](https://github.com/Abuuu2007).

## Content
- [Description](#description)
- [Usage](#usage)
- [Code Component](#code-component)
- [Main function](#main-function)

## Description
I was given the task of creating a Mastermind that has two parameters:
1. `-c` - setting the secret code. If the secret code is not registered, it will be generated randomly.
2. `-t` - indicating the number of attempts/rounds. If the number of attempts is not specified, then the number is 10.

Instead of 9 different colors, numbers from 0 to 8 inclusive are used.

But with all this, I am allowed to use a limited number of functions, namely:

* printf(3)
* write(2)
* read(2)
* rand() (/ srand())
* time()
* atoi()
* strcmp()

## Usage
### Start the game
In order to start the game, you need to enter into the console:
```
$ ./my_mastermind
```
### Secret code
In order to start the game by setting a secret code, you need to specify the appropriate parameters, for example:
```
$ ./my_mastermind -t 5
```
### Attempts
In order to start the game by specifying the number of attempts, you need to specify the appropriate parameters, for example:
```
$ ./my_mastermind -c 1234
```
If the parameters are entered incorrectly, the corresponding text will be displayed:
```
Error! Parameters are incorrect.
```
---
* You can also enter these two parameters at the same time.
---
#### Example:
```
>./my_mastermind -c "0123"
Will you find the secret code?
Please enter a valid guess
---
Round 0
>1456
Well placed pieces: 0
Misplaced pieces: 1
---
Round 1
>tata
Wrong input!
>4132
Well placed pieces: 1
Misplaced pieces: 2
---
Round 2
>0123
Congratz! You did it!
```
## Code component
### Checking the introduced number of attempts
```c
int attempt_check(int att){
    if(att <= 0)
        return 0;
    return 1;
}
```
### Analogous to `strlen`
```c
int my_strlen(char* p1){
    int i = 0;
    while(p1[i] != '\0')
        i++;
    return i;
}
```
### Checking the entered code
```c
int code_check(char* str){
    if(my_strlen(str) == 4 && (str[0] >= '0' && str[0] <= '8') && (str[1] >= '0' && str[1] <= '8') && (str[2] >= '0' && str[2] <= '8') && (str[3] >= '0' && str[3] <= '8') && (str[0] != str[1] && str[0] != str[2] && str[0] != str[3] && str[2] != str[1] && str[2] != str[3] && str[3] != str[1] && str[3] != str[2]))
        return 1;
    return 0;
}
```
### Reading code from the console
```c
int read_input(char* input){
    for(int i = 0; read(0, &input[i], 1); i++)
        if(input[i] == '\n'){
            input[i] = '\0';
            return 1;
        }
    return 0;
}
```
### Number of correct and incorrect placements
```c
int wellmisplace(char* code, char* secret){
    int x = 0;
    int y = 0;
    for(int i = 0; i < 4; i++){
        if(code[i] == secret[i])
            x++;
        for(int j = 0; j < 4; j++)
            if(i != j && code[i] == secret[j])
                y++;
    }
    if(x != 4){
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", x, y);
        return 0;
    }
    printf("Congratz! You did it!\n");
    return 1;
}
```
### Generation of the secret code
```c
char* random_code(char* code){
    srand(time(NULL));
    int num_arr[4];
    for(int i = 0; i < 4; i++)
        num_arr[i] = rand() % 9;
    while(num_arr[1] == num_arr[0] || num_arr[2] == num_arr[0] || num_arr[2] == num_arr[1] || num_arr[3] == num_arr[0] || num_arr[3] == num_arr[1] || num_arr[3] == num_arr[2])
        for(int i = 0; i < 4; i++)
            num_arr[i] = rand() % 9;
    for(int i = 0; i < 4; i++)
        code[i] = '0' + num_arr[i];
    code[4] = '\0';
    return code;
}
```
### Function that works if the parameters are incorrect
```c
int err_param(){
    printf("Error! Parameters are incorrect.\n");
    return 1;
}
```
### Checking the entered parameters
```c
int param_check(int argc, char* argv[], int* attempts, char* secret){
    if(argc > 2){
        if(strcmp(argv[1], "-c") == 0){
            for(int i = 0; i < 4; i++)
                secret[i] = argv[2][i];
            if(argc >= 4 && strcmp((argv[3]), "-t") == 0)
                *attempts = atoi(argv[4]);
        }
        else if(strcmp((argv[1]), "-t") == 0){
            *attempts = atoi(argv[2]);
            if(argc >= 4 && strcmp(argv[3], "-c") == 0)
                for(int i = 0; i < 4; i++)
                   secret[i] = argv[4][i];
        }
        secret[4] = '\0';
    }
    if((argc != 1 && argc != 3 && argc != 5) || !code_check(secret) || !attempt_check(*attempts))
        return err_param();
    return 0;
}
```
### Function that starts the game
```c
void game(char* secret, int attempts, char* input){
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for(int round = 0; round < attempts; round++){
        printf("---\nRound %d\n", round);
        write(1, ">", 1);
        if(!read_input(input))
            break;
        while(!code_check(input)){
            printf("Wrong input!\n");
            write(1, ">", 1);
            if(!read_input(input)){
                attempts = 0;
                break;
            }
        }
        if(round < attempts)
            if(wellmisplace(input, secret))
                break;
    }
}
```
## Main function
In the main function I did the following things:
* Indicated that the standard number of attempts is 10.
* Created two variables:
    * input - to enter the code.
    * secret - to set a secret code.
* Generated a secret code.
* Checked the entered parameters.
* And then I started the game itself.
```c
int main(int argc, char* argv[]){
    int attempts = 10;
    char input[5];
    char secret[5];
    random_code(secret);
    if(param_check(argc, argv, &attempts, secret))
        return 1;
    game(secret, attempts, input);
    return 0;
}
```
---
### The note! This Readme file was written and translated from Russian, therefore some semantic errors may occur
