#include <fstream>
#include <iostream>
using namespace std;

extern int light0, light1;
extern bool playback_running;

double startTime = 0.0, timeSinceStart = 0.0;
double deltaTime = 0, nowTime = 0, lastTime = 0;
int frames = 0 , updates = 0;

int FPS = 25;

double keyframeClock = 0.0;
double keyframeResolution = 1.0;

ifstream infile("keyframes.txt");

void playback() {
	glfwSetTime(0);
	playback_running = true;
	cout<<"Set time to 0."<<endl;
}

void update() {
	int light0, light1, lid_angle;
	if (infile 
		>> light0 
		>> light1
		>> lid_angle
	   ) {
		// cout<<light0<<" "<<light1<<" "<<lid_angle<<endl;
		switch_lamp_light(light0);
		switch_wall_light(light1);
		box_state(lid_angle);
	} else {
		playback_running = false;
	}
}

void playback_update() {
	nowTime = glfwGetTime();
	deltaTime += (nowTime - lastTime) * FPS;
	lastTime = nowTime;

	// Only update at defined FPS
	while (deltaTime >= 1.0) {
		// update();
		updates++;
		deltaTime--;
	}

	frames++;

	// Reset after one second
	if (glfwGetTime() - keyframeClock > keyframeResolution) {
		keyframeClock += keyframeResolution;
		update();
	}

	// Reset after one second
	if (glfwGetTime() - timeSinceStart > 1.0) {
		timeSinceStart ++;
		std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
		updates = 0, frames = 0;
	}
}
