#FLAGS = -O3 -pg
FLAGS = -O3

all:
	g++ -c ${FLAGS} -o MeterCollection.o MeterCollection.cpp
	g++ -c ${FLAGS} -o MetroWeights_Mazzola.o MetroWeights_Mazzola.cpp
	g++ -c ${FLAGS} -o Metrum.o Metrum.cpp
	g++ -c ${FLAGS} -o OnsetGroup_Memory.o OnsetGroup_Memory.cpp
	g++ -o imacpp imacpp.cpp MeterCollection.o MetroWeights_Mazzola.o Metrum.o OnsetGroup_Memory.o
	ar rvs libIMACPP.a *.o

imacpp:	all
	g++ -o imacpp imacpp.cpp -L. -lIMACPP
	
clean:
	rm *.o imacpp libIMACPP.a
