NAME	= get_next_line
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC = get_next_line.c get_next_line_utils.c main.c
OBJ = $(SRC:.c=.o)
HEADER = get_next_line.h 
TARGET = get_next_line

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
