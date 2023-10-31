CC = clang++
CFLAGS = -std=c++20 -Wno-implicit-exception-spec-mismatch
TARGET_DIR = build
TARGET = $(TARGET_DIR)\\ecs.exe
LIB_FLAGS = -Ivendor/raylib/include -Lvendor/raylib/lib
SRC_DIR := src
SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst %.cpp, %.o, $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp))

ifeq ($(OS),Windows_NT)
	# Comandos para Windows (cmd)
	MKDIR_BUILD =	@if not exist $(TARGET_DIR)\ (mkdir $(TARGET_DIR))
	TARGET = $(TARGET_DIR)\\ecs.exe
	LINK_FLAGS = -lraylib -lopengl32 -lshell32 -lmsvcrt -luser32 -lgdi32 -lwinmm
	CLEAN_OBJ = @clean_obj.bat
else
	UNAME_S := $(shell uname -s)
	MKDIR_BUILD = if [ ! -d $(TARGET_DIR) ]; then mkdir -p $(TARGET_DIR); fi
	TARGET = $(TARGET_DIR)/ecs
	ifeq ($(UNAME_S),Linux)
		LINK_FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	endif
	ifeq ($(UNAME_S),Darwin)
		LINK_FLAGS = -lraylib
	endif
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(MKDIR_BUILD)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIB_FLAGS) $(LINK_FLAGS)

# Regra genérica para compilar arquivos .cpp em arquivos .o
%.o: %.cpp
	$(MKDIR_BUILD)
	$(CC) $(CFLAGS) -c -o $@ $< 

clean:
	$(CLEAN_OBJ)
	del $(TARGET)	