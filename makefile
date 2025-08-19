CC = gcc
CFLAGS = -g -Iinclude
BUILD_DIR = build
SRC_DIR = src

# Liste des fichiers sources
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/initialisation.c \
      $(SRC_DIR)/export.c \
      $(SRC_DIR)/display.c \
      $(SRC_DIR)/listeDisciplines.c \
      $(SRC_DIR)/graphMetrics.c \
      $(SRC_DIR)/graph.c

# Objets correspondants dans build/
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

# Nom de l'exécutable (main)
TARGET = $(BUILD_DIR)/main


all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Règle générique pour compiler les .c en .o dans build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crée le dossier build s'il n'existe pas
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Nettoyage
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)
