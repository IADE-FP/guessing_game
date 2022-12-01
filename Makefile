CC=gcc
CFLAGS=-Wall -Wextra -Werror -g
LDFLAGS=-lm
EXEC=app
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o
