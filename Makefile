CC = gcc
CFCLS = -g -Wall -Wextra -Werror
SOURCE = my_mastemind.c
TARGET =  my_mastemind

$(TARGET): $(SOURCE)
	$(CC) $(CFCLS) -o $@ $^

.PHONY: flcean

flcean
	@rm -r $(TARGET)
