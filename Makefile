CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb -Wall -Wextra

BIN     := bin
SRC     := src
INCLUDE := include

EXECUTABLE  := sai

MKDIR_P := mkdir -p
OUT_DIR := bin

.PHONY: directories

all: directories $(BIN)/$(EXECUTABLE)

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@

clean:
	-rm -rf $(BIN)/*