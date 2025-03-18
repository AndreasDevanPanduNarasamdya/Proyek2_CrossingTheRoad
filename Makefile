# Compiler and paths
CC = gcc
RAYLIB_PATH = C:/raylib/raylib
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_PATHS = -I$(RAYLIB_PATH)/include -IC:/raylib/raylib/src
LDFLAGS = -L$(RAYLIB_PATH)/lib -LC:/raylib/raylib/src
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
CFLAGS = -Wall -g
PLATFORM = PLATFORM_DESKTOP
EXT = .exe

# Project target and object files
PROJECT_NAME = main
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/menu.o

# Default target
all: $(PROJECT_NAME)

# Project build target
$(PROJECT_NAME): $(OBJS)
    $(CC) -o $@$(EXT) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
    if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)   # For Windows
    $(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

# Clean build artifacts
clean:
    rm -rf $(OBJ_DIR)/*.o $(PROJECT_NAME)$(EXT)  # Adjust for Windows if needed
    @echo Cleaning done.
