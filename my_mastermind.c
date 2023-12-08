#include "mastermind.h"

int main(int argc, char** argv) {
    // Allocate memory for the secret code.
    char* st_cd = calloc(sizeof(char), 4 + 1);

    // Default maximum attempts.
    int mx_atmp = 10;

    // Parse command line arguments.
    for (int i = 1; i < argc; i++) {
        // Check for the secret code option.
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            // Copy the provided secret code to st_cd.
            strncpy(st_cd, argv[i + 1], 4);
            st_cd[4] = '\0'; // Ensure null-termination.
        } 
        // Check for the maximum attempts option.
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            // Set the maximum attempts based on the provided value.
            mx_atmp = atoi(argv[i + 1]);
        }
    }

    // If no secret code provided, generate a random one.
    if (strlen(st_cd) == 0) {
        srand(time(NULL));
        random_code(st_cd);
    }

    // Array to store the user's guess.
    char user_guess[4 + 1];
    // Variables to store feedback on the guess.
    int well_placed, misplaced;
    // Counter for the number of rounds played.
    int rounds = 0;

    // Prompt the user to enter a valid guess.
    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    // Main game loop.
    for (; rounds < mx_atmp; rounds++) {
        // Display the current round.
        printf("---\nRound %d\n>", rounds);

        // Read user input.
        if (read(0, user_guess, 4 + 1) == -1) {
            printf("Error reading input.\n");
            return 1;
        }

        user_guess[4] = '\0'; // Ensure null-termination.

        // Check if the input guess is valid.
        if (!is_input_valid(user_guess)) {
            printf("Wrong input!\n");
            continue; // Skip to the next iteration if the input is invalid.
        }

        // Evaluate the guess and update well_placed and misplaced counts.
        evaluate_guess(user_guess, st_cd, &well_placed, &misplaced);

        // Check if the user guessed the correct code.
        if (well_placed == 4) {
            printf("Congratz! You did it!\n");
            return 0;
        }

        // Display feedback on the guess.
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, misplaced);
    }

    // Game over message when maximum attempts are reached.
    printf("---\nGame over. You didn't find the secret code.\n");

    return 0;
}
