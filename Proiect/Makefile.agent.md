CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

TARGET = joc_sah

SRCS = main.c tabla.c joc.c mutari.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)
$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean: 
    rm -f $(OBJS) $(TARGET)