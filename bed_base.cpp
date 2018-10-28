GLuint bed_base_vbo, bed_base_vao;

glm::vec4 bed_base_positions[8] = {
  glm::vec4(-18, -10, -15, 1.0),
  glm::vec4(-18, -8, -15, 1.0),
  glm::vec4(0, -8, -15, 1.0),
  glm::vec4(0, -10, -15, 1.0),
  glm::vec4(-18, -10, -5, 1.0),
  glm::vec4(-18, -8, -5, 1.0),
  glm::vec4(0, -8, -5, 1.0),
  glm::vec4(0, -10, -5, 1.0)
};

void init_bed_base()
{
  init_texcub(&bed_base_vao, &bed_base_vbo, bed_base_positions);
}

void draw_bed_base(glm::mat4 view_matrix) {
  draw_texcub(view_matrix, &bed_base_vao, "images/dark_wood2.bmp", 100, 100);
}
