#Makefile for "Laboratorio 01" C++ aplication
#Created by Dionísio Carvalho & Daniel Oliveira

# Comandos do sistema operacional
# Linux: rm -rf
# Windows: cmd //C del
RM = rm -rf

# Compilador
CC = g++

# Variaveis para os subdiretorios
INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./build
BIN_DIR = ./bin
DOC_DIR = ./doc
TEST_DIR = ./test

# Outras variaveis

# Opcoes de compilacao
CFLAGS = -Wall -pedantic -ansi -std=c++11 -I $(INC_DIR)

# Garante que os alvos desta lista nao sejam confundidos com arquivos de mesmo nome
.PHONY: all clean distclean doxy

# Define o alvo (target) para a compilacao completa.
# Ao final da compilacao, remove os arquivos objeto.
all: tarefa1 tarefa2 tarefaextra doxy
debug: CFLAGS += -g -O0
debug: tarefa1 tarefa2 tarefaextra

# Alvo (target) para a construcao do objeto operacoes.o
# Define os arquivos operacoes.cpp e operacoes.h como dependencias.
$(OBJ_DIR)/operacoes.o: $(SRC_DIR)/operacoes.cpp $(INC_DIR)/operacoes.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do objeto arquivos.o
# Define os arquivos arquivos.cpp e arquivos.h como dependencias.
$(OBJ_DIR)/arquivos.o: $(SRC_DIR)/arquivos.cpp $(INC_DIR)/arquivos.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do executavel tarefa1
# Define os arquivos operacoes.o, arquivos.o e tarefa1main.o como dependencias
tarefa1: $(OBJ_DIR)/operacoes.o $(OBJ_DIR)/arquivos.o $(OBJ_DIR)/tarefa1main.o
	@echo "============="
	@echo "Ligando o alvo $@"
	@echo "============="
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^
	@echo "+++ [Executavel tarefa1 criado em $(BIN_DIR)] +++"
	@echo "============="

# Alvo (target) para a construcao do objeto tarefa1main.o
# Define o arquivo tarefa1main.cpp como dependencias.
$(OBJ_DIR)/tarefa1main.o: $(SRC_DIR)/tarefa1main.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do executavel tarefa2
# Define os arquivos operacoes.o, arquivos.o e tarefa2main.o como dependencias
tarefa2: $(OBJ_DIR)/operacoes.o $(OBJ_DIR)/arquivos.o $(OBJ_DIR)/tarefa2main.o
	@echo "============="
	@echo "Ligando o alvo $@"
	@echo "============="
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^
	@echo "+++ [Executavel tarefa2 criado em $(BIN_DIR)] +++"
	@echo "============="

# Alvo (target) para a construcao do objeto tarefa2main.o
# Define o arquivo tarefa2main.cpp como dependencias.
$(OBJ_DIR)/tarefa2main.o: $(SRC_DIR)/tarefa2main.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do executavel tarefaextra
# Define os arquivos operacoes.o, arquivos.o e tarefaextramain.o como dependencias
tarefaextra: $(OBJ_DIR)/operacoes.o $(OBJ_DIR)/arquivos.o $(OBJ_DIR)/tarefaextramain.o
	@echo "============="
	@echo "Ligando o alvo $@"
	@echo "============="
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^
	@echo "+++ [Executavel tarefaextra criado em $(BIN_DIR)] +++"
	@echo "============="

# Alvo (target) para a construcao do objeto tarefaextramain.o
# Define o arquivo tarefaextramain.cpp como dependencias.
$(OBJ_DIR)/tarefaextramain.o: $(SRC_DIR)/tarefaextramain.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a geração automatica de documentacao usando o Doxygen.
# Sempre remove a documentacao anterior (caso exista) e gera uma nova.
doxy:
	$(RM) $(DOC_DIR)/*
	doxygen Doxyfile

# Alvo (target) usado para limpar os arquivos temporarios (objeto)
# gerados durante a compilacao, assim como os arquivos binarios/executaveis.
clean:
	$(RM) $(BIN_DIR)/*
	$(RM) $(OBJ_DIR)/*
