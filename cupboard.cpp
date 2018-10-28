GLuint cupboard_vbo, cupboard_vao;
GLuint cupboard_front_vbo, cupboard_front_vao;

glm::vec4 cupboard_positions[8] = {
  glm::vec4(20, -10, 5, 1.0),
  glm::vec4(20, 5, 5, 1.0),
  glm::vec4(20, 5, 15, 1.0),
  glm::vec4(20, -10, 15, 1.0),
  glm::vec4(15, -10, 5, 1.0),
  glm::vec4(15, 5, 5, 1.0),
  glm::vec4(15, 5, 15, 1.0),
  glm::vec4(15, -10, 15, 1.0)
};

const int cupboard_num_vertices = 30;
int cupboard_tri_idx=0;
glm::vec4 cupboard_v_positions[cupboard_num_vertices];
glm::vec4 cupboard_v_colors[cupboard_num_vertices];
glm::vec4 cupboard_v_normals[cupboard_num_vertices];
glm::vec2 cupboard_tex_coords[cupboard_num_vertices];

glm::vec2 tex_cupboard[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 5.0),
  glm::vec2( 5.0, 0.0),
  glm::vec2( 5.0, 5.0)
};

void cupboard_quad(int a, int b, int c, int d)
{
  cupboard_v_positions[cupboard_tri_idx] = cupboard_positions[a];
  cupboard_tex_coords[cupboard_tri_idx] = tex_cupboard[1];
  cupboard_tri_idx++;
  cupboard_v_positions[cupboard_tri_idx] = cupboard_positions[b];
  cupboard_tex_coords[cupboard_tri_idx] = tex_cupboard[0];
  cupboard_tri_idx++;
  cupboard_v_positions[cupboard_tri_idx] = cupboard_positions[c];
  cupboard_tex_coords[cupboard_tri_idx] = tex_cupboard[2];
  cupboard_tri_idx++;
  cupboard_v_positions[cupboard_tri_idx] = cupboard_positions[a];
  cupboard_tex_coords[cupboard_tri_idx] = tex_cupboard[1];
  cupboard_tri_idx++;
  cupboard_v_positions[cupboard_tri_idx] = cupboard_positions[c]; 
  cupboard_tex_coords[cupboard_tri_idx] = tex_cupboard[2];
  cupboard_tri_idx++;
  cupboard_v_positions[cupboard_tri_idx] = cupboard_positions[d]; 
  cupboard_tex_coords[cupboard_tri_idx] = tex_cupboard[3];
  cupboard_tri_idx++;
}


const int cupboard_front_num_vertices = 6;
int cupboard_front_tri_idx=0;
glm::vec4 cupboard_front_v_positions[cupboard_front_num_vertices];
glm::vec4 cupboard_front_v_colors[cupboard_front_num_vertices];
glm::vec4 cupboard_front_v_normals[cupboard_front_num_vertices];
glm::vec2 cupboard_front_tex_coords[cupboard_front_num_vertices];

void cupboard_front(void)
{
  cupboard_front_v_positions[cupboard_front_tri_idx] = cupboard_positions[4];
  cupboard_front_tex_coords[cupboard_front_tri_idx] = tex_cupboard[1];
  cupboard_front_tri_idx++;
  cupboard_front_v_positions[cupboard_front_tri_idx] = cupboard_positions[5];
  cupboard_front_tex_coords[cupboard_front_tri_idx] = tex_cupboard[0];
  cupboard_front_tri_idx++;
  cupboard_front_v_positions[cupboard_front_tri_idx] = cupboard_positions[6];
  cupboard_front_tex_coords[cupboard_front_tri_idx] = tex_cupboard[2];
  cupboard_front_tri_idx++;
  cupboard_front_v_positions[cupboard_front_tri_idx] = cupboard_positions[4];
  cupboard_front_tex_coords[cupboard_front_tri_idx] = tex_cupboard[1];
  cupboard_front_tri_idx++;
  cupboard_front_v_positions[cupboard_front_tri_idx] = cupboard_positions[6]; 
  cupboard_front_tex_coords[cupboard_front_tri_idx] = tex_cupboard[2];
  cupboard_front_tri_idx++;
  cupboard_front_v_positions[cupboard_front_tri_idx] = cupboard_positions[7]; 
  cupboard_front_tex_coords[cupboard_front_tri_idx] = tex_cupboard[3];
  cupboard_front_tri_idx++;
}

void cupboard(void)
{ 
  // Back
  cupboard_quad( 1, 0, 3, 2);
  // Right
  cupboard_quad( 2, 3, 7, 6);
  // Front
  // cupboard_quad( 4, 5, 6, 7);
  // Left
  cupboard_quad( 5, 4, 0, 1);
  // // Top
  cupboard_quad( 6, 5, 1, 2);
  // // Bottom
  cupboard_quad( 3, 0, 4, 7);
}

void init_cupboard()
{
  // ---- Create cupboard. All but front face.

  glGenVertexArrays (1, &cupboard_vao);
  glGenBuffers (1, &cupboard_vbo);

  glBindVertexArray (cupboard_vao);
  glBindBuffer (GL_ARRAY_BUFFER, cupboard_vbo);

  cupboard();

  glBufferData (GL_ARRAY_BUFFER, sizeof (cupboard_v_positions) + sizeof(cupboard_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(cupboard_v_positions), cupboard_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(cupboard_v_positions), sizeof(cupboard_tex_coords), cupboard_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(cupboard_v_positions)) );

  // ---- Create cupboard. Front face.

  glGenVertexArrays (1, &cupboard_front_vao);
  glGenBuffers (1, &cupboard_front_vbo);

  glBindVertexArray (cupboard_front_vao);
  glBindBuffer (GL_ARRAY_BUFFER, cupboard_front_vbo);

  cupboard_front();

  glBufferData (GL_ARRAY_BUFFER, sizeof (cupboard_front_v_positions) + sizeof(cupboard_front_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(cupboard_front_v_positions), cupboard_front_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(cupboard_front_v_positions), sizeof(cupboard_front_tex_coords), cupboard_front_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(cupboard_front_v_positions)) );
}

void draw_cupboard(glm::mat4 view_matrix) {
  // Draw all but front face
  GLuint tex = LoadTexture("images/cupboard.bmp", 256, 256);
  glBindTexture(GL_TEXTURE_2D, tex);

  glUniform1i(useTexture, 1);
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  glBindVertexArray (cupboard_vao);
  glDrawArrays(GL_TRIANGLES, 0, cupboard_num_vertices);

  // Draw front face
  tex = LoadTexture("images/all1.bmp", 256, 256);
  glBindTexture(GL_TEXTURE_2D, tex);

  glUniform1i(useTexture, 1);
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  glBindVertexArray (cupboard_front_vao);
  glDrawArrays(GL_TRIANGLES, 0, cupboard_front_num_vertices);
}
