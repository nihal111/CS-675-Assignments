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

glm::vec2 tex_cupboard[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0)
};

const int cupboard_num_vertices = 30;
const int cupboard_front_num_vertices = 6;

void init_cupboard()
{
  // ---- Create cupboard. All but front face.

  glGenVertexArrays (1, &cupboard_vao);
  glGenBuffers (1, &cupboard_vbo);

  glBindVertexArray (cupboard_vao);
  glBindBuffer (GL_ARRAY_BUFFER, cupboard_vbo);

  glm::vec4 cupboard_v_positions[cupboard_num_vertices];
  glm::vec4 cupboard_v_normals[cupboard_num_vertices];
  glm::vec2 cupboard_tex_coords[cupboard_num_vertices];
  all_but_front_quads(cupboard_v_positions, cupboard_v_normals, cupboard_tex_coords, cupboard_positions, tex_cupboard);

  glBufferData (GL_ARRAY_BUFFER, sizeof (cupboard_v_positions) + sizeof(cupboard_v_normals) + sizeof(cupboard_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(cupboard_v_positions), cupboard_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(cupboard_v_positions), sizeof(cupboard_v_normals), cupboard_v_normals );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(cupboard_v_positions) + sizeof(cupboard_v_normals), sizeof(cupboard_tex_coords), cupboard_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(cupboard_v_positions)) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(cupboard_v_positions) + sizeof(cupboard_v_normals)) );

  // ---- Create cupboard. Front face.

  glGenVertexArrays (1, &cupboard_front_vao);
  glGenBuffers (1, &cupboard_front_vbo);

  glBindVertexArray (cupboard_front_vao);
  glBindBuffer (GL_ARRAY_BUFFER, cupboard_front_vbo);

  glm::vec4 cupboard_front_v_positions[cupboard_front_num_vertices];
  glm::vec4 cupboard_front_v_normals[cupboard_front_num_vertices];
  glm::vec2 cupboard_front_tex_coords[cupboard_front_num_vertices];
  front_quad(cupboard_front_v_positions, cupboard_front_v_normals, cupboard_front_tex_coords, cupboard_positions, tex_cupboard);

  glBufferData (GL_ARRAY_BUFFER, sizeof (cupboard_front_v_positions) + sizeof(cupboard_front_v_normals) + sizeof(cupboard_front_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(cupboard_front_v_positions), cupboard_front_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(cupboard_front_v_positions), sizeof(cupboard_front_v_normals), cupboard_front_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(cupboard_front_v_positions) + sizeof(cupboard_front_v_normals), sizeof(cupboard_front_tex_coords), cupboard_front_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(cupboard_front_v_positions)) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(cupboard_front_v_positions) + sizeof(cupboard_front_v_normals)) );
}

void draw_cupboard(glm::mat4 view_matrix) {
  draw_textured_object(view_matrix, &cupboard_vao, "images/light_wood.bmp", 100, 100, cupboard_num_vertices);
  draw_textured_object(view_matrix, &cupboard_front_vao, "images/cupboard_front.bmp", 256, 384, cupboard_front_num_vertices);
}
