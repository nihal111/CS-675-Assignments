GLuint door_vbo, door_vao;

glm::vec4 door_positions[8] = {
  glm::vec4(14, -10, -15, 1.0),
  glm::vec4(14, 5, -15, 1.0),
  glm::vec4(19, 5, -15, 1.0),
  glm::vec4(19, -10, -15, 1.0),
  glm::vec4(14, -10, -14.9, 1.0),
  glm::vec4(14, 5, -14.9, 1.0),
  glm::vec4(19, 5, -14.9, 1.0),
  glm::vec4(19, -10, -14.9, 1.0)
};

const int door_num_vertices = 36;
int door_tri_idx=0;
glm::vec4 door_v_positions[door_num_vertices];
glm::vec4 door_v_colors[door_num_vertices];
glm::vec4 door_v_normals[door_num_vertices];
glm::vec2 door_tex_coords[door_num_vertices];

glm::vec2 tex_door[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 5.0),
  glm::vec2( 5.0, 0.0),
  glm::vec2( 5.0, 5.0)
};

void door_quad(int a, int b, int c, int d)
{
  door_v_positions[door_tri_idx] = door_positions[a];
  door_tex_coords[door_tri_idx] = tex_door[1];
  door_tri_idx++;
  door_v_positions[door_tri_idx] = door_positions[b];
  door_tex_coords[door_tri_idx] = tex_door[0];
  door_tri_idx++;
  door_v_positions[door_tri_idx] = door_positions[c];
  door_tex_coords[door_tri_idx] = tex_door[2];
  door_tri_idx++;
  door_v_positions[door_tri_idx] = door_positions[a];
  door_tex_coords[door_tri_idx] = tex_door[1];
  door_tri_idx++;
  door_v_positions[door_tri_idx] = door_positions[c]; 
  door_tex_coords[door_tri_idx] = tex_door[2];
  door_tri_idx++;
  door_v_positions[door_tri_idx] = door_positions[d]; 
  door_tex_coords[door_tri_idx] = tex_door[3];
  door_tri_idx++;
}

void door(void)
{ 
   // Back
  door_quad( 1, 0, 3, 2);
  // Right
  door_quad( 2, 3, 7, 6);
  // Front
  door_quad( 4, 5, 6, 7);
  // Left
  door_quad( 5, 4, 0, 1);
  // // Top
  door_quad( 6, 5, 1, 2);
  // // Bottom
  door_quad( 3, 0, 4, 7);
}

void init_door()
{
  // ---- Create Door. 6 faces.

  glGenVertexArrays (1, &door_vao);
  glGenBuffers (1, &door_vbo);

  glBindVertexArray (door_vao);
  glBindBuffer (GL_ARRAY_BUFFER, door_vbo);

  door();

  glBufferData (GL_ARRAY_BUFFER, sizeof (door_v_positions) + sizeof(door_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(door_v_positions), door_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(door_v_positions), sizeof(door_tex_coords), door_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(door_v_positions)) );
}

void draw_door(glm::mat4 view_matrix) {
  GLuint tex = LoadTexture("images/door.bmp", 256, 256);
  glBindTexture(GL_TEXTURE_2D, tex);

  glUniform1i(useTexture, 1);
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  glBindVertexArray (door_vao);
  glDrawArrays(GL_TRIANGLES, 0, door_num_vertices);
}
