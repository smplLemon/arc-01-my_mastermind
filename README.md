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
1. `-c` - establishing a secret code. If the secret code is not registered, it will be generated randomly.
2. `-t` - indicating the number of attempts/rounds. If the number of attempts is not specified, then the number is 10.

Instead of 9 different colors, numbers from 0 to 8 inclusive are used.

But with all this, you can use a limited number of functions, namely:

* printf(3)
* write(2)
* read(2)
* rand() (/ srand())
* time()
* atoi()
* strcmp()

When creating, I needed all the functions besides `write()` \:D

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
I think there is no need to particularly imagine the game process, because... this information is already available in Qwasar and other platforms where we, Astrum’s students, were given access to complete tasks.

## Code component
### Function ``my_strlen``
To begin with, I created a function similar to `strlen`, because... its use was prohibited:
```c
int my_strlen(char* p1){
    int i = 0;
    while(p1[i] != '\0')
        i++;
    return i;
}
```
---
### Checking the input code `SCRT_CODE`
Next, I created a macro that checks the value entered through the console by the player for the number of characters and the individuality of each combination:
```c
#define SCRT_CODE(str) (my_strlen(str) == 4 && (str[0] >= '0' && str[0] <= '8') && (str[1] >= '0' && str[1] <= '8') && (str[2] >= '0' && str[2] <= '8') && (str[3] >= '0' && str[3] <= '8') && (str[0] != str[1] && str[0] != str[2] && str[0] != str[3] && str[2] != str[1] && str[2] != str[3] && str[3] != str[1] && str[3] != str[2]))
```
---
### Number of correctly and incorrectly placed numbers `wellmisplace`
This function checks whether the combinations of numbers entered by the player are located correctly:
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
    else{
        printf("Congratz! You did it!\n");
        return 1;
    }
}
```
1. If not all entered numbers are correct, the corresponding text is displayed, for example:
```
Well placed pieces: 2
Misplaced pieces: 1
```
2. If the entered code is identical to the secret code, the following text is displayed:
```
Congratz! You did it!
```
---
### Random generation of secret code `random_code`
The `random_code` function randomly generates a secret code if the `-c` option is not used:
```c
char* random_code(char* code){
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
## `Main` function
By setting the `argc` and `argv` parameters for passing console arguments, I set a condition so that if the number of arguments is incorrect, the game will stop:
```c
int main(int argc, char* argv[]){
    if(argc == 2 || argc > 5 || argc == 4){
        printf("Error! Parameters are incorrect.\n");
        return 1;
    }
```
---
* For `random_code` to work correctly I use `srand(time(NULL))`.
* I equate the number of attempts to 9 (indexing starts from 0, that is, 10 attempts).
* I create a variable `input` for passing the code through the console, and `secret` - for setting the secret code.
* Using `random_code(secret)` I randomly generate a secret code:
```c
srand(time(NULL));
int round = 0;
int attempts = 9;
char input[5];
char secret[5];
random_code(secret);
```
---
I'm writing code that takes `-c` and `-t` console arguments to set the secret code and the number of attempts:
```c
if(argc > 2){
    if(strcmp(argv[1], "-c") == 0){
        if(argc < 3 || !SCRT_CODE(argv[2])){
            printf("Error! Parameters are incorrect.\n");
            return 1;
        }
        for(int i = 0; i < 4; i++)
            secret[i] = argv[2][i];
        secret[4] = '\0';

        if(argc >= 4 && strcmp((argv[3]), "-t") == 0){
            if(argc < 5 || !attempt_checker(argv, 4)){
                printf("Error! Parameters are incorrect.\n");
                return 1;
            }
            attempts = atoi(argv[4]) - 1;
        }
    }
    else if(strcmp((argv[1]), "-t") == 0){
        if(argc < 3 || !attempt_checker(argv, 2)){
            printf("Error! Parameters are incorrect.\n");
            return 1;
        }
        attempts = atoi(argv[2]) - 1;

        if(argc >= 4 && strcmp(argv[3], "-c") == 0){
            if(argc < 5 || !SCRT_CODE(argv[4])){
                printf("Error! Parameters are incorrect.\n");
                return 1;
            }
            for(int i = 0; i < 4; i++)
                secret[i] = argv[4][i];
            secret[4] = '\0';
        }
    }
}
```
---
If the arguments are accepted successfully, the code runs, starting the game process:
```c
    while(round <= attempts){
        printf("---\nRound %d\n>", round);
        char c;
        int i = 0;
        while(read(0, &c, 1) && c != '\n'){
            input[i] = c;
            i++;
        }   input[i] = '\0';
        if(!SCRT_CODE(input))
            while(!SCRT_CODE(input)){
                printf("Wrong input!\n>");
                int i = 0;
                while(read(0, &c, 1) && c != '\n'){
                    input[i] = c;
                    i++;
                }   input[i] = '\0';
            }
        if(wellmisplace(input, secret)){
            return 0;
        } round++;
    }
    return 0;
}
```
If the player guesses the secret code or the number of attempts runs out, the game ends.

---

### The note! This Readme file was written and translated from Russian, therefore some semantic errors may occur