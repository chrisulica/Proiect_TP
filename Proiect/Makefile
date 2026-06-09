CC = gcc
CFLAGS = -Wall -std=c11
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = main.c tabla.c joc.c mutari.c ai.c
OBJ = $(SRC:.c=.o)
EXEC = simulator_sah

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC)