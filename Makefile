V=1
SOURCE_DIR=src
BUILD_DIR=build
include $(N64_INST)/include/n64.mk

all: sprite_test.z64
.PHONY: all

SRCS = $(wildcard $(SOURCE_DIR)/*.c)
OBJS = $(SRCS:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)

sprite_test.z64: N64_ROM_TITLE="Sprite Test"
sprite_test.z64: $(BUILD_DIR)/sprite_test.dfs

$(BUILD_DIR)/sprite_test.dfs: $(wildcard filesystem/*)

$(BUILD_DIR)/sprite_test.elf: $(OBJS)

clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)