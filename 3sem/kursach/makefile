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

.PHONY: clean
clean:
	rm -rf $(APP_OBJECTS)
	rm -rf $(DEPS)
	rm -rf $(APP_PATH)
	rm -rf ./graphic/*.png
	rm -rf ./experimental_data/*.txt

.PHONY: graphic
graphic:
	python3 python_script/random_lookup_time_sorted.py
	python3 python_script/random_lookup_time_random.py
	python3 python_script/last_lookup_time_sorted.py
	python3 python_script/last_lookup_time_random.py
	python3	python_script/deleting_from_last_time_random.py
	python3 python_script/deleting_from_last_time_sorted.py
	python3 python_script/random_insertion_time.py
	python3 python_script/sorted_insertion_time.py