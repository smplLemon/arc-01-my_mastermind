#include "../include/my_mastermind_functions.h"

int main (int argc, char *argv[]){
    flag_struct flags = init_flag_struct();
    check_for_flags(argc, argv, &flags);

    // set secret code
    char secret_code_array[SECRET_CODE_LENGTH + 1]; // +1 for null terminator
    if (flags.flag_secret_code_on && is_user_secret_code_valid(argv[flags.flag_secret_code_position])){
        // set the secret code to the user's secret code
        strcpy(secret_code_array, argv[flags.flag_secret_code_position]);
    }
    else{
        // create a random secret code
        create_random_secret_code(secret_code_array);
    }

    //set max number of attempts
    int max_attempts;
    if (flags.flag_attempts_on && is_user_attempt_count_valid(argv[flags.flag_attempts_position])){
        max_attempts = atoi(argv[flags.flag_attempts_position]);
    }
    else{
        max_attempts = MAX_ATTEMPTS;
    }

    char* welcome_message = "Will you find the secret code?\nPlease enter a valid guess\n";
    printf("%s", welcome_message);

    int attempt_count = 0;
    int user_guess_length = SECRET_CODE_LENGTH + 1;
    char user_guess[user_guess_length];
    while (attempt_count < max_attempts){
        printf("---\nRound %d of %d\n", attempt_count + 1, max_attempts);
        if (!read_user_input(user_guess, user_guess_length)){
           exit(0);
        }
        if (!is_user_guess_valid(user_guess)){
            printf("Wrong input!\n");
            continue;
        }
        else if (is_user_guess_correct(user_guess, secret_code_array)){
            printf("Congratz! You did it!\n");
            return 0;
        }
        else{
            evaluate_user_guess(user_guess, secret_code_array);
        }
        attempt_count++;
    }
    printf("You lost! The secret code was %s\n", secret_code_array);
}
