#include "mastermind.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));

    char secretCode[CODE_LENGTH + 1];
    int attempts = MAX_ATTEMPTS;

    if (argc > 1) {
        for (int i = 1; i < argc; i += 2) {
            if (argv[i][0] == '-' && (i + 1) < argc) {
                switch (argv[i][1]) {
                    case 'c':
                        strncpy(secretCode, argv[i + 1], CODE_LENGTH);
                        secretCode[CODE_LENGTH] = '\0';
                        break;
                    case 't':
                        attempts = atoi(argv[i + 1]);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    if (secretCode[0] == '\0') {
        generateSecretCode(secretCode);
    }

    printWelcomeMessage();

    for (int round = 0; round < attempts; ++round) {
        char guess[CODE_LENGTH + 1];
        printRound(round);

        int bytesRead = read(0, guess, CODE_LENGTH + 1);
        if (bytesRead <= 0) {
            printf("\n");
            break;
        }

        guess[CODE_LENGTH] = '\0';

        if (!isValidInput(guess)) {
            round--;
            continue;
        }

        int wellPlaced, misplaced;
        checkGuess(secretCode, guess, &wellPlaced, &misplaced);
        printResult(wellPlaced, misplaced);

        if (wellPlaced == CODE_LENGTH) {
            printf("Congratz! You did it!\n");
            break;
        }
    }

    return 0;
}