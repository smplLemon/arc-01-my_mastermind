G = gcc
TARGET =  my_mastermind
SRC = my_mastermind.c
FLAGC = -Wall -Wextra -Werror

$(TARGET): $(SRC)
 $(G) $(FLAGC) -o  $(TARGET) $(SRC)

clean:
 rm -r $(TARGET)
 