CC = gcc

CFLAGS = -Wall -Wextra

LIBS = -lm

EXEC = uav

SRC = main.c


all:
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(LIBS)

run:
	./$(EXEC)

clean:
	rm -f $(EXEC)
