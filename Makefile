CC      = gcc
CFLAGS  = -Wall -Wextra -O2
LIBS    = -lm
TARGET  = uav
SRCS    = main.c drone.c
OBJS    = main.o drone.o

# Compilation complete
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

main.o: main.c drone.h
	$(CC) $(CFLAGS) -c main.c

drone.o: drone.c drone.h
	$(CC) $(CFLAGS) -c drone.c

# Nettoyage des fichiers objets et binaire
clean:
	rm -f $(OBJS) $(TARGET)

# Recompilation complete depuis zero
re: clean all

# Lancement du programme
run: all
	./$(TARGET)

.PHONY: all clean re run
