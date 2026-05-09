CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99
LDFLAGS = -lm
TARGET  = uav
SRCS    = main.c fichier.c
OBJS    = $(SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

main.o: main.c fichier.h
	$(CC) $(CFLAGS) -c main.c

fichier.o: fichier.c fichier.h
	$(CC) $(CFLAGS) -c fichier.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)


