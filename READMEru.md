# My Mastermind
Данный код представляет собой имплементацию цифровой версии знаменитой настольной игры далёкого 1970 года, называющейся  - *Mastermind*.

Код был написан [Абдуссамадом Турдыходжаевым](https://github.com/Abuuu2007).

## Содержание
- [Описание](#описание)
- [Использование](#использование)
- [Составляющая кода](#составляющая-кода)
- [Основная функция main](#основная-функция-main)

## Описание
Мне было дано задание создать Mastermind, имеющий два параметра: 
1. `-c` - устанавливающий секретный код. Если секретный код не прописан, то он будет сгенерирован случайно.
2. `-t` - указывающий на число попыток/раундов. Если кол-во попыток не указывается, то число равно 10.

Вместо 9 разных цветов используются цифры от 0 до 8 включительно.

Но при всем этом, можно использовать ограниченное кол-во функций, а именно:

* printf(3)
* write(2)
* read(2)
* rand() (/ srand())
* time()
* atoi()
* strcmp()

При создании мне понадобились все функции, помимо `write()` \:D

## Использование
### Запуск игры
Для того, чтобы запустить игру, нужно ввести в консоль:
```
$ ./my_mastermind
```
### Секретный код
Для того, чтобы запустить игру, установив секретный код, нужно прописать соответствующие параметры, например:
```
$ ./my_mastermind -t 5
```
### Попытки
Для того, чтобы запустить игру, указав число попыток, нужно прописать соответствующие параметры, например:
```
$ ./my_mastermind -с 1234
```
В случае неправильного введения параметров будет выведен соответствующий текст:
```
Error! Parameters are incorrect.
```
---
* Одновременно вводить эти два параметра можно в том числе.
---
Думаю, нет необходимости подробно описывать процесс игры, так как эта информация уже доступна на платформах типа Qwasar, где мы, студенты Astrum, выполняем задания.

## Составляющая кода
### Функция `my_strlen`
Для начала я создал функцию, аналогичную `strlen`, т.к. его использование было запрещено:
```c
int my_strlen(char* p1){
    int i = 0;
    while(p1[i] != '\0')
        i++;
    return i;
}
```
---
### Проверка вводимого кода `SCRT_CODE`
Далее я создал макрос, проверяющий вводимое через консоль игроком значение на кол-во символов и индивидуальность каждой комбинации:
```c
#define SCRT_CODE(str) (my_strlen(str) == 4 && (str[0] >= '0' && str[0] <= '8') && (str[1] >= '0' && str[1] <= '8') && (str[2] >= '0' && str[2] <= '8') && (str[3] >= '0' && str[3] <= '8') && (str[0] != str[1] && str[0] != str[2] && str[0] != str[3] && str[2] != str[1] && str[2] != str[3] && str[3] != str[1] && str[3] != str[2]))
```
---
### Кол-во верно и неверно расположенных чисел `wellmisplace`
Данная функция проверяет то, правильно ли расположены введенные игроком комбинации цифр:
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
1. Если не все введенные цифры верны, выводится соответствующий текст, например:
```
Well placed pieces: 2
Misplaced pieces: 1
```
2. В случае идентичности введенного кода секретному, выводится следующий текст:
```
Congratz! You did it!
```
---
### Случайная генерация секретного кода `random_code`
Функция `random_code` выполняет случайную генерацию секретного кода, если параметр `-c` не будет использован:
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
## Основная функция `main`
Задавая параметры `argc` и `argv` для передачи аргументов консоли, задаю условие, чтобы в случае некорректного количества аргументов, игра останавливалась:
```c
int main(int argc, char* argv[]){
    if(argc == 2 || argc > 5 || argc == 4){
        printf("Error! Parameters are incorrect.\n");
        return 1;
    }
```
---
* Для правильной работы `random_code` использую `srand(time(NULL))`.
* Приравниваю число попыток к 9 (индексация начинается с нуля, т.е. попыток 10).
* Создаю переменную `input` для передачи кода через консоль, и `secret` - для установки секретного кода. 
* При помощи `random_code(secret)` генерирую случайным образом секретный код:
```c
srand(time(NULL));
int round = 0;
int attempts = 9;
char input[5];
char secret[5];
random_code(secret);
```
---
Пишу код, принимающий аргументы консоли `-c` и `-t` для установки секретного кода и числа попыток:
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
Если аргументы принимаются успешно, срабатывает код, запускающий процесс игры:
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
Если игрок угадывает секретный код или количество попыток кончается, игра заканчивается.

---