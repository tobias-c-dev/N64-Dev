V=1
SOURCE_DIR=src
BUILD_DIR=build
include $(N64_INST)/include/n64.mk

all: joypad.z64
.PHONY: all

OBJS = $(BUILD_DIR)/main.o

joypad.z64: N64_ROM_TITLE="Joypad Test"

$(BUILD_DIR)/joypad.elf: $(OBJS)

clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)