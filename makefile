CC := g++

INC_DIR := include
SRC_DIR := src
OBJECT_DIR := objects
BUILD_DIR := build
TARGET_NAME := gerador-de-trafego

SRCEXT := cpp
HEADEREXT := hpp

SOURCES := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJECTS := $(patsubst $(SRC_DIR)/%,$(OBJECT_DIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall -std=c++17

INC := -I $(INC_DIR) -I libs/args

# Linka todos os objetos e bibliotecas em um binário
$(BUILD_DIR)/$(TARGET_NAME): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $^ -o $(BUILD_DIR)/$(TARGET_NAME) $(LIB)

# Gera todos os objetos
$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# Limpa todos os arquivos que podem ser buildados
clean:
	@$(RM) -r $(OBJECT_DIR)
	@$(RM) -r $(BUILD_DIR)
