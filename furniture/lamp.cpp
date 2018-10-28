csX75::HNode* lamp_head;
csX75::HNode* lamp_base;
csX75::HNode* lamp_neck;


void init_lamp() {
	lamp_base = get_cylinder(1, 1, 0.1, grey);
	lamp_base->change_parameters(-18,-3.95,13,
	                        0.0,0.0,0.0);

	lamp_neck = get_cylinder(0.1, 0.1, 3, grey);
	lamp_neck->set_parent(lamp_base);
	lamp_neck->change_parameters(0,0.1,0,
	                        0.0,0.0,0.0);

	lamp_head = get_cylinder(0.8, 0.8, 2, orange);
	lamp_head->set_parent(lamp_neck);
	lamp_head->change_parameters(0,2,0,
	                        0.0,0.0,0.0);
}

void draw_lamp() {
	lamp_base->render_tree();
}