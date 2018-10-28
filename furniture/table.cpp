GLuint table_top_vbo, table_top_vao;

glm::vec4 table_top_positions[8] = {
  glm::vec4(-19, -5, 14, 1.0),
  glm::vec4(-19, -4, 14, 1.0),
  glm::vec4(-14, -4, 14, 1.0),
  glm::vec4(-14, -5, 14, 1.0),
  glm::vec4(-19, -5, 0, 1.0),
  glm::vec4(-19, -4, 0, 1.0),
  glm::vec4(-14, -4, 0, 1.0),
  glm::vec4(-14, -5, 0, 1.0)
};

void init_table_top()
{
  init_texcub(&table_top_vao, &table_top_vbo, table_top_positions);
}

void draw_table_top(glm::mat4 view_matrix) {
  draw_texcub(view_matrix, &table_top_vao, "images/wood1.bmp");
}

// Leg 1
GLuint table_leg1_vbo, table_leg1_vao;

glm::vec4 table_leg1_positions[8] = {
  glm::vec4(-19, -5, 14, 1.0),
  glm::vec4(-19, -10, 14, 1.0),
  glm::vec4(-18, -10, 14, 1.0),
  glm::vec4(-18, -5, 14, 1.0),
  glm::vec4(-19, -5, 13, 1.0),
  glm::vec4(-19, -10, 13, 1.0),
  glm::vec4(-18, -10, 13, 1.0),
  glm::vec4(-18, -5, 13, 1.0)
};

void init_table_leg1()
{
  init_texcub(&table_leg1_vao, &table_leg1_vbo, table_leg1_positions);
}

void draw_table_leg1(glm::mat4 view_matrix) {
  draw_texcub(view_matrix, &table_leg1_vao, "images/wood.bmp");
}

// Leg 2
GLuint table_leg2_vbo, table_leg2_vao;

glm::vec4 table_leg2_positions[8] = {
  glm::vec4(-15, -5, 14, 1.0),
  glm::vec4(-15, -10, 14, 1.0),
  glm::vec4(-14, -10, 14, 1.0),
  glm::vec4(-14, -5, 14, 1.0),
  glm::vec4(-15, -5, 13, 1.0),
  glm::vec4(-15, -10, 13, 1.0),
  glm::vec4(-14, -10, 13, 1.0),
  glm::vec4(-14, -5, 13, 1.0)
};

void init_table_leg2()
{
  init_texcub(&table_leg2_vao, &table_leg2_vbo, table_leg2_positions);
}

void draw_table_leg2(glm::mat4 view_matrix) {
  draw_texcub(view_matrix, &table_leg2_vao, "images/wood.bmp");
}

// Leg 3
GLuint table_leg3_vbo, table_leg3_vao;

glm::vec4 table_leg3_positions[8] = {
  glm::vec4(-19, -5, 1, 1.0),
  glm::vec4(-19, -10, 1, 1.0),
  glm::vec4(-18, -10, 1, 1.0),
  glm::vec4(-18, -5, 1, 1.0),
  glm::vec4(-19, -5, 0, 1.0),
  glm::vec4(-19, -10, 0, 1.0),
  glm::vec4(-18, -10, 0, 1.0),
  glm::vec4(-18, -5, 0, 1.0)
};

void init_table_leg3()
{
  init_texcub(&table_leg3_vao, &table_leg3_vbo, table_leg3_positions);
}

void draw_table_leg3(glm::mat4 view_matrix) {
  draw_texcub(view_matrix, &table_leg3_vao, "images/wood.bmp");
}

// Leg 4
GLuint table_leg4_vbo, table_leg4_vao;

glm::vec4 table_leg4_positions[8] = {
  glm::vec4(-15, -5, 1, 1.0),
  glm::vec4(-15, -10, 1, 1.0),
  glm::vec4(-14, -10, 1, 1.0),
  glm::vec4(-14, -5, 1, 1.0),
  glm::vec4(-15, -5, 0, 1.0),
  glm::vec4(-15, -10, 0, 1.0),
  glm::vec4(-14, -10, 0, 1.0),
  glm::vec4(-14, -5, 0, 1.0)
};

void init_table_leg4()
{
  init_texcub(&table_leg4_vao, &table_leg4_vbo, table_leg4_positions);
}

void draw_table_leg4(glm::mat4 view_matrix) {
  draw_texcub(view_matrix, &table_leg4_vao, "images/wood.bmp");
}


void init_table() {
  init_table_top();
  init_table_leg1();
  init_table_leg2();
  init_table_leg3();
  init_table_leg4();
}

void draw_table(glm::mat4 view_matrix) {
  draw_table_top(view_matrix);
  draw_table_leg1(view_matrix);
  draw_table_leg2(view_matrix);
  draw_table_leg3(view_matrix);
  draw_table_leg4(view_matrix);
}
