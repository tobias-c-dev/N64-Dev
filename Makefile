V=1
SOURCE_DIR=src
BUILD_DIR=build
include $(N64_INST)/include/n64.mk

all: display_test.z64
.PHONY: all

OBJS = $(BUILD_DIR)/main.o

display_test.z64: N64_ROM_TITLE="Display Test"
display_test.z64: $(BUILD_DIR)/display_test.dfs

$(BUILD_DIR)/display_test.dfs: $(wildcard filesystem/*)

$(BUILD_DIR)/display_test.elf: $(OBJS)

clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)