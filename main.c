#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

// Определение констант
enum
{
    CODE_LENGTH = 4,
    MAX_ATTEMPTS = 10,
    MAX_DIGIT = 8,
    MIN_DIGIT = 0,
    MAX_INPUT_LENGTH = CODE_LENGTH + 1,
    MY_INT_MIN = (-2147483648),
    MY_INT_MAX = 2147483647,
    INPUT_NOT_COMPLETE = -1
};

// Объявление функций
int my_strcmp(const char *str1, const char *str2);
char *my_strcpy(char *dest, const char *src);
size_t my_strlen(const char *str);
char *my_strchr(const char *str, int c);
size_t my_atoi(const char *str);
int is_valid_input(const char *str);
int are_digits_unique(const char *str);
void print_error_message(const char *message);
void start_game(int argc, char **argv);
void game_process(const char *secretCode, const int attempts);
char *generate_secret_code(char *secretCode);
char *my_scanf();
void display_game_info(const char *secretCode, int attempts);

// Основная функция
int main(int argc, char **argv) {
    start_game(argc, argv);
    return 0;
}

// Инициализация игры
void start_game(int argc, char **argv) {
    char secretCode[CODE_LENGTH + 1];
    int attempts = MAX_ATTEMPTS;

    // Обработка аргументов командной строки
    for (int i = 1; i < argc; i++) {
        if (my_strcmp(argv[i], "-c") == 0) {
            my_strcpy(secretCode, argv[++i]);
        }
        else if (my_strcmp(argv[i], "-t") == 0) {
            attempts = my_atoi(argv[++i]);
        }
    }

    // Если не предоставлен секретный код, сгенерировать новый
    if (secretCode[0] == '\0' || my_strlen(secretCode) != CODE_LENGTH ||
        !is_valid_input(secretCode) || !are_digits_unique(secretCode)) {
        generate_secret_code(secretCode);
    }

    // Вывод информации об игре
    display_game_info(secretCode, attempts);

    // Запуск процесса игры
    game_process(secretCode, attempts);
}

// Игровой процесс
void game_process(const char *secretCode, const int attempts) {
    int round = 0;
    char *userGuess;
    printf("Will you find the secret code?\nPlease enter a valid guess.\n");

    // Основной цикл игры
    while (round < attempts) {
        printf("Round %d\n", round);

        // Получение ввода от пользователя
        userGuess = my_scanf();

        // Проверка на неполный ввод или запрос пользователя на выход
        if (userGuess == NULL) {
            free(userGuess);
            break; 
        }
        else if (userGuess == (char *)INPUT_NOT_COMPLETE) {
            free(userGuess);
            continue;
        }

        // Валидация ввода пользователя
        if (my_strlen(userGuess) != CODE_LENGTH || !is_valid_input(userGuess) ||
            !are_digits_unique(userGuess)) {
            printf("Invalid input. Please enter a %d-digit code with unique values "
                "between %d and %d.\n",
                CODE_LENGTH, MIN_DIGIT, MAX_DIGIT);
            free(userGuess);
            continue;
        }

        // Сравнение догадки пользователя с секретным кодом
        int wellPlaced = 0, misplaced = 0;
        for (int i = 0; i < CODE_LENGTH; ++i) {
            if (userGuess[i] == secretCode[i]) {
                wellPlaced++;
            }
            else if (my_strchr(secretCode, userGuess[i]) != NULL) {
                misplaced++;
            }
        }

        // Проверка, угадал ли пользователь код
        if (wellPlaced == CODE_LENGTH) {
            printf("Congratulations! You did it!\n");
            free(userGuess);
            return;
        }

        // Предоставление обратной связи пользователю
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced,
            misplaced);

        free(userGuess);
        round++;
    }

    printf("You didn't find the secret code. Try again!\n");
}

// Генерация случайного секретного кода
char *generate_secret_code(char *secretCode) {
    srand((unsigned int)time(NULL));

    int used_digits[MAX_DIGIT - MIN_DIGIT + 1] = {0};

    for (size_t i = 0; i < CODE_LENGTH; ++i) {
        int digit;
        do {
            digit = rand() % (MAX_DIGIT - MIN_DIGIT + 1);
        } while (used_digits[digit]);

        secretCode[i] = (char)('0' + digit);
        used_digits[digit] = 1;
    }

    secretCode[CODE_LENGTH] = '\0';
    return secretCode;
}

// Пользовательская функция scanf для чтения ввода пользователя
char *my_scanf() {
    char c;
    size_t i = 0;
    char *inputString = (char *)calloc(MAX_INPUT_LENGTH, sizeof(char));

    if (inputString == NULL) {
        print_error_message("Memory allocation error");
        return NULL;
    }

    printf(">");

    // Чтение ввода посимвольно
    while (read(STDIN_FILENO, &c, 1)) {
        if (c == '\n') {
            inputString[i] = '\0';
            return (c == '\n') ? inputString : (char *)INPUT_NOT_COMPLETE;
        }

        inputString[i++] = c;

        if (i >= MAX_INPUT_LENGTH) {
            char *temp = (char *)realloc(inputString, i + 1);
            if (temp == NULL) {
                free(inputString);
                print_error_message("Memory allocation error");
                return NULL;
            }
            inputString = temp;
        }
    }


    return inputString;
}

// Вывод информации об игре
void display_game_info(const char *secretCode, int attempts) {
    printf("Secret Code: %s\n", secretCode);
    printf("Attempts: %d\n", attempts);
}

// Валидация ввода на наличие только допустимых цифр
int is_valid_input(const char *str) {
    for (size_t i = 0; i < CODE_LENGTH; i++) {
        if (!isdigit((unsigned char)str[i]) || str[i] < '0' || str[i] > '8') {
            return 0;
        }
    }
    return 1;
}

// Проверка, что все цифры во вводе уникальны
int are_digits_unique(const char *str) {
    for (size_t i = 0; i < CODE_LENGTH; i++) {
        for (size_t j = i + 1; j < CODE_LENGTH; j++) {
            if (str[i] == str[j]) {
                return 0;
            }
        }
    }
    return 1;
}

// Пользовательская функция atoi для преобразования строк в целые числа
size_t my_atoi(const char *str) {
    int i = 0;
    long int num = 0;
    int flag = 0;

    // Пропуск начальных пробелов
    while (str[i] == ' ') {
        i++;
    }

    // Проверка наличия знака
    if (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-') {
            flag = 1;
        }
        i++;
    }

    // Преобразование цифр в целое число
    while (str[i] >= '0' && str[i] <= '9') {
        num = num * 10 + (str[i] - '0');

        // Проверка на переполнение или недополнение
        if (!flag && num > MY_INT_MAX) {
            return MY_INT_MAX;
        }
        else if (flag && -num < MY_INT_MIN) {
            return MY_INT_MIN;
        }

        i++;
    }

    // Применение знака при необходимости
    if (flag) {
        num = -num;
    }

    return num;
}

// Пользовательская функция сравнения строк
int my_strcmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return (*str1 - *str2);
        }
        str1++;
        str2++;
    }

    if (*str1 == '\0' && *str2 == '\0') {
        return 0;
    }

    return (*str1 - *str2);
}

// Пользовательская функция копирования строк
char *my_strcpy(char *dest, const char *src) {
    size_t lenStr2 = my_strlen(src);

    for (size_t i = 0; i <= lenStr2; i++) {
        dest[i] = src[i];
    }
    return dest;
}

// Пользовательская функция определения длины строки
size_t my_strlen(const char *str) {
    size_t length = 0;

    while (*str != '\0') {
        ++length;
        ++str;
    }

    return length;
}

// Пользовательская функция поиска символа в строке
char *my_strchr(const char *str, int c) {
    while (*str != '\0') {
        if (*str == c) {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}

// Вывод сообщений об ошибке
void print_error_message(const char *message) {
    fprintf(stderr, "%s\n", message);
}
