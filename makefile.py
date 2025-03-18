# Auto-generate a Makefile for a basic C project
project_name = "main"
src_files = ["main.c", "Assets/lib/andreas/LibraryAndrew.c", "Assets/lib/azzam/LibraryAzzam.c",
             "Assets/lib/faiz/LibraryFaiz.c", "Assets/lib/fahraj/sfx.c", "Assets/lib/hakim/menu.c",
             "Assets/lib/hakim/options.c"]
obj_files = [f.replace(".c", ".o") for f in src_files]
raylib_path = "C:/raylib/raylib"
compiler = "gcc"

with open("Makefile", "w") as f:
    f.write(f"# Auto-generated Makefile\n")
    f.write(f"CC = {compiler}\n")
    f.write(f"RAYLIB_PATH = {raylib_path}\n")
    f.write(f"LDFLAGS = -L$(RAYLIB_PATH)/lib -LC:/raylib/raylib/src\n")
    f.write(f"LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm\n")
    f.write(f"CFLAGS = -Wall -g\n")
    f.write(f"OBJ_FILES = {' '.join(obj_files)}\n\n")

    f.write(f"all: {project_name}.exe\n\n")
    f.write(f"{project_name}.exe: $(OBJ_FILES)\n")
    f.write(f"\t$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)\n\n")

    f.write(f"%.o: %.c\n")
    f.write(f"\t$(CC) -c $< -o $@ $(CFLAGS)\n\n")

    f.write(f"clean:\n")
    f.write(f"\trm -f *.o {project_name}.exe\n")
