CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

RAYLIB_PATH = D:/Apps/raylib/raylib-5.0_win64_mingw-w64
INCLUDE_DIR = -I$(RAYLIB_PATH)/include
LIB_DIR = -L$(RAYLIB_PATH)/lib

LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

TARGET = joc_sah
SRCS = main.c tabla.c joc.c mutari.c ai.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -o $(TARGET) $(OBJS) $(LIB_DIR) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

clean: 
	rm -f $(OBJS) $(TARGET).exe