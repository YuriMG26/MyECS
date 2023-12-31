CC = clang++
STD_FLAGS = -std=c++17
CFLAGS = $(STD_FLAGS) -Wno-implicit-exception-spec-mismatch
TARGET_DIR = build
TARGET = $(TARGET_DIR)\\ecs.exe
LIB_FLAGS = -Ivendor/raylib/include 
SRC_DIR := src
SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst %.cpp, %.o, $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp))

ifeq ($(OS),Windows_NT)
	# Comandos para Windows (cmd)
	MKDIR_BUILD =	@if not exist $(TARGET_DIR)\ (mkdir $(TARGET_DIR))
	TARGET = $(TARGET_DIR)\\ecs.exe
	LINK_FLAGS = -lraylib -lopengl32 -lshell32 -lmsvcrt -luser32 -lgdi32 -lwinmm
	LIB_FLAGS += -Lvendor/raylib/lib/windows
	CLEAN_OBJ = @clean_obj.bat
else
	UNAME_S := $(shell uname -s)
	MKDIR_BUILD = if [ ! -d $(TARGET_DIR) ]; then mkdir -p $(TARGET_DIR); fi
	TARGET = $(TARGET_DIR)/ecs
	ifeq ($(UNAME_S),Linux)
		LINK_FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
		LIB_FLAGS += -Lvendor/raylib/lib/linux
	endif
	ifeq ($(UNAME_S),Darwin)
		# $(shell echo "Running on mac")
		LINK_FLAGS = -lraylib
		# LIB_FLAGS += -Lvendor/raylib/lib/mac
	endif
endif

all: $(TARGET)

RAYLIB_DIR := vendor/raylib/include
RAYLIB_SRC = $(wildcard $(RAYLIB_DIR)/*.cpp)
RAYLIB_TARGET := build
RAYLIB_OBJS := $(patsubst $(RAYLIB_DIR)/%.cpp, $(RAYLIB_TARGET)/%.o, $(wildcard $(RAYLIB_DIR)/*.cpp))


$(TARGET): $(RAYLIB_OBJS) $(OBJECTS)
	$(MKDIR_BUILD)
	$(CC) $(CFLAGS) -o $@ $(RAYLIB_TARGET)/*.o $(OBJECTS) $(LIB_FLAGS) $(LINK_FLAGS)

%.o: %.cpp
	$(MKDIR_BUILD)
	$(CC) $(STD_FLAGS) $(CFLAGS) -c -o $@ $< 

$(RAYLIB_TARGET)/%.o: $(RAYLIB_DIR)/%.cpp
	$(MKDIR_BUILD)
	$(CC) $(STD_FLAGS) -c -o $@ $<

clean:
	$(CLEAN_OBJ)
	del $(TARGET)	