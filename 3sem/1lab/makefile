APP_NAME = app

CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I src -MMD -lm
CC = g++

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

APP_PATH = $(BIN_DIR)/$(APP_NAME)

SRC_EXT = cpp

APP_SOURCES = $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
APP_OBJECTS := $(patsubst $(SRC_DIR)/%.$(SRC_EXT),$(OBJ_DIR)/%.o,$(APP_SOURCES))

DEPS = $(APP_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: run
run: all
	./bin/app
	python3 ./src/graphic.py

.PHONY: clean
clean:
	rm -rf $(APP_OBJECTS)
	rm -rf $(DEPS)
	rm -rf $(APP_PATH)
	rm -rf ./data/*.csv
	rm -rf ./graphic/*.png