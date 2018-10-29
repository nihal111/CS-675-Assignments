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

// Parameters
float last_light0, next_light0;
float last_light1, next_light1;
float last_lid_angle, next_lid_angle;

float last_torso_tx, next_torso_tx;
float last_torso_ty, next_torso_ty;
float last_torso_tz, next_torso_tz;
float last_torso_rx, next_torso_rx;
float last_torso_ry, next_torso_ry;
float last_torso_rz, next_torso_rz;

float last_left_upper_arm_tx, next_left_upper_arm_tx;
float last_left_upper_arm_ty, next_left_upper_arm_ty;
float last_left_upper_arm_tz, next_left_upper_arm_tz;
float last_left_upper_arm_rx, next_left_upper_arm_rx;
float last_left_upper_arm_ry, next_left_upper_arm_ry;
float last_left_upper_arm_rz, next_left_upper_arm_rz;
float last_left_lower_arm_tx, next_left_lower_arm_tx;
float last_left_lower_arm_ty, next_left_lower_arm_ty;
float last_left_lower_arm_tz, next_left_lower_arm_tz;
float last_left_lower_arm_rx, next_left_lower_arm_rx;
float last_left_lower_arm_ry, next_left_lower_arm_ry;
float last_left_lower_arm_rz, next_left_lower_arm_rz;
float last_right_upper_arm_tx, next_right_upper_arm_tx;
float last_right_upper_arm_ty, next_right_upper_arm_ty;
float last_right_upper_arm_tz, next_right_upper_arm_tz;
float last_right_upper_arm_rx, next_right_upper_arm_rx;
float last_right_upper_arm_ry, next_right_upper_arm_ry;
float last_right_upper_arm_rz, next_right_upper_arm_rz;
float last_right_lower_arm_tx, next_right_lower_arm_tx;
float last_right_lower_arm_ty, next_right_lower_arm_ty;
float last_right_lower_arm_tz, next_right_lower_arm_tz;
float last_right_lower_arm_rx, next_right_lower_arm_rx;
float last_right_lower_arm_ry, next_right_lower_arm_ry;
float last_right_lower_arm_rz, next_right_lower_arm_rz;
float last_left_upper_leg_tx, next_left_upper_leg_tx;
float last_left_upper_leg_ty, next_left_upper_leg_ty;
float last_left_upper_leg_tz, next_left_upper_leg_tz;
float last_left_upper_leg_rx, next_left_upper_leg_rx;
float last_left_upper_leg_ry, next_left_upper_leg_ry;
float last_left_upper_leg_rz, next_left_upper_leg_rz;
float last_left_lower_leg_tx, next_left_lower_leg_tx;
float last_left_lower_leg_ty, next_left_lower_leg_ty;
float last_left_lower_leg_tz, next_left_lower_leg_tz;
float last_left_lower_leg_rx, next_left_lower_leg_rx;
float last_left_lower_leg_ry, next_left_lower_leg_ry;
float last_left_lower_leg_rz, next_left_lower_leg_rz;
float last_right_upper_leg_tx, next_right_upper_leg_tx;
float last_right_upper_leg_ty, next_right_upper_leg_ty;
float last_right_upper_leg_tz, next_right_upper_leg_tz;
float last_right_upper_leg_rx, next_right_upper_leg_rx;
float last_right_upper_leg_ry, next_right_upper_leg_ry;
float last_right_upper_leg_rz, next_right_upper_leg_rz;
float last_right_lower_leg_tx, next_right_lower_leg_tx;
float last_right_lower_leg_ty, next_right_lower_leg_ty;
float last_right_lower_leg_tz, next_right_lower_leg_tz;
float last_right_lower_leg_rx, next_right_lower_leg_rx;
float last_right_lower_leg_ry, next_right_lower_leg_ry;
float last_right_lower_leg_rz, next_right_lower_leg_rz;
float last_r2d2_left_arm_tx, next_r2d2_left_arm_tx;
float last_r2d2_left_arm_ty, next_r2d2_left_arm_ty;
float last_r2d2_left_arm_tz, next_r2d2_left_arm_tz;
float last_r2d2_left_arm_rx, next_r2d2_left_arm_rx;
float last_r2d2_left_arm_ry, next_r2d2_left_arm_ry;
float last_r2d2_left_arm_rz, next_r2d2_left_arm_rz;
float last_r2d2_right_arm_tx, next_r2d2_right_arm_tx;
float last_r2d2_right_arm_ty, next_r2d2_right_arm_ty;
float last_r2d2_right_arm_tz, next_r2d2_right_arm_tz;
float last_r2d2_right_arm_rx, next_r2d2_right_arm_rx;
float last_r2d2_right_arm_ry, next_r2d2_right_arm_ry;
float last_r2d2_right_arm_rz, next_r2d2_right_arm_rz;

float last_r2d2_body_tx, next_r2d2_body_tx;
float last_r2d2_body_ty, next_r2d2_body_ty;
float last_r2d2_body_tz, next_r2d2_body_tz;
float last_r2d2_body_rx, next_r2d2_body_rx;
float last_r2d2_body_ry, next_r2d2_body_ry;
float last_r2d2_body_rz, next_r2d2_body_rz;


bool load_last() {
	return (infile 
		>> last_light0
		>> last_light1
		>> last_lid_angle

		>> last_torso_tx
		>> last_torso_ty
		>> last_torso_tz
		>> last_torso_rx
		>> last_torso_ry
		>> last_torso_rz

		>> last_left_upper_arm_tx
		>> last_left_upper_arm_ty
		>> last_left_upper_arm_tz
		>> last_left_upper_arm_rx
		>> last_left_upper_arm_ry
		>> last_left_upper_arm_rz

		>> last_left_lower_arm_tx
		>> last_left_lower_arm_ty
		>> last_left_lower_arm_tz
		>> last_left_lower_arm_rx
		>> last_left_lower_arm_ry
		>> last_left_lower_arm_rz

		>> last_right_upper_arm_tx
		>> last_right_upper_arm_ty
		>> last_right_upper_arm_tz
		>> last_right_upper_arm_rx
		>> last_right_upper_arm_ry
		>> last_right_upper_arm_rz

		>> last_right_lower_arm_tx
		>> last_right_lower_arm_ty
		>> last_right_lower_arm_tz
		>> last_right_lower_arm_rx
		>> last_right_lower_arm_ry
		>> last_right_lower_arm_rz

		>> last_left_upper_leg_tx
		>> last_left_upper_leg_ty
		>> last_left_upper_leg_tz
		>> last_left_upper_leg_rx
		>> last_left_upper_leg_ry
		>> last_left_upper_leg_rz

		>> last_left_lower_leg_tx
		>> last_left_lower_leg_ty
		>> last_left_lower_leg_tz
		>> last_left_lower_leg_rx
		>> last_left_lower_leg_ry
		>> last_left_lower_leg_rz

		>> last_right_upper_leg_tx
		>> last_right_upper_leg_ty
		>> last_right_upper_leg_tz
		>> last_right_upper_leg_rx
		>> last_right_upper_leg_ry
		>> last_right_upper_leg_rz

		>> last_right_lower_leg_tx
		>> last_right_lower_leg_ty
		>> last_right_lower_leg_tz
		>> last_right_lower_leg_rx
		>> last_right_lower_leg_ry
		>> last_right_lower_leg_rz

		>> last_r2d2_left_arm_tx
		>> last_r2d2_left_arm_ty
		>> last_r2d2_left_arm_tz
		>> last_r2d2_left_arm_rx
		>> last_r2d2_left_arm_ry
		>> last_r2d2_left_arm_rz

		>> last_r2d2_right_arm_tx
		>> last_r2d2_right_arm_ty
		>> last_r2d2_right_arm_tz
		>> last_r2d2_right_arm_rx
		>> last_r2d2_right_arm_ry
		>> last_r2d2_right_arm_rz

		>> last_r2d2_body_tx
		>> last_r2d2_body_ty
		>> last_r2d2_body_tz
		>> last_r2d2_body_rx
		>> last_r2d2_body_ry
		>> last_r2d2_body_rz);
}

bool load_next() {
	return (infile 
		>> next_light0
		>> next_light1
		>> next_lid_angle

		>> next_torso_tx
		>> next_torso_ty
		>> next_torso_tz
		>> next_torso_rx
		>> next_torso_ry
		>> next_torso_rz

		>> next_left_upper_arm_tx
		>> next_left_upper_arm_ty
		>> next_left_upper_arm_tz
		>> next_left_upper_arm_rx
		>> next_left_upper_arm_ry
		>> next_left_upper_arm_rz

		>> next_left_lower_arm_tx
		>> next_left_lower_arm_ty
		>> next_left_lower_arm_tz
		>> next_left_lower_arm_rx
		>> next_left_lower_arm_ry
		>> next_left_lower_arm_rz

		>> next_right_upper_arm_tx
		>> next_right_upper_arm_ty
		>> next_right_upper_arm_tz
		>> next_right_upper_arm_rx
		>> next_right_upper_arm_ry
		>> next_right_upper_arm_rz

		>> next_right_lower_arm_tx
		>> next_right_lower_arm_ty
		>> next_right_lower_arm_tz
		>> next_right_lower_arm_rx
		>> next_right_lower_arm_ry
		>> next_right_lower_arm_rz

		>> next_left_upper_leg_tx
		>> next_left_upper_leg_ty
		>> next_left_upper_leg_tz
		>> next_left_upper_leg_rx
		>> next_left_upper_leg_ry
		>> next_left_upper_leg_rz

		>> next_left_lower_leg_tx
		>> next_left_lower_leg_ty
		>> next_left_lower_leg_tz
		>> next_left_lower_leg_rx
		>> next_left_lower_leg_ry
		>> next_left_lower_leg_rz

		>> next_right_upper_leg_tx
		>> next_right_upper_leg_ty
		>> next_right_upper_leg_tz
		>> next_right_upper_leg_rx
		>> next_right_upper_leg_ry
		>> next_right_upper_leg_rz

		>> next_right_lower_leg_tx
		>> next_right_lower_leg_ty
		>> next_right_lower_leg_tz
		>> next_right_lower_leg_rx
		>> next_right_lower_leg_ry
		>> next_right_lower_leg_rz

		>> next_r2d2_left_arm_tx
		>> next_r2d2_left_arm_ty
		>> next_r2d2_left_arm_tz
		>> next_r2d2_left_arm_rx
		>> next_r2d2_left_arm_ry
		>> next_r2d2_left_arm_rz

		>> next_r2d2_right_arm_tx
		>> next_r2d2_right_arm_ty
		>> next_r2d2_right_arm_tz
		>> next_r2d2_right_arm_rx
		>> next_r2d2_right_arm_ry
		>> next_r2d2_right_arm_rz

		>> next_r2d2_body_tx
		>> next_r2d2_body_ty
		>> next_r2d2_body_tz
		>> next_r2d2_body_rx
		>> next_r2d2_body_ry
		>> next_r2d2_body_rz);
}

void update() {
	float light0 = ((FPS - updates)*last_light0 + updates*next_light0)/FPS;
	float light1 = ((FPS - updates)*last_light1 + updates*next_light1)/FPS;
	float lid_angle = ((FPS - updates)*last_lid_angle + updates*next_lid_angle)/FPS;
	float torso_tx = ((FPS - updates)*last_torso_tx + updates*next_torso_tx)/FPS;
	float torso_ty = ((FPS - updates)*last_torso_ty + updates*next_torso_ty)/FPS;
	float torso_tz = ((FPS - updates)*last_torso_tz + updates*next_torso_tz)/FPS;
	float torso_rx = ((FPS - updates)*last_torso_rx + updates*next_torso_rx)/FPS;
	float torso_ry = ((FPS - updates)*last_torso_ry + updates*next_torso_ry)/FPS;
	float torso_rz = ((FPS - updates)*last_torso_rz + updates*next_torso_rz)/FPS;
	float r2d2_body_tx = ((FPS - updates)*last_r2d2_body_tx + updates*next_r2d2_body_tx)/FPS;
	float r2d2_body_ty = ((FPS - updates)*last_r2d2_body_ty + updates*next_r2d2_body_ty)/FPS;
	float r2d2_body_tz = ((FPS - updates)*last_r2d2_body_tz + updates*next_r2d2_body_tz)/FPS;
	float r2d2_body_rx = ((FPS - updates)*last_r2d2_body_rx + updates*next_r2d2_body_rx)/FPS;
	float r2d2_body_ry = ((FPS - updates)*last_r2d2_body_ry + updates*next_r2d2_body_ry)/FPS;
	float r2d2_body_rz = ((FPS - updates)*last_r2d2_body_rz + updates*next_r2d2_body_rz)/FPS;

	float left_upper_arm_tx = ((FPS - updates)*last_left_upper_arm_tx + updates*next_left_upper_arm_tx)/FPS;
	float left_upper_arm_ty = ((FPS - updates)*last_left_upper_arm_ty + updates*next_left_upper_arm_ty)/FPS;
	float left_upper_arm_tz = ((FPS - updates)*last_left_upper_arm_tz + updates*next_left_upper_arm_tz)/FPS;
	float left_upper_arm_rx = ((FPS - updates)*last_left_upper_arm_rx + updates*next_left_upper_arm_rx)/FPS;
	float left_upper_arm_ry = ((FPS - updates)*last_left_upper_arm_ry + updates*next_left_upper_arm_ry)/FPS;
	float left_upper_arm_rz = ((FPS - updates)*last_left_upper_arm_rz + updates*next_left_upper_arm_rz)/FPS;

	float left_lower_arm_tx = ((FPS - updates)*last_left_lower_arm_tx + updates*next_left_lower_arm_tx)/FPS;
	float left_lower_arm_ty = ((FPS - updates)*last_left_lower_arm_ty + updates*next_left_lower_arm_ty)/FPS;
	float left_lower_arm_tz = ((FPS - updates)*last_left_lower_arm_tz + updates*next_left_lower_arm_tz)/FPS;
	float left_lower_arm_rx = ((FPS - updates)*last_left_lower_arm_rx + updates*next_left_lower_arm_rx)/FPS;
	float left_lower_arm_ry = ((FPS - updates)*last_left_lower_arm_ry + updates*next_left_lower_arm_ry)/FPS;
	float left_lower_arm_rz = ((FPS - updates)*last_left_lower_arm_rz + updates*next_left_lower_arm_rz)/FPS;

	float right_upper_arm_tx = ((FPS - updates)*last_right_upper_arm_tx + updates*next_right_upper_arm_tx)/FPS;
	float right_upper_arm_ty = ((FPS - updates)*last_right_upper_arm_ty + updates*next_right_upper_arm_ty)/FPS;
	float right_upper_arm_tz = ((FPS - updates)*last_right_upper_arm_tz + updates*next_right_upper_arm_tz)/FPS;
	float right_upper_arm_rx = ((FPS - updates)*last_right_upper_arm_rx + updates*next_right_upper_arm_rx)/FPS;
	float right_upper_arm_ry = ((FPS - updates)*last_right_upper_arm_ry + updates*next_right_upper_arm_ry)/FPS;
	float right_upper_arm_rz = ((FPS - updates)*last_right_upper_arm_rz + updates*next_right_upper_arm_rz)/FPS;

	float right_lower_arm_tx = ((FPS - updates)*last_right_lower_arm_tx + updates*next_right_lower_arm_tx)/FPS;
	float right_lower_arm_ty = ((FPS - updates)*last_right_lower_arm_ty + updates*next_right_lower_arm_ty)/FPS;
	float right_lower_arm_tz = ((FPS - updates)*last_right_lower_arm_tz + updates*next_right_lower_arm_tz)/FPS;
	float right_lower_arm_rx = ((FPS - updates)*last_right_lower_arm_rx + updates*next_right_lower_arm_rx)/FPS;
	float right_lower_arm_ry = ((FPS - updates)*last_right_lower_arm_ry + updates*next_right_lower_arm_ry)/FPS;
	float right_lower_arm_rz = ((FPS - updates)*last_right_lower_arm_rz + updates*next_right_lower_arm_rz)/FPS;

	float left_upper_leg_tx = ((FPS - updates)*last_left_upper_leg_tx + updates*next_left_upper_leg_tx)/FPS;
	float left_upper_leg_ty = ((FPS - updates)*last_left_upper_leg_ty + updates*next_left_upper_leg_ty)/FPS;
	float left_upper_leg_tz = ((FPS - updates)*last_left_upper_leg_tz + updates*next_left_upper_leg_tz)/FPS;
	float left_upper_leg_rx = ((FPS - updates)*last_left_upper_leg_rx + updates*next_left_upper_leg_rx)/FPS;
	float left_upper_leg_ry = ((FPS - updates)*last_left_upper_leg_ry + updates*next_left_upper_leg_ry)/FPS;
	float left_upper_leg_rz = ((FPS - updates)*last_left_upper_leg_rz + updates*next_left_upper_leg_rz)/FPS;

	float left_lower_leg_tx = ((FPS - updates)*last_left_lower_leg_tx + updates*next_left_lower_leg_tx)/FPS;
	float left_lower_leg_ty = ((FPS - updates)*last_left_lower_leg_ty + updates*next_left_lower_leg_ty)/FPS;
	float left_lower_leg_tz = ((FPS - updates)*last_left_lower_leg_tz + updates*next_left_lower_leg_tz)/FPS;
	float left_lower_leg_rx = ((FPS - updates)*last_left_lower_leg_rx + updates*next_left_lower_leg_rx)/FPS;
	float left_lower_leg_ry = ((FPS - updates)*last_left_lower_leg_ry + updates*next_left_lower_leg_ry)/FPS;
	float left_lower_leg_rz = ((FPS - updates)*last_left_lower_leg_rz + updates*next_left_lower_leg_rz)/FPS;

	float right_upper_leg_tx = ((FPS - updates)*last_right_upper_leg_tx + updates*next_right_upper_leg_tx)/FPS;
	float right_upper_leg_ty = ((FPS - updates)*last_right_upper_leg_ty + updates*next_right_upper_leg_ty)/FPS;
	float right_upper_leg_tz = ((FPS - updates)*last_right_upper_leg_tz + updates*next_right_upper_leg_tz)/FPS;
	float right_upper_leg_rx = ((FPS - updates)*last_right_upper_leg_rx + updates*next_right_upper_leg_rx)/FPS;
	float right_upper_leg_ry = ((FPS - updates)*last_right_upper_leg_ry + updates*next_right_upper_leg_ry)/FPS;
	float right_upper_leg_rz = ((FPS - updates)*last_right_upper_leg_rz + updates*next_right_upper_leg_rz)/FPS;

	float right_lower_leg_tx = ((FPS - updates)*last_right_lower_leg_tx + updates*next_right_lower_leg_tx)/FPS;
	float right_lower_leg_ty = ((FPS - updates)*last_right_lower_leg_ty + updates*next_right_lower_leg_ty)/FPS;
	float right_lower_leg_tz = ((FPS - updates)*last_right_lower_leg_tz + updates*next_right_lower_leg_tz)/FPS;
	float right_lower_leg_rx = ((FPS - updates)*last_right_lower_leg_rx + updates*next_right_lower_leg_rx)/FPS;
	float right_lower_leg_ry = ((FPS - updates)*last_right_lower_leg_ry + updates*next_right_lower_leg_ry)/FPS;
	float right_lower_leg_rz = ((FPS - updates)*last_right_lower_leg_rz + updates*next_right_lower_leg_rz)/FPS;

	float r2d2_left_arm_tx = ((FPS - updates)*last_r2d2_left_arm_tx + updates*next_r2d2_left_arm_tx)/FPS;
	float r2d2_left_arm_ty = ((FPS - updates)*last_r2d2_left_arm_ty + updates*next_r2d2_left_arm_ty)/FPS;
	float r2d2_left_arm_tz = ((FPS - updates)*last_r2d2_left_arm_tz + updates*next_r2d2_left_arm_tz)/FPS;
	float r2d2_left_arm_rx = ((FPS - updates)*last_r2d2_left_arm_rx + updates*next_r2d2_left_arm_rx)/FPS;
	float r2d2_left_arm_ry = ((FPS - updates)*last_r2d2_left_arm_ry + updates*next_r2d2_left_arm_ry)/FPS;
	float r2d2_left_arm_rz = ((FPS - updates)*last_r2d2_left_arm_rz + updates*next_r2d2_left_arm_rz)/FPS;

	float r2d2_right_arm_tx = ((FPS - updates)*last_r2d2_right_arm_tx + updates*next_r2d2_right_arm_tx)/FPS;
	float r2d2_right_arm_ty = ((FPS - updates)*last_r2d2_right_arm_ty + updates*next_r2d2_right_arm_ty)/FPS;
	float r2d2_right_arm_tz = ((FPS - updates)*last_r2d2_right_arm_tz + updates*next_r2d2_right_arm_tz)/FPS;
	float r2d2_right_arm_rx = ((FPS - updates)*last_r2d2_right_arm_rx + updates*next_r2d2_right_arm_rx)/FPS;
	float r2d2_right_arm_ry = ((FPS - updates)*last_r2d2_right_arm_ry + updates*next_r2d2_right_arm_ry)/FPS;
	float r2d2_right_arm_rz = ((FPS - updates)*last_r2d2_right_arm_rz + updates*next_r2d2_right_arm_rz)/FPS;
	
	switch_lamp_light(light0);
	switch_wall_light(light1);
	box_state(lid_angle);

	torso->set_tx(torso_tx);
	torso->set_ty(torso_ty);
	torso->set_tz(torso_tz);
	torso->set_rx(torso_rx);
	torso->set_ry(torso_ry);
	torso->set_rz(torso_rz);

	left_upper_arm->set_tx(left_upper_arm_tx);
	left_upper_arm->set_ty(left_upper_arm_ty);
	left_upper_arm->set_tz(left_upper_arm_tz);
	left_upper_arm->set_rx(left_upper_arm_rx);
	left_upper_arm->set_ry(left_upper_arm_ry);
	left_upper_arm->set_rz(left_upper_arm_rz);

	left_lower_arm->set_tx(left_lower_arm_tx);
	left_lower_arm->set_ty(left_lower_arm_ty);
	left_lower_arm->set_tz(left_lower_arm_tz);
	left_lower_arm->set_rx(left_lower_arm_rx);
	left_lower_arm->set_ry(left_lower_arm_ry);
	left_lower_arm->set_rz(left_lower_arm_rz);

	right_upper_arm->set_tx(right_upper_arm_tx);
	right_upper_arm->set_ty(right_upper_arm_ty);
	right_upper_arm->set_tz(right_upper_arm_tz);
	right_upper_arm->set_rx(right_upper_arm_rx);
	right_upper_arm->set_ry(right_upper_arm_ry);
	right_upper_arm->set_rz(right_upper_arm_rz);

	right_lower_arm->set_tx(right_lower_arm_tx);
	right_lower_arm->set_ty(right_lower_arm_ty);
	right_lower_arm->set_tz(right_lower_arm_tz);
	right_lower_arm->set_rx(right_lower_arm_rx);
	right_lower_arm->set_ry(right_lower_arm_ry);
	right_lower_arm->set_rz(right_lower_arm_rz);

	left_upper_leg->set_tx(left_upper_leg_tx);
	left_upper_leg->set_ty(left_upper_leg_ty);
	left_upper_leg->set_tz(left_upper_leg_tz);
	left_upper_leg->set_rx(left_upper_leg_rx);
	left_upper_leg->set_ry(left_upper_leg_ry);
	left_upper_leg->set_rz(left_upper_leg_rz);

	left_lower_leg->set_tx(left_lower_leg_tx);
	left_lower_leg->set_ty(left_lower_leg_ty);
	left_lower_leg->set_tz(left_lower_leg_tz);
	left_lower_leg->set_rx(left_lower_leg_rx);
	left_lower_leg->set_ry(left_lower_leg_ry);
	left_lower_leg->set_rz(left_lower_leg_rz);

	right_upper_leg->set_tx(right_upper_leg_tx);
	right_upper_leg->set_ty(right_upper_leg_ty);
	right_upper_leg->set_tz(right_upper_leg_tz);
	right_upper_leg->set_rx(right_upper_leg_rx);
	right_upper_leg->set_ry(right_upper_leg_ry);
	right_upper_leg->set_rz(right_upper_leg_rz);

	right_lower_leg->set_tx(right_lower_leg_tx);
	right_lower_leg->set_ty(right_lower_leg_ty);
	right_lower_leg->set_tz(right_lower_leg_tz);
	right_lower_leg->set_rx(right_lower_leg_rx);
	right_lower_leg->set_ry(right_lower_leg_ry);
	right_lower_leg->set_rz(right_lower_leg_rz);

	r2d2_left_arm->set_tx(r2d2_left_arm_tx);
	r2d2_left_arm->set_ty(r2d2_left_arm_ty);
	r2d2_left_arm->set_tz(r2d2_left_arm_tz);
	r2d2_left_arm->set_rx(r2d2_left_arm_rx);
	r2d2_left_arm->set_ry(r2d2_left_arm_ry);
	r2d2_left_arm->set_rz(r2d2_left_arm_rz);

	r2d2_right_arm->set_tx(r2d2_right_arm_tx);
	r2d2_right_arm->set_ty(r2d2_right_arm_ty);
	r2d2_right_arm->set_tz(r2d2_right_arm_tz);
	r2d2_right_arm->set_rx(r2d2_right_arm_rx);
	r2d2_right_arm->set_ry(r2d2_right_arm_ry);
	r2d2_right_arm->set_rz(r2d2_right_arm_rz);

	r2d2_body->set_tx(r2d2_body_tx);
	r2d2_body->set_ty(r2d2_body_ty);
	r2d2_body->set_tz(r2d2_body_tz);
	r2d2_body->set_rx(r2d2_body_rx);
	r2d2_body->set_ry(r2d2_body_ry);
	r2d2_body->set_rz(r2d2_body_rz);
}

void playback_init() {
	glfwSetTime(0);
	playback_running = true;
	cout<<"Set time to 0."<<endl;

	// Init last
	if (load_last()) {
	} else {
		playback_running = false;
	}

	// Init next
	if (load_next()) {
	} else {
		playback_running = false;
	}
}

void keyframe_read() {
	// Last becomes old next
	last_light0 = next_light0;
	last_light1 = next_light1;
	last_lid_angle = next_lid_angle;
	last_light0 = next_light0;
	last_light1 = next_light1;
	last_lid_angle = next_lid_angle;

	last_torso_tx = next_torso_tx;
	last_torso_ty = next_torso_ty;
	last_torso_tz = next_torso_tz;
	last_torso_rx = next_torso_rx;
	last_torso_ry = next_torso_ry;
	last_torso_rz = next_torso_rz;

	last_left_upper_arm_tx = next_left_upper_arm_tx;
	last_left_upper_arm_ty = next_left_upper_arm_ty;
	last_left_upper_arm_tz = next_left_upper_arm_tz;
	last_left_upper_arm_rx = next_left_upper_arm_rx;
	last_left_upper_arm_ry = next_left_upper_arm_ry;
	last_left_upper_arm_rz = next_left_upper_arm_rz;

	last_left_lower_arm_tx = next_left_lower_arm_tx;
	last_left_lower_arm_ty = next_left_lower_arm_ty;
	last_left_lower_arm_tz = next_left_lower_arm_tz;
	last_left_lower_arm_rx = next_left_lower_arm_rx;
	last_left_lower_arm_ry = next_left_lower_arm_ry;
	last_left_lower_arm_rz = next_left_lower_arm_rz;

	last_right_upper_arm_tx = next_right_upper_arm_tx;
	last_right_upper_arm_ty = next_right_upper_arm_ty;
	last_right_upper_arm_tz = next_right_upper_arm_tz;
	last_right_upper_arm_rx = next_right_upper_arm_rx;
	last_right_upper_arm_ry = next_right_upper_arm_ry;
	last_right_upper_arm_rz = next_right_upper_arm_rz;

	last_right_lower_arm_tx = next_right_lower_arm_tx;
	last_right_lower_arm_ty = next_right_lower_arm_ty;
	last_right_lower_arm_tz = next_right_lower_arm_tz;
	last_right_lower_arm_rx = next_right_lower_arm_rx;
	last_right_lower_arm_ry = next_right_lower_arm_ry;
	last_right_lower_arm_rz = next_right_lower_arm_rz;

	last_left_upper_leg_tx = next_left_upper_leg_tx;
	last_left_upper_leg_ty = next_left_upper_leg_ty;
	last_left_upper_leg_tz = next_left_upper_leg_tz;
	last_left_upper_leg_rx = next_left_upper_leg_rx;
	last_left_upper_leg_ry = next_left_upper_leg_ry;
	last_left_upper_leg_rz = next_left_upper_leg_rz;

	last_left_lower_leg_tx = next_left_lower_leg_tx;
	last_left_lower_leg_ty = next_left_lower_leg_ty;
	last_left_lower_leg_tz = next_left_lower_leg_tz;
	last_left_lower_leg_rx = next_left_lower_leg_rx;
	last_left_lower_leg_ry = next_left_lower_leg_ry;
	last_left_lower_leg_rz = next_left_lower_leg_rz;

	last_right_upper_leg_tx = next_right_upper_leg_tx;
	last_right_upper_leg_ty = next_right_upper_leg_ty;
	last_right_upper_leg_tz = next_right_upper_leg_tz;
	last_right_upper_leg_rx = next_right_upper_leg_rx;
	last_right_upper_leg_ry = next_right_upper_leg_ry;
	last_right_upper_leg_rz = next_right_upper_leg_rz;

	last_right_lower_leg_tx = next_right_lower_leg_tx;
	last_right_lower_leg_ty = next_right_lower_leg_ty;
	last_right_lower_leg_tz = next_right_lower_leg_tz;
	last_right_lower_leg_rx = next_right_lower_leg_rx;
	last_right_lower_leg_ry = next_right_lower_leg_ry;
	last_right_lower_leg_rz = next_right_lower_leg_rz;

	last_r2d2_left_arm_tx = next_r2d2_left_arm_tx;
	last_r2d2_left_arm_ty = next_r2d2_left_arm_ty;
	last_r2d2_left_arm_tz = next_r2d2_left_arm_tz;
	last_r2d2_left_arm_rx = next_r2d2_left_arm_rx;
	last_r2d2_left_arm_ry = next_r2d2_left_arm_ry;
	last_r2d2_left_arm_rz = next_r2d2_left_arm_rz;

	last_r2d2_right_arm_tx = next_r2d2_right_arm_tx;
	last_r2d2_right_arm_ty = next_r2d2_right_arm_ty;
	last_r2d2_right_arm_tz = next_r2d2_right_arm_tz;
	last_r2d2_right_arm_rx = next_r2d2_right_arm_rx;
	last_r2d2_right_arm_ry = next_r2d2_right_arm_ry;
	last_r2d2_right_arm_rz = next_r2d2_right_arm_rz;

	last_r2d2_body_tx = next_r2d2_body_tx;
	last_r2d2_body_ty = next_r2d2_body_ty;
	last_r2d2_body_tz = next_r2d2_body_tz;
	last_r2d2_body_rx = next_r2d2_body_rx;
	last_r2d2_body_ry = next_r2d2_body_ry;
	last_r2d2_body_rz = next_r2d2_body_rz;

	// Read new next
	if (load_next()) {
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
