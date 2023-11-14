APP_NAME = app

CFLAGS = -Wall -Wextra -Werror -O0 -g
CPPFLAGS = -I src -MMD
LFLAGS = -lm
CC = gcc

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

APP_PATH = $(BIN_DIR)/$(APP_NAME)

SRC_EXT = c

APP_SOURCES = $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
APP_OBJECTS := $(patsubst $(SRC_DIR)/%.$(SRC_EXT),$(OBJ_DIR)/%.o,$(APP_SOURCES))

DEPS = $(APP_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LFLAGS)

.PHONY: run
run: all
	./bin/app
	python3 graphic1.py
	python3 graphic2.py
	python3 graphic3.py

.PHONY: clean
clean:
	rm -rf $(APP_OBJECTS)
	rm -rf $(DEPS)
	rm -rf $(APP_PATH)

.PHONY: graphic
graphic:
	python3 graphic1.py
	python3 graphic2.py
	python3 graphic3.py