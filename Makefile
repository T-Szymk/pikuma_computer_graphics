
PROJ_DIR = $(PWD)
SRC_DIR  = $(PROJ_DIR)/src
BUILD_DIR = $(PROJ_DIR)/build
INC_PATHS = $(PROJ_DIR)/include

SRC_FILES = $(SRC_DIR)/*.c

OUTPUT = $(BUILD_DIR)/renderer.elf

CC       ?= gcc
CC_FLAGS ?= -Wall -Wextra -Wpedantic -std=c99 -O0 -g
CC_LIBS  ?= -lSDL2

init:
	mkdir -p $(BUILD_DIR)

build: init
	$(CC) $(CC_FLAGS) $(SRC_FILES) $(CC_LIBS) -I$(INC_PATHS) -o $(OUTPUT) 

run:
	$(OUTPUT)

clean:
	rm -rf $(BUILD_DIR)
