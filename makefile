CC=g++
FLAGS=-std=c++11
INCLUDE=-Iinclude

SRC=src
MAIN_SRC=$(wildcard $(SRC)/*.cpp)

TARGET=bin
EXE=$(TARGET)/continuous_dropout

OBJ_TARGET=obj
MAIN_OBJ=$(patsubst $(SRC)/%.cpp, $(OBJ_TARGET)/%.o, $(MAIN_SRC))

default: all

all: $(EXE)

$(EXE): $(TARGET) $(MAIN_OBJ)
	$(CC) $(FLAGS) -o $(EXE) $(MAIN_OBJ)

$(TARGET):
	mkdir $@

$(OBJ_TARGET)/%.o: $(OBJ_TARGET) $(SRC)/%.cpp
	$(CC) -c $(FLAGS) $(INCLUDE) -o $@ $(patsubst $(OBJ_TARGET)/%.o, $(SRC)/%.cpp, $@)

$(OBJ_TARGET):
	mkdir $@

clean:
	rm -f *.o *.out *.gch $(EXE) $(MAIN_OBJ)
