GLuint bed_headrest_vbo, bed_headrest_vao;

glm::vec4 bed_headrest_positions[8] = {
  glm::vec4(-20, -10, -15, 1.0),
  glm::vec4(-20, -3, -15, 1.0),
  glm::vec4(-18, -3, -15, 1.0),
  glm::vec4(-18, -10, -15, 1.0),
  glm::vec4(-20, -10, -5, 1.0),
  glm::vec4(-20, -3, -5, 1.0),
  glm::vec4(-18, -3, -5, 1.0),
  glm::vec4(-18, -10, -5, 1.0)
};

void init_bed_headrest()
{
  init_texcub(&bed_headrest_vao, &bed_headrest_vbo, bed_headrest_positions);
}

void draw_bed_headrest(glm::mat4 view_matrix) {
  draw_texcub(view_matrix, &bed_headrest_vao, "images/floor.bmp");
}
