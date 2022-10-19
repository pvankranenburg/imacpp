#FLAGS = -O3 -pg
FLAGS = -O3

.DEFAULT_GOAL := all

libIMACPP.a: MeterCollection.cpp MetroWeights_Mazzola.cpp Metrum.cpp OnsetGroup_Memory.cpp
	g++ -c ${FLAGS} -o MeterCollection.o MeterCollection.cpp
	g++ -c ${FLAGS} -o MetroWeights_Mazzola.o MetroWeights_Mazzola.cpp
	g++ -c ${FLAGS} -o Metrum.o Metrum.cpp
	g++ -c ${FLAGS} -o OnsetGroup_Memory.o OnsetGroup_Memory.cpp
	ar rvs libIMACPP.a *.o

imacpp:	libIMACPP.a imacpp.cpp
	g++ -o imacpp imacpp.cpp -L. -lIMACPP

onsets2ima: libIMACPP.a onsets2ima.cpp
	g++ -o onsets2ima onsets2ima.cpp -L. -lIMACPP

all: libIMACPP.a imacpp onsets2ima

clean:
	rm *.o imacpp onsets2ima libIMACPP.a
