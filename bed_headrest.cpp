GLuint bed_headrest_vbo, bed_headrest_vao;
GLuint bed_headrest_front_vbo, bed_headrest_front_vao;

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

const int bed_headrest_num_vertices = 30;
int bed_headrest_tri_idx=0;
glm::vec4 bed_headrest_v_positions[bed_headrest_num_vertices];
glm::vec4 bed_headrest_v_colors[bed_headrest_num_vertices];
glm::vec4 bed_headrest_v_normals[bed_headrest_num_vertices];
glm::vec2 bed_headrest_tex_coords[bed_headrest_num_vertices];

glm::vec2 tex_bed_headrest[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 5.0),
  glm::vec2( 5.0, 0.0),
  glm::vec2( 5.0, 5.0)
};

void bed_headrest_quad(int a, int b, int c, int d)
{
  bed_headrest_v_positions[bed_headrest_tri_idx] = bed_headrest_positions[a];
  bed_headrest_tex_coords[bed_headrest_tri_idx] = tex_bed_headrest[1];
  bed_headrest_tri_idx++;
  bed_headrest_v_positions[bed_headrest_tri_idx] = bed_headrest_positions[b];
  bed_headrest_tex_coords[bed_headrest_tri_idx] = tex_bed_headrest[0];
  bed_headrest_tri_idx++;
  bed_headrest_v_positions[bed_headrest_tri_idx] = bed_headrest_positions[c];
  bed_headrest_tex_coords[bed_headrest_tri_idx] = tex_bed_headrest[2];
  bed_headrest_tri_idx++;
  bed_headrest_v_positions[bed_headrest_tri_idx] = bed_headrest_positions[a];
  bed_headrest_tex_coords[bed_headrest_tri_idx] = tex_bed_headrest[1];
  bed_headrest_tri_idx++;
  bed_headrest_v_positions[bed_headrest_tri_idx] = bed_headrest_positions[c]; 
  bed_headrest_tex_coords[bed_headrest_tri_idx] = tex_bed_headrest[2];
  bed_headrest_tri_idx++;
  bed_headrest_v_positions[bed_headrest_tri_idx] = bed_headrest_positions[d]; 
  bed_headrest_tex_coords[bed_headrest_tri_idx] = tex_bed_headrest[3];
  bed_headrest_tri_idx++;
}

void bed_headrest(void)
{ 
  // Back
  bed_headrest_quad( 1, 0, 3, 2);
  // Right
  bed_headrest_quad( 2, 3, 7, 6);
  // Front
  bed_headrest_quad( 4, 5, 6, 7);
  // Left
  bed_headrest_quad( 5, 4, 0, 1);
  // // Top
  bed_headrest_quad( 6, 5, 1, 2);
  // // Bottom
  bed_headrest_quad( 3, 0, 4, 7);
}

void init_bed_headrest()
{
  // ---- Create bed_headrest. All but front face.

  glGenVertexArrays (1, &bed_headrest_vao);
  glGenBuffers (1, &bed_headrest_vbo);

  glBindVertexArray (bed_headrest_vao);
  glBindBuffer (GL_ARRAY_BUFFER, bed_headrest_vbo);

  bed_headrest();

  glBufferData (GL_ARRAY_BUFFER, sizeof (bed_headrest_v_positions) + sizeof(bed_headrest_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(bed_headrest_v_positions), bed_headrest_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(bed_headrest_v_positions), sizeof(bed_headrest_tex_coords), bed_headrest_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(bed_headrest_v_positions)) );
}

void draw_bed_headrest(glm::mat4 view_matrix) {
  // Draw all but front face
  GLuint tex = LoadTexture("images/floor.bmp", 256, 256);
  glBindTexture(GL_TEXTURE_2D, tex);

  glUniform1i(useTexture, 1);
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  glBindVertexArray (bed_headrest_vao);
  glDrawArrays(GL_TRIANGLES, 0, bed_headrest_num_vertices);
}
