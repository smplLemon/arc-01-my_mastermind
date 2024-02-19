#include <my_mastermind.h>

void play_mastermind(int attempts, char *code) {
  int game_status = ONGOING;
  char *player_input = NULL;
  int tries = 0;
  
  printf("Will you find the secret code?\n");
  while (attempts > 0) {
    printf("---\n");
    printf("Round %d\n", tries);
    player_input = get_valid_input();
    if ((game_status = mastermind_logic(player_input, code)) == WIN) {
      break;
    }
    tries++;
    attempts--;
  }
  if (attempts == 0) {
    game_status = LOSE;
  }
  end_game_message(game_status);
}

int main(int argc, char **argv) {
  int attempts = 10;
  char *code = random_code();
  (void)argc;

  argv++;
  if (handle_flags(&attempts, &code, argv) == 0) {
    play_mastermind(attempts, code);
  } else {
    printf("Invalid input!");
  }
  free(code);
  return 0;
}
