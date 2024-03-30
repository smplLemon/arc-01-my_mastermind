#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int calculateLength(char *input) {
    int length = 0;
    while (input[length])
        length++;
    return length;
}

char *copyString(char *destination, char *source) {
    int i;
    for (i = 0; source[i]; i++)
        destination[i] = source[i];
    destination[i] = '\0';
    return destination;
}

int findNumberInArray(char *numbers, char num) {
    for (int i = 0; numbers[i]; i++) {
        if (numbers[i] == num)
            return i;
    }
    return -1;
}

int ArethereSimilarCharacters(char *input) {
    int length = calculateLength(input);
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (input[i] == input[j]) {
                return 1;
            }
        }
    }
    return 0;
}

int compareNumbers(char *input, char *secretNumbers) {
    int correctlyPlaced = 0;
    int misplaced = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        for (int j = 0; secretNumbers[j] != '\0'; j++) {
            if (input[i] == secretNumbers[j] && i != j) {
                misplaced++;
            }
            else if (input[i] == secretNumbers[j]) {
                correctlyPlaced++;
            }
        }
    }
    if (correctlyPlaced == 4) {
        printf("Congratz! You did it!\n");
        return 1;
    }

    printf("Well placed numbers: %d\nMisplaced numbers: %d\n", correctlyPlaced, misplaced);
    return 0;
}

char *readInput() {
    int length = 0;
    char character;
    char *input = malloc(6);
    write(1, ">", 1);
    while (read(0, &character, 1)) {
        if (character == '\n') {
            input[length] = '\0';
            return input;
        }
        input[length++] = character;
    }
    return NULL;
}

char *SecretNumbers() {
    int count = 0;
    char *numbers = malloc(sizeof(char) * 5);
    numbers[4] = '\0';
    char num;
    while (count < 4) {
        num = rand() % 9 + 48;
        if (findNumberInArray(numbers, num) == -1) {
            numbers[count] = num;
            count++;
        }
    }
    return numbers;
}

int checkError(char *input) {
    int length = calculateLength(input);
    int count = 0;
    if (length != 4 || ArethereSimilarCharacters(input) == 1) {
        printf("Wrong input!\n");
        return 1;
    }
    while (count < length) {
        if (input[count] < '0' || input[count] > '8') {
            printf("Wrong input!\n");
            return 1;
        }
        count++;
    }
    return 0;
}

void startGame(int round, char *secretNumbers) {
    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");
    char *input;
    int count = 0;

    printf("---\n");
    printf("Round %d\n", count);

    while (count < round) {
        int inputError = 1;
        while (inputError) {
            input = readInput();
            if (input == NULL)
                return;
            inputError = checkError(input);
        }
        if (compareNumbers(input, secretNumbers))
            return;

        count++;
        if (count < round) {
            printf("---\n");
            printf("Round %d\n", count);
        }
    }
}

void commandLine(int argc, char **argv) {
    int count = 1;
    int round = 10;
    char *secretNumbers = SecretNumbers();
    while (count < argc) {
        if (strcmp(argv[count], "-c") == 0) {
            secretNumbers = argv[count + 1];
            count += 2;
        }
        else if (strcmp(argv[count], "-t") == 0) {
            round = atoi(argv[count + 1]);
            count += 2;
        }
    }
    startGame(round, secretNumbers);
}

int main(int argc, char **argv) {
    commandLine(argc, argv);
    return 0;
}
