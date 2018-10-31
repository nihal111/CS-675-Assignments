// Chair top
GLuint chair_top_vbo, chair_top_vao;

glm::vec4 chair_top_positions[8] = {
  glm::vec4(-10, -7, 14, 1.0),
  glm::vec4(-10, -6.5, 14, 1.0),
  glm::vec4(-8, -6.5, 14, 1.0),
  glm::vec4(-8, -7, 14, 1.0),
  glm::vec4(-10, -7, 12, 1.0),
  glm::vec4(-10, -6.5, 12, 1.0),
  glm::vec4(-8, -6.5, 12, 1.0),
  glm::vec4(-8, -7, 12, 1.0)
};

void init_chair_top()
{
  init_texcub(&chair_top_vao, &chair_top_vbo, chair_top_positions);
}

void draw_chair_top(glm::mat4 view_matrix) {
  draw_textured_object(view_matrix, &chair_top_vao, "images/dark_wood.bmp", 100, 100);
}

// Leg 1
GLuint chair_leg1_vbo, chair_leg1_vao;

glm::vec4 chair_leg1_positions[8] = {
  glm::vec4(-10, -7, 14, 1.0),
  glm::vec4(-10, -10, 14, 1.0),
  glm::vec4(-9.9, -10, 14, 1.0),
  glm::vec4(-9.9, -7, 14, 1.0),
  glm::vec4(-10, -7, 13.9, 1.0),
  glm::vec4(-10, -10, 13.9, 1.0),
  glm::vec4(-9.9, -10, 13.9, 1.0),
  glm::vec4(-9.9, -7, 13.9, 1.0)
};

void init_chair_leg1()
{
  init_texcub(&chair_leg1_vao, &chair_leg1_vbo, chair_leg1_positions);
}

void draw_chair_leg1(glm::mat4 view_matrix) {
  draw_textured_object(view_matrix, &chair_leg1_vao, "images/dark_wood.bmp", 100, 100);
}

// Leg 2
GLuint chair_leg2_vbo, chair_leg2_vao;

glm::vec4 chair_leg2_positions[8] = {
  glm::vec4(-8.1, -7, 14, 1.0),
  glm::vec4(-8.1, -10, 14, 1.0),
  glm::vec4(-8, -10, 14, 1.0),
  glm::vec4(-8, -7, 14, 1.0),
  glm::vec4(-8.1, -7, 13.9, 1.0),
  glm::vec4(-8.1, -10, 13.9, 1.0),
  glm::vec4(-8, -10, 13.9, 1.0),
  glm::vec4(-8, -7, 13.9, 1.0)
};

void init_chair_leg2()
{
  init_texcub(&chair_leg2_vao, &chair_leg2_vbo, chair_leg2_positions);
}

void draw_chair_leg2(glm::mat4 view_matrix) {
  draw_textured_object(view_matrix, &chair_leg2_vao, "images/dark_wood.bmp", 100, 100);
}

// Leg 3
GLuint chair_leg3_vbo, chair_leg3_vao;

glm::vec4 chair_leg3_positions[8] = {
  glm::vec4(-10, -7, 12.1, 1.0),
  glm::vec4(-10, -10, 12.1, 1.0),
  glm::vec4(-9.9, -10, 12.1, 1.0),
  glm::vec4(-9.9, -7, 12.1, 1.0),
  glm::vec4(-10, -7, 12, 1.0),
  glm::vec4(-10, -10, 12, 1.0),
  glm::vec4(-9.9, -10, 12, 1.0),
  glm::vec4(-9.9, -7, 12, 1.0)
};

void init_chair_leg3()
{
  init_texcub(&chair_leg3_vao, &chair_leg3_vbo, chair_leg3_positions);
}

void draw_chair_leg3(glm::mat4 view_matrix) {
  draw_textured_object(view_matrix, &chair_leg3_vao, "images/dark_wood.bmp", 100, 100);
}

// Leg 4
GLuint chair_leg4_vbo, chair_leg4_vao;

glm::vec4 chair_leg4_positions[8] = {
  glm::vec4(-8.1, -7, 12.1, 1.0),
  glm::vec4(-8.1, -10, 12.1, 1.0),
  glm::vec4(-8, -10, 12.1, 1.0),
  glm::vec4(-8, -7, 12.1, 1.0),
  glm::vec4(-8.1, -7, 12, 1.0),
  glm::vec4(-8.1, -10, 12, 1.0),
  glm::vec4(-8, -10, 12, 1.0),
  glm::vec4(-8, -7, 12, 1.0)
};

void init_chair_leg4()
{
  init_texcub(&chair_leg4_vao, &chair_leg4_vbo, chair_leg4_positions);
}

void draw_chair_leg4(glm::mat4 view_matrix) {
  draw_textured_object(view_matrix, &chair_leg4_vao, "images/dark_wood.bmp", 100, 100);
}

// Chair back
GLuint chair_back_vbo, chair_back_vao;

glm::vec4 chair_back_positions[8] = {
  glm::vec4(-10, -6.5, 14, 1.0),
  glm::vec4(-10, -4, 14, 1.0),
  glm::vec4(-8, -4, 14, 1.0),
  glm::vec4(-8, -6.5, 14, 1.0),
  glm::vec4(-10, -6.5, 13.9, 1.0),
  glm::vec4(-10, -4, 13.9, 1.0),
  glm::vec4(-8, -4, 13.9, 1.0),
  glm::vec4(-8, -6.5, 13.9, 1.0)
};

void init_chair_back()
{
  init_texcub(&chair_back_vao, &chair_back_vbo, chair_back_positions);
}

void draw_chair_back(glm::mat4 view_matrix) {
  draw_textured_object(view_matrix, &chair_back_vao, "images/dark_wood.bmp", 100, 100);
}


void init_chair() {
  init_chair_top();
  init_chair_leg1();
  init_chair_leg2();
  init_chair_leg3();
  init_chair_leg4();
  init_chair_back();
}

void draw_chair(glm::mat4 view_matrix) {
  draw_chair_top(view_matrix);
  draw_chair_leg1(view_matrix);
  draw_chair_leg2(view_matrix);
  draw_chair_leg3(view_matrix);
  draw_chair_leg4(view_matrix);
  draw_chair_back(view_matrix);
}
