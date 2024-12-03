# Definindo o compilador e as flags de compilação
CXX = g++
CXXFLAGS = -Wall -std=c++11 -I/usr/include/GL

# Flags para linkar com as bibliotecas GLUT e OpenGL
LDFLAGS = -lGL -lGLU -lglut

# Diretórios dos arquivos de código-fonte e arquivos de destino
SRC_DIR = .
OBJ_DIR = ./obj
BIN_DIR = ./bin

# Arquivos fonte
SRC_FILES = $(SRC_DIR)/inimigo.cpp $(SRC_DIR)/torre.cpp $(SRC_DIR)/main.cpp $(SRC_DIR)/graphics.cpp $(SRC_DIR)/game.cpp

# Arquivos objeto
OBJ_FILES = $(OBJ_DIR)/inimigo.o $(OBJ_DIR)/torre.o $(OBJ_DIR)/main.o $(OBJ_DIR)/graphics.o $(OBJ_DIR)/game.o

# Nome do executável
EXEC = $(BIN_DIR)/jogo

# Alvo padrão: compilar e gerar o executável
all: $(EXEC)

# Como gerar o executável
$(EXEC): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)  # Cria o diretório bin se não existir
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ_FILES) $(LDFLAGS)

# Regras para compilar os arquivos fonte
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)  # Cria o diretório obj se não existir
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Alvo para limpar os arquivos objetos e o executável
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Alvo para rodar o programa compilado
run: $(EXEC)
	$(EXEC)

# Definindo as dependências dos arquivos objeto
$(OBJ_DIR)/inimigo.o: $(SRC_DIR)/inimigo.cpp $(SRC_DIR)/inimigo.h
$(OBJ_DIR)/torre.o: $(SRC_DIR)/torre.cpp $(SRC_DIR)/torre.h
$(OBJ_DIR)/graphics.o: $(SRC_DIR)/graphics.cpp $(SRC_DIR)/graphics.h
$(OBJ_DIR)/game.o: $(SRC_DIR)/game.cpp $(SRC_DIR)/game.h
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/inimigo.h $(SRC_DIR)/torre.h

.PHONY: all clean run
