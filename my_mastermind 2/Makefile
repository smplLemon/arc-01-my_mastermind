KOM = gcc
CFLAGS = -g -Wall -Wextra -Werror
NAME = my_mastermind.c
OUTFILE = my_mastermind

$(OUTFILE):$(NAME)
	$(KOM) $(CFLAGS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -r $(OUTFILE)