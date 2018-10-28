csX75::HNode* wall_light_base;
csX75::HNode* wall_light_bulb;


void init_wall_light() {
	wall_light_base = get_cylinder(0.5, 0.5, 2, black);
	wall_light_base->change_parameters(-19.4,2,7,
	                        0.0,0.0,0.0);

	wall_light_bulb = get_ellipsoid(0.4, 0.4, 0.4, orange);
	wall_light_bulb->set_parent(wall_light_base);
	wall_light_bulb->change_parameters(0.0, -0.2, 0.0,
	                      0.0, 0.0, 0.0);
}

void draw_wall_light() {
	wall_light_base->render_tree();
}