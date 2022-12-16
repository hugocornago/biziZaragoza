###############################################################################################
## Fichero «Makefile» para los programas de la práctica 6 y el trabajo:
## «datos-pruebas» y «bizi»
###############################################################################################

###############################################################################################
## Declaracion de variables del fichero «Makefile»

## DIRECTORIOS
SOURCE_DIR = src
BUILD_DIR = build
BIN_DIR = bin

VPATH = $(SOURCE_DIR) 

## COMPILADOR Y OPCIONES DE COMPILACIÓN:
CXX = g++
CXXFLAGS = -g -Wall -Wextra 


## FICHEROS OBJETO (RESULTADOS INTERMEDIOS DE COMPILACIÓN):
DATOS_PRUEBAS_OBJECTS =  $(SOURCE_DIR)/0-datos-pruebas.cpp
BIZI_OBJECTS =  $(addprefix $(BUILD_DIR)/, bizi-main.o estacion.o nombres-ficheros.o uso.o \
                                           usos-usuario.o usuarios.o)

###############################################################################################
## Reglas del fichero «Makefile»

bizi: $(BIZI_OBJECTS) | $(BIN_DIR)
	$(CXX) -g $^ -o $(BIN_DIR)/$@ 

datos-pruebas: $(DATOS_PRUEBAS_OBJECTS) | $(BIN_DIR)
	$(CXX) -g $^ -o $(BIN_DIR)/$@ 

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@  

$(BUILD_DIR)/bizi-main.o: estacion.hpp nombres-ficheros.hpp uso.hpp usos-usuario.hpp usuarios.hpp
$(BUILD_DIR)/estacion.o: estacion.hpp nombres-ficheros.hpp uso.hpp
$(BUILD_DIR)/nombres-ficheros.o: nombres-ficheros.hpp
$(BUILD_DIR)/uso.o: uso.hpp
$(BUILD_DIR)/usos-usuario.o: uso.hpp usos-usuario.hpp
$(BUILD_DIR)/usuarios.o: usuarios.hpp


$(BIN_DIR):
	mkdir $(BIN_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
ifeq ($(OS),Windows_NT)
	if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)
	if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
else
	rm -f $(DATOS_PRUEBAS_OBJECTS) $(CONTAR_USOS_OBJECTS) $(USOS_POR_USUARIO_OBJECTS) $(BIN_DIR)/*
endif
