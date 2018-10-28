GLuint drawer_vbo, drawer_vao;
GLuint drawer_front_vbo, drawer_front_vao;

glm::vec4 drawer_positions[8] = {
  glm::vec4(1, -10, -15, 1.0),
  glm::vec4(1, 0, -15, 1.0),
  glm::vec4(6, 0, -15, 1.0),
  glm::vec4(6, -10, -15, 1.0),
  glm::vec4(1, -10, -12, 1.0),
  glm::vec4(1, 0, -12, 1.0),
  glm::vec4(6, 0, -12, 1.0),
  glm::vec4(6, -10, -12, 1.0)
};

const int drawer_num_vertices = 30;
int drawer_tri_idx=0;
glm::vec4 drawer_v_positions[drawer_num_vertices];
glm::vec4 drawer_v_colors[drawer_num_vertices];
glm::vec4 drawer_v_normals[drawer_num_vertices];
glm::vec2 drawer_tex_coords[drawer_num_vertices];

glm::vec2 tex_drawer[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 5.0),
  glm::vec2( 5.0, 0.0),
  glm::vec2( 5.0, 5.0)
};

void drawer_quad(int a, int b, int c, int d)
{
  drawer_v_positions[drawer_tri_idx] = drawer_positions[a];
  drawer_tex_coords[drawer_tri_idx] = tex_drawer[1];
  drawer_tri_idx++;
  drawer_v_positions[drawer_tri_idx] = drawer_positions[b];
  drawer_tex_coords[drawer_tri_idx] = tex_drawer[0];
  drawer_tri_idx++;
  drawer_v_positions[drawer_tri_idx] = drawer_positions[c];
  drawer_tex_coords[drawer_tri_idx] = tex_drawer[2];
  drawer_tri_idx++;
  drawer_v_positions[drawer_tri_idx] = drawer_positions[a];
  drawer_tex_coords[drawer_tri_idx] = tex_drawer[1];
  drawer_tri_idx++;
  drawer_v_positions[drawer_tri_idx] = drawer_positions[c]; 
  drawer_tex_coords[drawer_tri_idx] = tex_drawer[2];
  drawer_tri_idx++;
  drawer_v_positions[drawer_tri_idx] = drawer_positions[d]; 
  drawer_tex_coords[drawer_tri_idx] = tex_drawer[3];
  drawer_tri_idx++;
}


const int drawer_front_num_vertices = 6;
int drawer_front_tri_idx=0;
glm::vec4 drawer_front_v_positions[drawer_front_num_vertices];
glm::vec4 drawer_front_v_colors[drawer_front_num_vertices];
glm::vec4 drawer_front_v_normals[drawer_front_num_vertices];
glm::vec2 drawer_front_tex_coords[drawer_front_num_vertices];

void drawer_front(void)
{
  drawer_front_v_positions[drawer_front_tri_idx] = drawer_positions[4];
  drawer_front_tex_coords[drawer_front_tri_idx] = tex_drawer[1];
  drawer_front_tri_idx++;
  drawer_front_v_positions[drawer_front_tri_idx] = drawer_positions[5];
  drawer_front_tex_coords[drawer_front_tri_idx] = tex_drawer[0];
  drawer_front_tri_idx++;
  drawer_front_v_positions[drawer_front_tri_idx] = drawer_positions[6];
  drawer_front_tex_coords[drawer_front_tri_idx] = tex_drawer[2];
  drawer_front_tri_idx++;
  drawer_front_v_positions[drawer_front_tri_idx] = drawer_positions[4];
  drawer_front_tex_coords[drawer_front_tri_idx] = tex_drawer[1];
  drawer_front_tri_idx++;
  drawer_front_v_positions[drawer_front_tri_idx] = drawer_positions[6]; 
  drawer_front_tex_coords[drawer_front_tri_idx] = tex_drawer[2];
  drawer_front_tri_idx++;
  drawer_front_v_positions[drawer_front_tri_idx] = drawer_positions[7]; 
  drawer_front_tex_coords[drawer_front_tri_idx] = tex_drawer[3];
  drawer_front_tri_idx++;
}

void drawer(void)
{ 
  // Back
  drawer_quad( 1, 0, 3, 2);
  // Right
  drawer_quad( 2, 3, 7, 6);
  // Front
  // drawer_quad( 4, 5, 6, 7);
  // Left
  drawer_quad( 5, 4, 0, 1);
  // // Top
  drawer_quad( 6, 5, 1, 2);
  // // Bottom
  drawer_quad( 3, 0, 4, 7);
}

void init_drawer()
{
  // ---- Create drawer. All but front face.

  glGenVertexArrays (1, &drawer_vao);
  glGenBuffers (1, &drawer_vbo);

  glBindVertexArray (drawer_vao);
  glBindBuffer (GL_ARRAY_BUFFER, drawer_vbo);

  drawer();

  glBufferData (GL_ARRAY_BUFFER, sizeof (drawer_v_positions) + sizeof(drawer_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(drawer_v_positions), drawer_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(drawer_v_positions), sizeof(drawer_tex_coords), drawer_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(drawer_v_positions)) );

  // ---- Create drawer. Front face.

  glGenVertexArrays (1, &drawer_front_vao);
  glGenBuffers (1, &drawer_front_vbo);

  glBindVertexArray (drawer_front_vao);
  glBindBuffer (GL_ARRAY_BUFFER, drawer_front_vbo);

  drawer_front();

  glBufferData (GL_ARRAY_BUFFER, sizeof (drawer_front_v_positions) + sizeof(drawer_front_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(drawer_front_v_positions), drawer_front_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(drawer_front_v_positions), sizeof(drawer_front_tex_coords), drawer_front_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(drawer_front_v_positions)) );
}

void draw_drawer(glm::mat4 view_matrix) {
  // Draw all but front face
  GLuint tex = LoadTexture("images/drawer.bmp", 256, 256);
  glBindTexture(GL_TEXTURE_2D, tex);

  glUniform1i(useTexture, 1);
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  glBindVertexArray (drawer_vao);
  glDrawArrays(GL_TRIANGLES, 0, drawer_num_vertices);

  // Draw front face
  tex = LoadTexture("images/all1.bmp", 256, 256);
  glBindTexture(GL_TEXTURE_2D, tex);

  glUniform1i(useTexture, 1);
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  glBindVertexArray (drawer_front_vao);
  glDrawArrays(GL_TRIANGLES, 0, drawer_front_num_vertices);
}
