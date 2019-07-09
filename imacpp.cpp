/*
Copyright 2011 Chris Dyer
Ported from java to c++ by Peter van Kranenburg (peter.van.kranenburg@meertens.knaw.nl)

This file is part of IMACPP.

IMACPP is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

IMACPP is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with IMACPP.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "MetroWeights_Mazzola.h"
#include <iostream>
using namespace std;


int main(int argc, const char* argv[]) {

	vector<int> test;
	test.push_back(0);
	test.push_back(4);
	
	MetroWeights_Mazzola mw(2,2,0,1);
	WeightSet weights = mw.getWeights(test);
	cout << "maximal local meters: " << endl;
	weights.meterCollection.printAll();
	for (int i=0; i<weights.spectralWeight.size(); i++) {
	    cout << weights.spectralWeight[i] << " ";
	}
	cout << endl;
	for (int i=0; i<weights.weights.size(); i++) {
	    cout << weights.weights[i] << " ";
	}
	cout << endl;
}

