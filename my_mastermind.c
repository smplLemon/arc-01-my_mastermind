#include "mastermind.h"

#define MAX_ATTEMPTS 10

int main(int argc, char *argv[]) {
    if (argc == 5) {
        mastermind(argv[2], atoi(argv[4]));
    } else if (argc == 3) {
        mastermind(argv[3], MAX_ATTEMPTS);
    } else {
        char code[5];
        srand(time(0));
        snprintf(code, 5, "%d", 1000+(rand()%8000));
        mastermind(code, MAX_ATTEMPTS);
    }

    return 0;
}
