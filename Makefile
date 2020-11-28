CC=g++
LIBS=-lSDL2 -lSDL2_ttf

SRC_DIR := src
OBJ_DIR := $(SRC_DIR)/obj
OUT_DIR := output

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
HEADER_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(SRC_DIR)/%.h,$(SRC_FILES))
OUT_BIN := $(OUT_DIR)/pong

FLAGS := -I$(SRC_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h
	$(CC) -c -o $@ $< $(FLAGS)

$(OUT_BIN): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIBS)

clean: $(OBJ_FILES) $(OUT_BIN)
	rm $^
