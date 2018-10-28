
const int texcub_num_vertices = 36;
int texcub_tri_idx=0;
glm::vec4 texcub_v_positions[texcub_num_vertices];
glm::vec4 texcub_v_colors[texcub_num_vertices];
glm::vec4 texcub_v_normals[texcub_num_vertices];
glm::vec2 texcub_tex_coords[texcub_num_vertices];

glm::vec2 tex_texcub[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 5.0),
  glm::vec2( 5.0, 0.0),
  glm::vec2( 5.0, 5.0)
};

void texcub_quad(int a, int b, int c, int d, glm::vec4* texcub_positions)
{
  texcub_v_positions[texcub_tri_idx] = texcub_positions[a];
  texcub_tex_coords[texcub_tri_idx] = tex_texcub[0];
  texcub_tri_idx++;
  texcub_v_positions[texcub_tri_idx] = texcub_positions[b];
  texcub_tex_coords[texcub_tri_idx] = tex_texcub[1];
  texcub_tri_idx++;
  texcub_v_positions[texcub_tri_idx] = texcub_positions[c];
  texcub_tex_coords[texcub_tri_idx] = tex_texcub[3];
  texcub_tri_idx++;
  texcub_v_positions[texcub_tri_idx] = texcub_positions[a];
  texcub_tex_coords[texcub_tri_idx] = tex_texcub[0];
  texcub_tri_idx++;
  texcub_v_positions[texcub_tri_idx] = texcub_positions[c]; 
  texcub_tex_coords[texcub_tri_idx] = tex_texcub[3];
  texcub_tri_idx++;
  texcub_v_positions[texcub_tri_idx] = texcub_positions[d]; 
  texcub_tex_coords[texcub_tri_idx] = tex_texcub[2];
  texcub_tri_idx++;
}

void texcub(glm::vec4* texcub_positions)
{ 
  // Back
  texcub_quad( 1, 0, 3, 2, texcub_positions);
  // Right
  texcub_quad( 2, 3, 7, 6, texcub_positions);
  // Front
  texcub_quad( 4, 5, 6, 7, texcub_positions);
  // Left
  texcub_quad( 5, 4, 0, 1, texcub_positions);
  // // Top
  texcub_quad( 6, 5, 1, 2, texcub_positions);
  // // Bottom
  texcub_quad( 3, 0, 4, 7, texcub_positions);
}

void init_texcub(GLuint* texcub_vao, GLuint* texcub_vbo, glm::vec4* texcub_positions)
{
  // ---- Create texcub. All but front face.

  glGenVertexArrays (1, texcub_vao);
  glGenBuffers (1, texcub_vbo);

  glBindVertexArray (*texcub_vao);
  glBindBuffer (GL_ARRAY_BUFFER, *texcub_vbo);

  texcub_tri_idx=0;
  texcub(texcub_positions);

  glBufferData (GL_ARRAY_BUFFER, sizeof (texcub_v_positions) + sizeof(texcub_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(texcub_v_positions), texcub_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(texcub_v_positions), sizeof(texcub_tex_coords), texcub_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(texcub_v_positions)) );
}

void draw_texcub(glm::mat4 view_matrix, GLuint* texcub_vao, const char* filename) {
  // Draw all but front face
  GLuint tex = LoadTexture(filename, 256, 256);
  glBindTexture(GL_TEXTURE_2D, tex);

  glUniform1i(useTexture, 1);
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  glBindVertexArray (*texcub_vao);
  glDrawArrays(GL_TRIANGLES, 0, texcub_num_vertices);
}
