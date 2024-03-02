CC = gccc
CFLAGS = -Wall -Wextra -Werror
SOURCE = my_mastermind.c
TARGET = my_mastermind
SRC = my_mastermind.c 

all: $(TARGET)

$(TARGET) : $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

$(OBJECT) : $(SOURCE)
	 $(CC) $(CFLAGS) -C $(SOURCE)

clean :
    rm -f *.o


fclean:
	rm -r $(TARGET)