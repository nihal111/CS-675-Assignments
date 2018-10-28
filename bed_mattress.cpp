GLuint bed_mattress_vbo, bed_mattress_vao;
GLuint bed_mattress_front_vbo, bed_mattress_front_vao;

glm::vec4 bed_mattress_positions[8] = {
  glm::vec4(-18, -8, -14.9, 1.0),
  glm::vec4(-18, -7, -14.9, 1.0),
  glm::vec4(-0.1, -7, -14.9, 1.0),
  glm::vec4(-0.1, -8, -14.9, 1.0),
  glm::vec4(-18, -8, -5.1, 1.0),
  glm::vec4(-18, -7, -5.1, 1.0),
  glm::vec4(-0.1, -7, -5.1, 1.0),
  glm::vec4(-0.1, -8, -5.1, 1.0)
};

const int bed_mattress_num_vertices = 30;
int bed_mattress_tri_idx=0;
glm::vec4 bed_mattress_v_positions[bed_mattress_num_vertices];
glm::vec4 bed_mattress_v_colors[bed_mattress_num_vertices];
glm::vec4 bed_mattress_v_normals[bed_mattress_num_vertices];
glm::vec2 bed_mattress_tex_coords[bed_mattress_num_vertices];

glm::vec2 tex_bed_mattress[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 5.0),
  glm::vec2( 5.0, 0.0),
  glm::vec2( 5.0, 5.0)
};

void bed_mattress_quad(int a, int b, int c, int d)
{
  bed_mattress_v_positions[bed_mattress_tri_idx] = bed_mattress_positions[a];
  bed_mattress_tex_coords[bed_mattress_tri_idx] = tex_bed_mattress[1];
  bed_mattress_tri_idx++;
  bed_mattress_v_positions[bed_mattress_tri_idx] = bed_mattress_positions[b];
  bed_mattress_tex_coords[bed_mattress_tri_idx] = tex_bed_mattress[0];
  bed_mattress_tri_idx++;
  bed_mattress_v_positions[bed_mattress_tri_idx] = bed_mattress_positions[c];
  bed_mattress_tex_coords[bed_mattress_tri_idx] = tex_bed_mattress[2];
  bed_mattress_tri_idx++;
  bed_mattress_v_positions[bed_mattress_tri_idx] = bed_mattress_positions[a];
  bed_mattress_tex_coords[bed_mattress_tri_idx] = tex_bed_mattress[1];
  bed_mattress_tri_idx++;
  bed_mattress_v_positions[bed_mattress_tri_idx] = bed_mattress_positions[c]; 
  bed_mattress_tex_coords[bed_mattress_tri_idx] = tex_bed_mattress[2];
  bed_mattress_tri_idx++;
  bed_mattress_v_positions[bed_mattress_tri_idx] = bed_mattress_positions[d]; 
  bed_mattress_tex_coords[bed_mattress_tri_idx] = tex_bed_mattress[3];
  bed_mattress_tri_idx++;
}

void bed_mattress(void)
{ 
  // Back
  bed_mattress_quad( 1, 0, 3, 2);
  // Right
  bed_mattress_quad( 2, 3, 7, 6);
  // Front
  bed_mattress_quad( 4, 5, 6, 7);
  // Left
  bed_mattress_quad( 5, 4, 0, 1);
  // // Top
  bed_mattress_quad( 6, 5, 1, 2);
  // // Bottom
  bed_mattress_quad( 3, 0, 4, 7);
}

void init_bed_mattress()
{
  // ---- Create bed_mattress. All but front face.

  glGenVertexArrays (1, &bed_mattress_vao);
  glGenBuffers (1, &bed_mattress_vbo);

  glBindVertexArray (bed_mattress_vao);
  glBindBuffer (GL_ARRAY_BUFFER, bed_mattress_vbo);

  bed_mattress();

  glBufferData (GL_ARRAY_BUFFER, sizeof (bed_mattress_v_positions) + sizeof(bed_mattress_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(bed_mattress_v_positions), bed_mattress_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(bed_mattress_v_positions), sizeof(bed_mattress_tex_coords), bed_mattress_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(bed_mattress_v_positions)) );
}

void draw_bed_mattress(glm::mat4 view_matrix) {
  // Draw all but front face
  GLuint tex = LoadTexture("images/all1.bmp", 256, 256);
  glBindTexture(GL_TEXTURE_2D, tex);

  glUniform1i(useTexture, 1);
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  glBindVertexArray (bed_mattress_vao);
  glDrawArrays(GL_TRIANGLES, 0, bed_mattress_num_vertices);
}
