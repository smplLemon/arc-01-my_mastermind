NAME = my_mastermind
CC = gcc
SRCS_DIR = ./srcs/
INCLUDES = ./includes/
RM = /bin/rm -f
FILES = my_mastermind useful_funcs options logic
CFILES = $(patsubst %, $(SRCS_DIR)%.c, $(FILES))
OFILES = $(patsubst %, %.o, $(FILES))
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(OFILES):
	@$(CC) $(CFLAGS) -c -I $(INCLUDES) $(CFILES)

$(NAME): $(OFILES)
	@$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

clean:
	@$(RM) $(OFILES)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re