#include "mastermind.h"

// Function to generate a random secret code and store it in the 'result' array.
char* random_code(char* result) {
    // Array of available digits.
    char available_numbers[] = "0123456789";

    // Loop to fill the result array with random digits.
    for (int i = 0; i < 4; i++) {
        // Generate a random index within the available numbers.
        int index = rand() % (10 - i);

        // Assign the selected digit to the result array.
        result[i] = available_numbers[index];

        // Remove the used digit from the available numbers.
        available_numbers[index] = available_numbers[9 - i];
    }

    // Add null terminator to the result array.
    result[4] = '\0';

    // Return the generated result array.
    return result;
}

// Function to evaluate a guess against the secret code and update correct and misplaced counts.
void evaluate_guess(char* guess, char* secret_code, int* correct_place, int* misplaced) {
    // Arrays to store histograms of digits in the guess and secret code.
    int guess_histogram[10] = {0};
    int secret_code_histogram[10] = {0};

    // Initialize counts to zero.
    *correct_place = 0;
    *misplaced = 0;

    // Loop to compare each digit in the guess and secret code.
    for (int i = 0; i < 4; i++) {
        // Check for correct placement of digits.
        if (guess[i] == secret_code[i]) {
            (*correct_place)++;
        } else {
            // Update histograms for misplaced digits.
            guess_histogram[guess[i] - '0']++;
            secret_code_histogram[secret_code[i] - '0']++;
        }
    }

    // Loop to calculate the total count of misplaced digits.
    for (int i = 0; i < 10; i++) {
        *misplaced += (secret_code_histogram[i] < guess_histogram[i]) ? secret_code_histogram[i] : guess_histogram[i];
    }
}

// Function to check if the input guess is valid according to game rules.
int is_input_valid(char* input) {
    // Check if the length of the input is exactly 4.
    if (strlen(input) != 4) {
        return 0;
    }

    // Check for repeated digits in the input.
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (input[i] == input[j]) {
                return 0; // Invalid input with repeated digits.
            }
        }
    }

    // Check if each character in the input is a digit between 0 and 9.
    for (int i = 0; i < 4; i++) {
        if (input[i] < '0' || input[i] > '9') {
            return 0; // Invalid input with non-digit characters.
        }
    }

    // Input is valid according to game rules.
    return 1;
}
