CC=gcc
CFLAGS=-std=c99
OBJ=levenshtein-distance.o

%.o: %.c 
	$(CC) -c -o $@ $^ $(CFLAGS)

levenshtein-distance: $(OBJ)  
	gcc -o levenshtein-distance levenshtein-distance.o 
