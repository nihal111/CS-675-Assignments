#include <fstream>
#include <iostream>
using namespace std;

extern int light0, light1;
extern csX75::HNode *base_box, *lid, *platform, *curr_node;
extern csX75::HNode *left_upper_arm, *left_lower_arm, *right_upper_arm, *right_lower_arm, *left_hand, *right_hand,
                    *left_upper_leg, *left_lower_leg, *right_upper_leg, *right_lower_leg, *left_feet, *right_feet, 
                    *torso, *neck, *head;
extern csX75::HNode *r2d2_body, *r2d2_head, *r2d2_left_arm, *r2d2_right_arm, *r2d2_left_hand, *r2d2_right_hand;


void recorder() {
	ofstream myfile;
	myfile.open ("keyframes.txt", ios::out | ios::app);
	cout<<"Recording position"<<endl;
	myfile << light0 					<< " " 
		   << light1 					<< " "
		   << lid->get_rx()				<< " "

		   << torso->get_tx() 			<< " "
		   << torso->get_ty() 			<< " "
		   << torso->get_tz() 			<< " "
		   << torso->get_rx() 			<< " "
		   << torso->get_ry() 			<< " "
		   << torso->get_rz() 			<< " "

		   << left_upper_arm->get_rx()	<< " "
		   << left_upper_arm->get_ry()	<< " "
		   << left_upper_arm->get_rz()	<< " "

		   << left_lower_arm->get_rx()	<< " "
		   << left_lower_arm->get_ry()	<< " "
		   << left_lower_arm->get_rz()	<< " "

		   << right_upper_arm->get_rx()	<< " "
		   << right_upper_arm->get_ry()	<< " "
		   << right_upper_arm->get_rz()	<< " "

		   << right_lower_arm->get_rx()	<< " "
		   << right_lower_arm->get_ry()	<< " "
		   << right_lower_arm->get_rz()	<< " "

		   << left_upper_leg->get_rx()	<< " "
		   << left_upper_leg->get_ry()	<< " "
		   << left_upper_leg->get_rz()	<< " "

		   << left_lower_leg->get_rx()	<< " "
		   << left_lower_leg->get_ry()	<< " "
		   << left_lower_leg->get_rz()	<< " "

		   << right_upper_leg->get_rx()	<< " "
		   << right_upper_leg->get_ry()	<< " "
		   << right_upper_leg->get_rz()	<< " "

		   << right_lower_leg->get_rx()	<< " "
		   << right_lower_leg->get_ry()	<< " "
		   << right_lower_leg->get_rz()	<< " "

		   << r2d2_left_arm->get_rx()	<< " "
		   << r2d2_left_arm->get_ry()	<< " "
		   << r2d2_left_arm->get_rz()	<< " "

		   << r2d2_right_arm->get_rx()	<< " "
		   << r2d2_right_arm->get_ry()	<< " "
		   << r2d2_right_arm->get_rz()	<< " "

		   << r2d2_body->get_tx() 		<< " "
		   << r2d2_body->get_ty() 		<< " "
		   << r2d2_body->get_tz() 		<< " "
		   << r2d2_body->get_rx() 		<< " "
		   << r2d2_body->get_ry() 		<< " "
		   << r2d2_body->get_rz() 		<< " "
		   << endl;
	myfile.close();
}
