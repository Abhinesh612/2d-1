CC=gcc

# Compiler Flags
CFLAGS=-ggdb
CFLAGS+=$(shell pkg-config --cflags sdl2)

# Libraries
CLIBS=$(shell pkg-config --libs sdl2 gl)
CLIBS+=-lglad -lm -lcglm

# Include Directories
CINCLUDE=./include

# Library Directories
CLIBDIRNAME=lib
CLIBDIR=./$(CLIBDIRNAME)

# Linker Library Path
LD_PATH=$(realpath .)/$(CLIBDIRNAME)

SOURCE_DIR=src
SOURCE_ENGINE=engine
SOURCE_RENDER=render
SOURCE_IO=io
SOURCE=$(wildcard ./$(SOURCE_DIR)/*.c)
SOURCE+=$(wildcard ./$(SOURCE_DIR)/$(SOURCE_ENGINE)/*.c)
SOURCE+=$(wildcard ./$(SOURCE_DIR)/$(SOURCE_ENGINE)/$(SOURCE_RENDER)/*.c)
SOURCE+=$(wildcard ./$(SOURCE_DIR)/$(SOURCE_ENGINE)/$(SOURCE_IO)/*.c)

TARGET=main

.PHONY: all clean

all: build

build: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -I$(CINCLUDE) -L$(CLIBDIR) -Wl,-rpath=$(LD_PATH) $(SOURCE) -o $(TARGET) $(CLIBS)

clean:
	rm $(TARGET)
