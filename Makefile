CC      = gcc
CFLAGS  = -Wall -Wextra -O2
LIBS    = -lm
TARGET  = uav
SRCS    = main.c fichier.c
OBJS    = main.o fichier.o

# Compilation complete
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

main.o: main.c fichier.h
	$(CC) $(CFLAGS) -c main.c

fichier.o: fichier.c fichier.h
	$(CC) $(CFLAGS) -c fichier.c

# Nettoyage des fichiers objets et binaire
clean:
	rm -f $(OBJS) $(TARGET)

# Recompilation complete depuis zero
re: clean all

# Lancement du programme
run: all
	./$(TARGET)

.PHONY: all clean re run
