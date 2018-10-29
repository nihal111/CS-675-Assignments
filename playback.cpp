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

// Parameters
float last_light0, next_light0;
float last_light1, next_light1;
float last_lid_angle, next_lid_angle;


ifstream infile("keyframes.txt");

void playback_init() {
	glfwSetTime(0);
	playback_running = true;
	cout<<"Set time to 0."<<endl;

	// Init last
	if (infile 
		>> last_light0
		>> last_light1
		>> last_lid_angle
	   ) {
	} else {
		playback_running = false;
	}

	// Init next
	if (infile 
		>> next_light0 
		>> next_light1
		>> next_lid_angle
	   ) {
	} else {
		playback_running = false;
	}
}

void keyframe_read() {
	// Last becomes old next
	last_light0 = next_light0;
	last_light1 = next_light1;
	last_lid_angle = next_lid_angle;

	// Read new next
	if (infile 
		>> next_light0 
		>> next_light1
		>> next_lid_angle
	   ) {
	} else {
		playback_running = false;
	}
}

void update() {
	float light0 = ((FPS - updates)*last_light0 + updates*next_light0)/FPS;
	float light1 = ((FPS - updates)*last_light1 + updates*next_light1)/FPS;
	float lid_angle = ((FPS - updates)*last_lid_angle + updates*next_lid_angle)/FPS;
	switch_lamp_light(light0);
	switch_wall_light(light1);
	box_state(lid_angle);
}

void playback_update() {
	nowTime = glfwGetTime();
	deltaTime += (nowTime - lastTime) * FPS;
	lastTime = nowTime;

	// Only update at defined FPS
	while (deltaTime >= 1.0) {
		update();
		updates++;
		deltaTime--;
	}

	frames++;

	// Reset after one second
	if (glfwGetTime() - keyframeClock > keyframeResolution) {
		keyframeClock += keyframeResolution;
		keyframe_read();
	}

	// Reset after one second
	if (glfwGetTime() - timeSinceStart > 1.0) {
		timeSinceStart ++;
		std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
		updates = 0, frames = 0;
	}
}
