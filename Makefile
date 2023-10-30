CC = clang++
CFLAGS = -std=c++20
TARGET_DIR = build
TARGET = $(TARGET_DIR)\\ecs.exe
LIB_FLAGS = -Ivendor/raylib/include -Lvendor/raylib/lib
LINK_FLAGS = -lraylib -lopengl32 -lshell32 -lmsvcrt -luser32 -lgdi32 -lwinmm

OBJECTS = Entry.o Application.o Logger.o Game.o GameObject.o SimpleEntity.o

ifeq ($(OS),Windows_NT)
	# Comandos para Windows (cmd)
	MKDIR_BUILD =	@if not exist $(TARGET_DIR)\ (mkdir $(TARGET_DIR))
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		MKDIR_BUILD = if [ ! -d $(TARGET_DIR) ]; then mkdir -p $(TARGET_DIR); fi
	endif
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(MKDIR_BUILD)
	$(CC) $(CFLAGS) -g -o $(TARGET) $(LIB_FLAGS) $(OBJECTS) $(LINK_FLAGS)

Entry.o: src/Entry.cpp
	$(CC) $(CFLAGS) -g -c src/Entry.cpp

Application.o: src/Application.cpp
	$(CC) $(CFLAGS) -g -c src/Application.cpp

Logger.o: src/Logger.cpp
	$(CC) $(CFLAGS) -g -c src/Logger.cpp

Game.o: src/Game.cpp
	$(CC) $(CFLAGS) -g -c src/Game.cpp

GameObject.o: src/GameObject.cpp
	$(CC) $(CFLAGS) -g -c src/GameObject.cpp

SimpleEntity.o: src/game/SimpleEntity.cpp
	$(CC) $(CFLAGS) -g -c src/game/SimpleEntity.cpp

clean-obj:
	del *.o

clean:
	del $(TARGET)	