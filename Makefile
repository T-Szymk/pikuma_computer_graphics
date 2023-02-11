
PROJ_DIR = $(PWD)
SRC_DIR  = $(PROJ_DIR)/src
BUILD_DIR = $(PROJ_DIR)/build

SRC_FILES = $(SRC_DIR)/*.c

OUTPUT = $(BUILD_DIR)/renderer.elf

CC       ?= gcc
CC_FLAGS ?= -Wall -Wextra -Wpedantic -std=c99

init:
	mkdir -p $(BUILD_DIR)

build: init
	$(CC) $(CC_FLAGS) $(SRC_FILES) -o $(OUTPUT)

run:
	$(OUTPUT)

clean:
	rm -rf $(BUILD_DIR)
