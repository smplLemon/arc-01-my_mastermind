#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

// Объявления функций
void startGame(int argc, char **argv);
void gameProcess(int attempts, char *secret_code);
char *myRand(char *secret_code);
char *myStrchr(const char *str, int c);
size_t myStrlen(const char *str);
int myStrcmp(const char *str1, const char *str2);
char *myStrcpy(char *str1, const char *str2);
int myAtoi(const char *str);
char *myScanf();


// Главная функция
int main(int argc, char **argv) {
  // Вызов главной функции игры
  startGame(argc, argv);
  return 0;
}

// Функция начала игры
void startGame(int argc, char **argv) {
  // Выделение памяти под секретный код
  char *secretCode = malloc(sizeof(char) * 5);
  int attempts = 10;

  // Обработка аргументов командной строки
  for (int i = 1; i < argc; i++) {
    if (myStrcmp(argv[i], "-c") == 0) {
      myStrcpy(secretCode, argv[++i]);
    } else if (myStrcmp(argv[i], "-t") == 0) {
      attempts = myAtoi(argv[++i]);
    }
  }

  // Если секретный код не был предоставлен, генерируем его
  if (!secretCode[0]) {
    myRand(secretCode);
  }

  // Вывод информации о игре на английском
  printf("Secret Code: %s\n", secretCode);
  printf("Attempts: %d\n", attempts);

  // Запуск процесса игры
  gameProcess(attempts, secretCode);

  // Освобождение памяти
  free(secretCode);
}

// Функция для игрового процесса
void gameProcess(int attempts, char *secret_code) {
  int i = 0;
  char *enter_code;
  printf("Will you find the secret code?\nPlease enter a valid guess.\n");

  while (i < attempts) {
    printf("Round %d\n", i);

    if (myStrcmp((enter_code = myScanf()), "stop") == 0) {
      free(enter_code); // Освобождаем память после использования
      return;
    }

    // Вывод информации о правильно и неправильно угаданных символах
    int wellPlaced = 0, misplaced = 0;
    for (int j = 0; j < 4; ++j) {
      if (enter_code[j] == secret_code[j]) {
        wellPlaced++;
      } else if (myStrchr(secret_code, enter_code[j]) != NULL) {
        misplaced++;
      }
    }
    // Проверка на выигрыш
    if (wellPlaced == 4) {
      printf("Congratz! You did it!\n");
      return;
    }
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced,
           misplaced);

    free(enter_code); // Освобождаем память после использования

    i++;
  }

  // Если игрок не угадал секретный код за отведенное количество попыток
  printf("You didn't find the secret code. Try again!\n");
}

// Функция генерации случайного секретного кода
char *myRand(char *secret_code) {
  srand(time(0));
  int i = 0;

  while (i < 4) {
    char valid_numbers = (rand() % 9) + '0';
    int found = 0;

    // Проверка, есть ли valid_numbers уже в secret_code
    for (int j = 0; j < i; ++j) {
      if (secret_code[j] == valid_numbers) {
        found = 1;
        break;
      }
    }

    // Если valid_numbers не найден в secret_code, добавляем его
    if (!found) {
      secret_code[i++] = valid_numbers;
    }
  }

  return secret_code;
}

// Функция поиска символа в строке
char *myStrchr(const char *str, int c) {
  while (*str != '\0') {
    if (*str == c) {
      return (char *)str;
    }
    str++;
  }
  return NULL;
}

// Функция определения длины строки
size_t myStrlen(const char *str) {
  size_t size = 0;
  for (size_t i = 0; str[i] != '\0'; i++) {
    size++;
  }
  return size;
}

// Функция сравнения строк
int myStrcmp(const char *str1, const char *str2) {
  size_t sizeStr1 = myStrlen(str1);
  size_t sizeStr2 = myStrlen(str2);

  if (sizeStr1 > sizeStr2) {
    return 1;
  } else if (sizeStr1 < sizeStr2) {
    return -1;
  }

  for (size_t i = 0; i < sizeStr1; i++) {
    if (str1[i] != str2[i]) {
      return str1[i] - str2[i];
    }
  }

  return 0;
}

// Функция копирования строк
char *myStrcpy(char *str1, const char *str2) {
  size_t lenStr2 = myStrlen(str2);

  for (size_t i = 0; i <= lenStr2; i++) {
    str1[i] = str2[i];
  }
  return str1;
}

// Функция преобразования строки в число
int myAtoi(const char *str) {
  int i = 0;
  long int num = 0;
  int flag = 0;

  while (str[i] == ' ') {
    i++;
  }

  if (str[i] == '+' || str[i] == '-') {
    if (str[i] == '-') {
      flag = 1;
    }
    i++;
  }

  while (str[i] >= '0' && str[i] <= '9') {
    num = num * 10 + (str[i] - '0');

    if (!flag && num > INT_MAX) {
      return INT_MAX;
    } else if (flag && -num < INT_MIN) {
      return INT_MIN;
    }

    i++;
  }
  if (flag) {
    num = -num;
  }

  return num;
}

// Функция чтения строки с клавиатуры
char *myScanf() {
  char c;
  int i = 0;
  char *str = malloc(sizeof(char) * 6); // Выделение памяти под строку
  printf(">");

  if (str == NULL) {
    perror("Memory allocation error");
    exit(EXIT_FAILURE);
  }

  while (read(STDIN_FILENO, &c, 1)) {
    if (c == '\n' || i == 5) {
      str[i] = '\0'; // Завершаем строку нулевым символом
      return str;
    }

    str[i] = c;
    i++;

    // Если выделенная память заканчивается, увеличиваем ее размер
    if (i >= 5) {
      char *temp = realloc(
          str,
          i + 1); // Увеличиваем размер на 1 для завершающего нулевого символа
      if (temp == NULL) {
        free(str); // Освобождаем память в случае неудачи realloc
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
      }
      str = temp;
    }
  }

  // В случае ошибки возвращаем NULL
  return NULL;
}
