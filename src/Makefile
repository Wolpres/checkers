CC=g++
CFLAGS=-Wall -Wextra -pedantic -lsfml-graphics -lsfml-system -lsfml-window
FILES=main.o

%o: %cpp
	$(CC) $(CFLAGS) -c $(FILES)

all: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o dama

clear:
	$(RM) $(FILES) dama
