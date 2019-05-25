CC = gcc
INC = include
SRC = src
BUILD = build
BIN = bin
INCLUDE = -I ./$(INC)
LIB = `mysql_config --cflags --libs`

TARGET = myclient

OBJECTS = $(BUILD)/main.o $(BUILD)/common.o $(BUILD)/user.o $(BUILD)/course.o

$(BIN)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN)
	@$(CC) -o $@ $^ $(INCLUDE) $(LIB)

$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(BUILD)
	@$(CC) -o $@ -c $^ $(INCLUDE) $(LIB)

run: $(BIN)/$(TARGET)
	@$(BIN)/$(TARGET)

clean:
	@echo "Cleaning..."
	@rm -rf $(BUILD) $(BIN)
