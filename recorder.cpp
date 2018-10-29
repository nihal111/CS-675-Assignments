#include <fstream>
#include <iostream>
using namespace std;

extern int light0, light1;

void recorder() {
	ofstream myfile;
	myfile.open ("keyframes.txt", ios::out | ios::app);
	myfile << light0 << " " << light1 << endl;
	myfile.close();
}
