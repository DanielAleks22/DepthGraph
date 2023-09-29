CXX=g++ 
C11=--std=c++11
SRC_DIGRAPH= $(wildcard *_digraph.cpp)
SRC_REDUIRE= $(wildcard *_reduire.cpp)
EXEC_DIGRAPH= $(wildcard *_digraph)
EXEC_REDUIRE= $(wildcard *_reduire)

build: $(SRC_DIGRAPH)	$(SRC_REDUIRE)
	$(CXX) $(C11) 01_digraph.cpp -o 01_digraph
	$(CXX) $(C11) 02_digraph.cpp -o 02_digraph
	$(CXX) $(C11) 03_digraph.cpp -o 03_digraph
	$(CXX) $(C11) 04_digraph.cpp -o 04_digraph
	$(CXX) $(C11) 05_digraph.cpp -o 05_digraph
	$(CXX) $(C11) 06_digraph.cpp -o 06_digraph
	$(CXX) $(C11) 07_digraph.cpp -o 07_digraph
	$(CXX) $(C11) 08_digraph.cpp -o 08_digraph
	$(CXX) $(C11) 01_reduire.cpp -o 01_reduire
	$(CXX) $(C11) 02_reduire.cpp -o 02_reduire
	$(CXX) $(C11) 03_reduire.cpp -o 03_reduire
	$(CXX) $(C11) 04_reduire.cpp -o 04_reduire

digraph: $(EXEC_DIGRAPH)
	./01_digraph
	./02_digraph
	./03_digraph
	./04_digraph
	./05_digraph
	./06_digraph tutte_graph tutte_dettes-prets_sommet tutte_sg_1 tutte_sg_2
	./07_digraph regular_graph regular_dettes-prets_sommet regular_sg_1 regular_sg_2
	./08_digraph dorogovtsev_graph dorogovtsev_dettes-prets_sommet dorogovtsev_sg_1 dorogovtsev_sg_2 

reduire: $(EXEC_REDUIRE)
	./01_reduire
	./02_reduire
	./03_reduire complete complete_reduction
	./04_reduire complete complete_reduction_sg

full: digraph reduire

clean:
	rm $(EXEC_DIGRAPH)
	rm $(EXEC_REDUIRE)
