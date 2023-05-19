# Makefile

# A variável $@ representa o alvo (target) da regra (rule). Já a variável $^ representa a lista de pré-requisitos.
# O make não compila todos de uma vez, só o que colocamos depois de make no terminal

#codigo: make bin/(nome que está no main à exceção do .cpp).exe (o nome tem que ser o que está no main. dps vai ver os include desse main e encontrar os ficheiros src e header que lhe estão associados)
SRC = $(wildcard src/*.cpp)
INC = $(wildcard src/*.h)
MAIN = $(wildcard main/*.cpp)
CXX = g++ $(shell root-config --cflags) -I src

ROOTLIB = $(shell root-config --libs)

####################################

SRC_OBJ = $(patsubst %.cpp, bin/%.o, $(notdir $(SRC)))
MAIN_OBJ = $(patsubst %.cpp, bin/%.o, $(notdir $(MAIN)))

bin/%.exe: bin/%.o $(SRC_OBJ)
	@echo "compiling and liking file [ $< ] to $@ "
	$(CXX) $< -o $@ $(SRC_OBJ) $(ROOTLIB)

bin/%.o: src/%.cpp
	@echo "compiling file [ $< ] to $@ "
	$(CXX) -c $< -o $@

bin/%.o: main/%.cpp
	@echo "compiling file [ $< ] to $@ "
	$(CXX) -c $< -o $@

####################################

FTILDE = $(wildcard src/~) $(wildcard main/~)
FBIN = $(wildcard bin/*.o)

clean:
	@echo "cleaning..."
	@rm -fv $(FBIN)

dump: 
	@echo "dump list of src files..."
	@echo $(SRC)
	@echo $(INC)
	@echo $(MAIN)
	@echo $(FTILDE)
	@echo $(FBIN)
	@echo $(CXX)
	@echo $(SRC_OBJ)