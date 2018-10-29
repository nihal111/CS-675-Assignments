#include <fstream>
#include <iostream>
using namespace std;

extern int light0, light1;
extern csX75::HNode* lid;

void recorder() {
	ofstream myfile;
	myfile.open ("keyframes.txt", ios::out | ios::app);
	myfile << light0 			<< " " 
		   << light1 			<< " "
		   << lid->get_rx()		<< endl;
	myfile.close();
}
