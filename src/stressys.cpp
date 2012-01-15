#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdio>
#include "stressys.h"
using namespace std;

void stressys::set_params(double sxo, double syo, double txyo) {
	sx = sxo;
	sy = syo;
	txy = txyo;
	}

void stressys::mohr(){
	C = (sx+sy)/2.0;
	R = sqrt(pow((sx-C),2)+pow(txy,2));
	s1 = C+R;
	s2 = C-R;
	}

void stressys::print_mohr(){
	cout    << "***********************************************" << endl
		<< "*          Mohr's Circle Calculations         *" << endl
		<< "***********************************************" << endl << endl
		<< left << setw(35) << "Circle Radius:" << R << endl
		<< setw(35) << "Circle Center:" << C << endl
		<< setw (35) << "First Principal Stress:" << s1 << endl
		<< setw(35 ) << "Second Principal Stress:" << s2 << endl;
	}
