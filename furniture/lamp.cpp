csX75::HNode* lamp_base;
csX75::HNode* lamp_neck;

GLuint lamp_head_vbo, lamp_head_vao;
extern GLuint light0ON;

glm::vec4 lamp_head_positions[8] = {
  glm::vec4(-19, -2, 14, 1.0),
  glm::vec4(-19, 1, 14, 1.0),
  glm::vec4(-17, 1, 14, 1.0),
  glm::vec4(-17, -2, 14, 1.0),
  glm::vec4(-19, -2, 12, 1.0),
  glm::vec4(-19, 1, 12, 1.0),
  glm::vec4(-17, 1, 12, 1.0),
  glm::vec4(-17, -2, 12, 1.0)
};

void init_lamp() {
	lamp_base = get_cylinder(1, 1, 0.1, grey);
	lamp_base->change_parameters(-18,-3.95,13,
	                        0.0,0.0,0.0);

	lamp_neck = get_cylinder(0.1, 0.1, 3, grey);
	lamp_neck->set_parent(lamp_base);
	lamp_neck->change_parameters(0,0.1,0,
	                        0.0,0.0,0.0);

	init_texcub(&lamp_head_vao, &lamp_head_vbo, lamp_head_positions, -1);
}

void draw_lamp(glm::mat4 view_matrix) {
	lamp_base->render_tree();
	draw_textured_object(view_matrix, &lamp_head_vao, "images/lamp.bmp", 100, 100);
}

void switch_lamp_light(float l) {
	int light = (l > 0.5) ? 1 : 0;
	glUniform1i(light0ON, light);
}