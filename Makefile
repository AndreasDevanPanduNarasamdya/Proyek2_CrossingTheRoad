# Auto-generated Makefile
CC = gcc
RAYLIB_PATH = C:/raylib/raylib
LDFLAGS = -L$(RAYLIB_PATH)/lib -LC:/raylib/raylib/src
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
CFLAGS = -Wall -g
OBJ_FILES = main.o Assets/lib/andreas/LibraryAndrew.o Assets/lib/azzam/LibraryAzzam.o Assets/lib/faiz/LibraryFaiz.o Assets/lib/fahraj/sfx.o Assets/lib/hakim/menu.o Assets/lib/hakim/options.o

all: main.exe

main.exe: $(OBJ_FILES)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o main.exe
