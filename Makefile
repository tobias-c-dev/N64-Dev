V=1
SOURCE_DIR=src
BUILD_DIR=build
include $(N64_INST)/include/n64.mk

all: dfs_test.z64
.PHONY: all

SRCS = $(wildcard $(SOURCE_DIR)/*.c)
OBJS = $(SRCS:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)

dfs_test.z64: N64_ROM_TITLE="DFS Test"
dfs_test.z64: $(BUILD_DIR)/dfs_test.dfs

$(BUILD_DIR)/dfs_test.dfs: $(wildcard filesystem/*)

$(BUILD_DIR)/dfs_test.elf: $(OBJS)

clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)