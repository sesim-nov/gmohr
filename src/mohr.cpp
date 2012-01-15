#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "stressys.h"
using namespace std;

int main(int argc, char* argv[]) {
double sx, sy, txy;
stressys s1;
if (argc == 4){
	sx = atof(argv[1]);
	sy = atof(argv[2]);
	txy = atof(argv[3]);
	}
else {
	cout << "What is the value of the x-direction tensile stress??\t";
	cin >> sx;
	cout << "What is the value of the y-direction tensile stress??\t";
	cin >> sy;
	cout << "What is the value of the shear stress??\t";
	cin >> txy;
	}
s1.set_params(sx,sy,txy);
s1.mohr();
s1.print_mohr();
cin.get();
return 0;
}
