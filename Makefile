SRC = src
INC = include
OBJ = obj
LIB = lib
BIN = bin
CXX = g++
AR = ar rvs
AR_MACOSX = libtool -static -o
CPPFLAGS = -Wall -g  -I$(INC) -c



all: $(BIN)/conecta4
# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

$(BIN)/conecta4: $(SRC)/conecta4.cpp $(INC)/conecta4.h $(SRC)/metricas.cpp $(INC)/metricas.h
	$(CXX) $(SRC)/tablero.cpp $(SRC)/metricas.cpp $(SRC)/conecta4.cpp $(SRC)/mando.cpp $(SRC)/main.cpp -I$(INC) -o $(BIN)/main -std=c++14

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(LIB)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
