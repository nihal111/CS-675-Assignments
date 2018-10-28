GLuint bed_mattress_vbo, bed_mattress_vao;

glm::vec4 bed_mattress_positions[8] = {
  glm::vec4(-18, -8, -14.9, 1.0),
  glm::vec4(-18, -7, -14.9, 1.0),
  glm::vec4(-0.1, -7, -14.9, 1.0),
  glm::vec4(-0.1, -8, -14.9, 1.0),
  glm::vec4(-18, -8, -5.1, 1.0),
  glm::vec4(-18, -7, -5.1, 1.0),
  glm::vec4(-0.1, -7, -5.1, 1.0),
  glm::vec4(-0.1, -8, -5.1, 1.0)
};

void init_bed_mattress()
{
  init_texcub(&bed_mattress_vao, &bed_mattress_vbo, bed_mattress_positions);
}

void draw_bed_mattress(glm::mat4 view_matrix) {
  draw_texcub(view_matrix, &bed_mattress_vao, "images/mattress.bmp", 100, 100);
}
