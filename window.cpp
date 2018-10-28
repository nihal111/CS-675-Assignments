GLuint window_sill_vbo, window_sill_vao;

glm::vec4 window_sill_positions[8] = {
  glm::vec4(-0.1, -5.1, 15, 1.0),
  glm::vec4(-0.1, 0.1, 15, 1.0),
  glm::vec4(10.1, 0.1, 15, 1.0),
  glm::vec4(10.1, -5.1, 15, 1.0),
  glm::vec4(-0.1, -5.1, 14.99, 1.0),
  glm::vec4(-0.1, 0.1, 14.99, 1.0),
  glm::vec4(10.1, 0.1, 14.99, 1.0),
  glm::vec4(10.1, -5.1, 14.99, 1.0)
};

void init_window_sill()
{
  init_texcub(&window_sill_vao, &window_sill_vbo, window_sill_positions);
}

void draw_window_sill(glm::mat4 view_matrix) {
  draw_texcub(view_matrix, &window_sill_vao, "images/floor.bmp");
}

// Leg 1
GLuint window_scene_vbo, window_scene_vao;

glm::vec4 window_scene_positions[8] = {
  glm::vec4(0, -5, 14.99, 1.0),
  glm::vec4(0, 0, 14.99, 1.0),
  glm::vec4(10, 0, 14.99, 1.0),
  glm::vec4(10, -5, 14.99, 1.0),
  glm::vec4(0, -5, 14.98, 1.0),
  glm::vec4(0, 0, 14.98, 1.0),
  glm::vec4(10, 0, 14.98, 1.0),
  glm::vec4(10, -5, 14.98, 1.0)
};

void init_window_scene()
{
  init_texcub(&window_scene_vao, &window_scene_vbo, window_scene_positions);
}

void draw_window_scene(glm::mat4 view_matrix) {
  draw_texcub(view_matrix, &window_scene_vao, "images/window.bmp", 512, 256);
}

void init_window() {
  init_window_sill();
  init_window_scene();
}

void draw_window(glm::mat4 view_matrix) {
  draw_window_sill(view_matrix);
  draw_window_scene(view_matrix);
}
