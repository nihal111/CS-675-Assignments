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

glm::vec2 tex_drawer[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0)
};

const int drawer_num_vertices = 30;
const int drawer_front_num_vertices = 6;

void init_drawer()
{
  // ---- Create drawer. All but front face.

  glGenVertexArrays (1, &drawer_vao);
  glGenBuffers (1, &drawer_vbo);

  glBindVertexArray (drawer_vao);
  glBindBuffer (GL_ARRAY_BUFFER, drawer_vbo);

  glm::vec4 drawer_v_positions[drawer_num_vertices];
  glm::vec4 drawer_v_normals[drawer_num_vertices];
  glm::vec2 drawer_tex_coords[drawer_num_vertices];
  all_but_front_quads(drawer_v_positions, drawer_v_normals, drawer_tex_coords, drawer_positions, tex_drawer);

  glBufferData (GL_ARRAY_BUFFER, sizeof (drawer_v_positions) + sizeof(drawer_v_normals) + sizeof(drawer_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(drawer_v_positions), drawer_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(drawer_v_positions), sizeof(drawer_v_positions), drawer_v_normals );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(drawer_v_positions) + sizeof(drawer_v_normals), sizeof(drawer_tex_coords), drawer_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(drawer_v_positions)) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(drawer_v_positions) + sizeof(drawer_v_normals)) );

  // ---- Create drawer. Front face.

  glGenVertexArrays (1, &drawer_front_vao);
  glGenBuffers (1, &drawer_front_vbo);

  glBindVertexArray (drawer_front_vao);
  glBindBuffer (GL_ARRAY_BUFFER, drawer_front_vbo);

  glm::vec4 drawer_front_v_positions[drawer_front_num_vertices];
  glm::vec4 drawer_front_v_normals[drawer_front_num_vertices];
  glm::vec2 drawer_front_tex_coords[drawer_front_num_vertices];
  front_quad(drawer_front_v_positions, drawer_front_v_normals, drawer_front_tex_coords, drawer_positions, tex_drawer);

  glBufferData (GL_ARRAY_BUFFER, sizeof (drawer_front_v_positions) + sizeof(drawer_front_v_normals) + sizeof(drawer_front_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(drawer_front_v_positions), drawer_front_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(drawer_front_v_positions), sizeof(drawer_front_v_normals), drawer_front_v_normals );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(drawer_front_v_positions) + sizeof(drawer_front_v_normals), sizeof(drawer_front_tex_coords), drawer_front_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(drawer_front_v_positions)) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(drawer_front_v_positions) + sizeof(drawer_front_v_normals)) );
}

void draw_drawer(glm::mat4 view_matrix) {
  draw_textured_object(view_matrix, &drawer_vao, "images/dark_wood.bmp", 100, 100, drawer_num_vertices);
  draw_textured_object(view_matrix, &drawer_front_vao, "images/drawer_front.bmp", 256, 512, drawer_front_num_vertices);
}
