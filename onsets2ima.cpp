/*
Copyright 2022 by Peter van Kranenburg (peter.van.kranenburg@meertens.knaw.nl)

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
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<double> getNormalizedIMA(vector<int> onsets, bool spectral = false) {

	MetroWeights_Mazzola mw(2,2,0,1);
	WeightSet weights = mw.getWeights(onsets);
    vector<int> target_weights;

    if(spectral)
        target_weights = weights.spectralWeight;
    else
        target_weights = weights.weights;

	vector<double> normalzied_weights;
	int maxw = 0;
	for(int i=0; i<target_weights.size(); i++)
		if ( target_weights[i] > maxw ) maxw = target_weights[i];

	// if no local meters at all
	if ( maxw == 0 ) maxw = 1;

	for(int i=0; i<target_weights.size(); i++)
		normalzied_weights.push_back((double)target_weights[i] / (double)maxw);
	return normalzied_weights;
}

int main(int argc, const char* argv[]) {

    //read file with onsets (one series of onsets per line)

    ifstream infile;
    ofstream outfile, outfile_spect;
    string infile_name, outfile_name, outfile_spect_name;

    if (argc != 4 || string(argv[1]) == "-help") {
        cout << "Usage: onset2ima <infile> <outfile> <outfile_spect>" << endl;
        cout << "infile contains space separated onsets (int). One series of onsets per line." << endl;
        cout << "outfile will contain ima weights. One weight for each onset." << endl;
        cout << "outfile_spect will contain ima spectral weights. One weight for each onset." << endl;
        exit(0);
    }

	infile_name = string(argv[1]);
	outfile_name = string(argv[2]);
    outfile_spect_name = string(argv[3]);

    infile.open(infile_name);
    outfile.open(outfile_name);
    outfile_spect.open(outfile_spect_name);

    string line;
    vector<int> onsets;
    vector<double> ima;
    vector<double> ima_spect;

    while (getline(infile, line))
    {
        onsets.clear();
        ima.clear();
        ima_spect.clear();

        int onset;
        stringstream l( line );
        while(l >> onset)  //read as long as there is integer
        onsets.push_back(onset);

        ima = getNormalizedIMA(onsets, false);
        ima_spect = getNormalizedIMA(onsets, true);

        for (int i=0; i<ima.size(); i++) {
            outfile << ima[i] << " ";
        }
        outfile << endl;

        for (int i=0; i<ima_spect.size(); i++) {
            outfile_spect << ima_spect[i] << " ";
        }
        outfile_spect << endl;

    }

    infile.close();
    outfile.close();
    outfile_spect.close();

    return 0;

}