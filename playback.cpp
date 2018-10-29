#include <fstream>
#include <iostream>
using namespace std;

extern int light0, light1;
extern bool playback_running;

double startTime = 0.0;
double deltaTime = 0, nowTime = 0;

void playback() {
	ifstream infile("keyframes.txt");
	int a,b;
	while (infile >> a >> b)
	{
	    cout<<a<<" "<<b<<endl;
	}

	glfwSetTime(0);
	playback_running = true;
	cout<<"Set time to 0."<<endl;
}


void playback_update() {
	nowTime = glfwGetTime();
	if (nowTime < 5)
		cout<<glfwGetTime()<<endl;
	else 
		playback_running = false;
}