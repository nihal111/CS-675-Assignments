GLuint bed_base_vbo, bed_base_vao;
GLuint bed_base_front_vbo, bed_base_front_vao;

glm::vec4 bed_base_positions[8] = {
  glm::vec4(-20, -10, -15, 1.0),
  glm::vec4(-20, -8, -15, 1.0),
  glm::vec4(0, -8, -15, 1.0),
  glm::vec4(0, -10, -15, 1.0),
  glm::vec4(-20, -10, -5, 1.0),
  glm::vec4(-20, -8, -5, 1.0),
  glm::vec4(0, -8, -5, 1.0),
  glm::vec4(0, -10, -5, 1.0)
};

const int bed_base_num_vertices = 30;
int bed_base_tri_idx=0;
glm::vec4 bed_base_v_positions[bed_base_num_vertices];
glm::vec4 bed_base_v_colors[bed_base_num_vertices];
glm::vec4 bed_base_v_normals[bed_base_num_vertices];
glm::vec2 bed_base_tex_coords[bed_base_num_vertices];

glm::vec2 tex_bed_base[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 5.0),
  glm::vec2( 5.0, 0.0),
  glm::vec2( 5.0, 5.0)
};

void bed_base_quad(int a, int b, int c, int d)
{
  bed_base_v_positions[bed_base_tri_idx] = bed_base_positions[a];
  bed_base_tex_coords[bed_base_tri_idx] = tex_bed_base[1];
  bed_base_tri_idx++;
  bed_base_v_positions[bed_base_tri_idx] = bed_base_positions[b];
  bed_base_tex_coords[bed_base_tri_idx] = tex_bed_base[0];
  bed_base_tri_idx++;
  bed_base_v_positions[bed_base_tri_idx] = bed_base_positions[c];
  bed_base_tex_coords[bed_base_tri_idx] = tex_bed_base[2];
  bed_base_tri_idx++;
  bed_base_v_positions[bed_base_tri_idx] = bed_base_positions[a];
  bed_base_tex_coords[bed_base_tri_idx] = tex_bed_base[1];
  bed_base_tri_idx++;
  bed_base_v_positions[bed_base_tri_idx] = bed_base_positions[c]; 
  bed_base_tex_coords[bed_base_tri_idx] = tex_bed_base[2];
  bed_base_tri_idx++;
  bed_base_v_positions[bed_base_tri_idx] = bed_base_positions[d]; 
  bed_base_tex_coords[bed_base_tri_idx] = tex_bed_base[3];
  bed_base_tri_idx++;
}

void bed_base(void)
{ 
  // Back
  bed_base_quad( 1, 0, 3, 2);
  // Right
  bed_base_quad( 2, 3, 7, 6);
  // Front
  bed_base_quad( 4, 5, 6, 7);
  // Left
  bed_base_quad( 5, 4, 0, 1);
  // // Top
  bed_base_quad( 6, 5, 1, 2);
  // // Bottom
  bed_base_quad( 3, 0, 4, 7);
}

void init_bed_base()
{
  // ---- Create bed_base. All but front face.

  glGenVertexArrays (1, &bed_base_vao);
  glGenBuffers (1, &bed_base_vbo);

  glBindVertexArray (bed_base_vao);
  glBindBuffer (GL_ARRAY_BUFFER, bed_base_vbo);

  bed_base();

  glBufferData (GL_ARRAY_BUFFER, sizeof (bed_base_v_positions) + sizeof(bed_base_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(bed_base_v_positions), bed_base_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(bed_base_v_positions), sizeof(bed_base_tex_coords), bed_base_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(bed_base_v_positions)) );
}

void draw_bed_base(glm::mat4 view_matrix) {
  // Draw all but front face
  GLuint tex = LoadTexture("images/floor.bmp", 256, 256);
  glBindTexture(GL_TEXTURE_2D, tex);

  glUniform1i(useTexture, 1);
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  glBindVertexArray (bed_base_vao);
  glDrawArrays(GL_TRIANGLES, 0, bed_base_num_vertices);
}
