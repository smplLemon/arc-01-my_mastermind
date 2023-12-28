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
int myStrcmp(const char *str1, const char *str2);
char *myStrcpy(char *dest, const char *src);
size_t myStrlen(const char *str);
char *myStrchr(const char *str, int c);
size_t myAtoi(const char *str);
int isValidInput(const char *str);
int areDigitsUnique(const char *str);
void printErrorMessage(const char *message);
void startGame(int argc, char **argv);
void gameProcess(const char *secretCode);
char *generateSecretCode(char *secretCode);
char *myScanf();
void displayGameInfo(const char *secretCode, int attempts);

// Основная функция
int main(int argc, char **argv)
{
    startGame(argc, argv);
    return 0;
}

// Инициализация игры
void startGame(int argc, char **argv)
{
    char secretCode[CODE_LENGTH + 1];
    int attempts = MAX_ATTEMPTS;

    // Обработка аргументов командной строки
    for (int i = 1; i < argc; i++)
    {
        if (myStrcmp(argv[i], "-c") == 0)
        {
            myStrcpy(secretCode, argv[++i]);
        }
        else if (myStrcmp(argv[i], "-t") == 0)
        {
            attempts = myAtoi(argv[++i]);
        }
    }

    // Если не предоставлен секретный код, сгенерировать новый
    if (secretCode[0] == '\0' || myStrlen(secretCode) != CODE_LENGTH || !isValidInput(secretCode) || !areDigitsUnique(secretCode))
    {
        generateSecretCode(secretCode);
    }

    // Вывод информации об игре
    displayGameInfo(secretCode, attempts);

    // Запуск процесса игры
    gameProcess(secretCode);
}

// Игровой процесс
void gameProcess(const char *secretCode)
{
    int round = 0;
    char *userGuess;

    printf("Will you find the secret code?\nPlease enter a valid guess.\n");

    // Основной цикл игры
    while (1)
    {
        printf("Round %d\n", round);

        // Получение ввода от пользователя
        userGuess = myScanf();

        // Проверка на неполный ввод или запрос пользователя на выход
        if (userGuess == NULL)
        {
            free(userGuess);
            continue;
        }
        else if (userGuess == (char *)INPUT_NOT_COMPLETE)
        {
            free(userGuess);
            break;
        }

        // Валидация ввода пользователя
        if (myStrlen(userGuess) != CODE_LENGTH || !isValidInput(userGuess) || !areDigitsUnique(userGuess))
        {
            printf("Invalid input. Please enter a %d-digit code with unique values between %d and %d.\n", CODE_LENGTH, MIN_DIGIT, MAX_DIGIT);
            free(userGuess);
            continue;
        }

        // Сравнение догадки пользователя с секретным кодом
        int wellPlaced = 0, misplaced = 0;
        for (int i = 0; i < CODE_LENGTH; ++i)
        {
            if (userGuess[i] == secretCode[i])
            {
                wellPlaced++;
            }
            else if (myStrchr(secretCode, userGuess[i]) != NULL)
            {
                misplaced++;
            }
        }

        // Проверка, угадал ли пользователь код
        if (wellPlaced == CODE_LENGTH)
        {
            printf("Congratulations! You did it!\n");
            free(userGuess);
            return;
        }

        // Предоставление обратной связи пользователю
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);

        free(userGuess);
        round++;
    }

    printf("You didn't find the secret code. Try again!\n");
}

// Генерация случайного секретного кода
char *generateSecretCode(char *secretCode)
{
    srand(time(NULL));

    int used_digits[MAX_DIGIT - MIN_DIGIT + 1] = {0};

    for (int i = 0; i < CODE_LENGTH; ++i)
    {
        int digit;
        do
        {
            digit = rand() % (MAX_DIGIT - MIN_DIGIT + 1);
        } while (used_digits[digit]);

        secretCode[i] = '0' + digit;
        used_digits[digit] = 1;
    }

    secretCode[CODE_LENGTH] = '\0';
    return secretCode;
}

// Пользовательская функция scanf для чтения ввода пользователя
char *myScanf()
{
    char c;
    int i = 0;
    char *inputString = malloc(sizeof(char) * MAX_INPUT_LENGTH);

    printf(">");

    if (inputString == NULL)
    {
        printErrorMessage("Memory allocation error");
    }

    // Чтение ввода посимвольно
    while (read(STDIN_FILENO, &c, 1))
    {
        // Проверка на новую строку или достижение максимальной длины
        if (c == '\n' || i == CODE_LENGTH)
        {
            inputString[i] = '\0';
            return (c == '\n') ? inputString : (char *)INPUT_NOT_COMPLETE;
        }

        // Сохранение символа в строке ввода
        inputString[i++] = c;

        // Изменение размера строки ввода при необходимости
        if (i >= MAX_INPUT_LENGTH)
        {
            char *temp = realloc(inputString, i + 1);
            if (temp == NULL)
            {
                free(inputString);
                printErrorMessage("Memory allocation error");
            }
            inputString = temp;
        }
    }

    return NULL;
}

// Вывод информации об игре
void displayGameInfo(const char *secretCode, int attempts)
{
    printf("Secret Code: %s\n", secretCode);
    printf("Attempts: %d\n", attempts);
}

// Валидация ввода на наличие только допустимых цифр
int isValidInput(const char *str)
{
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        if (!isdigit(str[i]) || str[i] < '0' || str[i] > '8')
        {
            return 0;
        }
    }
    return 1;
}

// Проверка, что все цифры во вводе уникальны
int areDigitsUnique(const char *str)
{
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        for (int j = i + 1; j < CODE_LENGTH; j++)
        {
            if (str[i] == str[j])
            {
                return 0;
            }
        }
    }
    return 1;
}

// Пользовательская функция atoi для преобразования строк в целые числа
size_t myAtoi(const char *str)
{
    int i = 0;
    long int num = 0;
    int flag = 0;

    // Пропуск начальных пробелов
    while (str[i] == ' ')
    {
        i++;
    }

    // Проверка наличия знака
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
        {
            flag = 1;
        }
        i++;
    }

    // Преобразование цифр в целое число
    while (str[i] >= '0' && str[i] <= '9')
    {
        num = num * 10 + (str[i] - '0');

        // Проверка на переполнение или недополнение
        if (!flag && num > MY_INT_MAX)
        {
            return MY_INT_MAX;
        }
        else if (flag && -num < MY_INT_MIN)
        {
            return MY_INT_MIN;
        }

        i++;
    }

    // Применение знака при необходимости
    if (flag)
    {
        num = -num;
    }

    return num;
}

// Пользовательская функция сравнения строк
int myStrcmp(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 < *str2)
        {
            return -1;
        }
        else if (*str1 > *str2)
        {
            return 1;
        }
        str1++;
        str2++;
    }

    return 0;
}

// Пользовательская функция копирования строк
char *myStrcpy(char *dest, const char *src)
{
    size_t lenStr2 = myStrlen(src);

    for (size_t i = 0; i <= lenStr2; i++)
    {
        dest[i] = src[i];
    }
    return dest;
}

// Пользовательская функция определения длины строки
size_t myStrlen(const char *str)
{
    size_t length = 0;

    while (*str != '\0')
    {
        ++length;
        ++str;
    }

    return length;
}

// Пользовательская функция поиска символа в строке
char *myStrchr(const char *str, int c)
{
    while (*str != '\0')
    {
        if (*str == c)
        {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}

// Вывод сообщений об ошибке
void printErrorMessage(const char *message)
{
    fprintf(stderr, "%s\n", message);
}
