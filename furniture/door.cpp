GLuint door_vbo, door_vao;
GLuint door_front_vbo, door_front_vao;

glm::vec4 door_positions[8] = {
  glm::vec4(14, -10, -15, 1.0),
  glm::vec4(14, 5, -15, 1.0),
  glm::vec4(19, 5, -15, 1.0),
  glm::vec4(19, -10, -15, 1.0),
  glm::vec4(14, -10, -14.9, 1.0),
  glm::vec4(14, 5, -14.9, 1.0),
  glm::vec4(19, 5, -14.9, 1.0),
  glm::vec4(19, -10, -14.9, 1.0)
};;

glm::vec2 tex_door[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0)
};

const int door_num_vertices = 30;
const int door_front_num_vertices = 6;

void init_door()
{
  // ---- Create door. All but front face.

  glGenVertexArrays (1, &door_vao);
  glGenBuffers (1, &door_vbo);

  glBindVertexArray (door_vao);
  glBindBuffer (GL_ARRAY_BUFFER, door_vbo);

  glm::vec4 door_v_positions[door_num_vertices];
  glm::vec4 door_v_normals[door_num_vertices];
  glm::vec2 door_tex_coords[door_num_vertices];
  all_but_front_quads(door_v_positions, door_v_normals, door_tex_coords, door_positions, tex_door);

  glBufferData (GL_ARRAY_BUFFER, sizeof (door_v_positions) + sizeof(door_v_normals) + sizeof(door_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(door_v_positions), door_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(door_v_positions), sizeof(door_v_normals), door_v_normals );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(door_v_positions) + sizeof(door_v_normals), sizeof(door_tex_coords), door_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(door_v_positions)) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(door_v_positions) + sizeof(door_v_normals)) );

  // ---- Create door. Front face.

  glGenVertexArrays (1, &door_front_vao);
  glGenBuffers (1, &door_front_vbo);

  glBindVertexArray (door_front_vao);
  glBindBuffer (GL_ARRAY_BUFFER, door_front_vbo);

  glm::vec4 door_front_v_positions[door_front_num_vertices];
  glm::vec4 door_front_v_normals[door_front_num_vertices];
  glm::vec2 door_front_tex_coords[door_front_num_vertices];
  front_quad(door_front_v_positions, door_front_v_normals, door_front_tex_coords, door_positions, tex_door);

  glBufferData (GL_ARRAY_BUFFER, sizeof (door_front_v_positions) + sizeof(door_v_normals) + sizeof(door_front_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(door_front_v_positions), door_front_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(door_front_v_positions), sizeof(door_front_v_normals), door_front_v_normals );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(door_front_v_positions) + sizeof(door_front_v_normals), sizeof(door_front_tex_coords), door_front_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(door_front_v_positions)) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(door_front_v_positions) + sizeof(door_front_v_normals)) );
}

void draw_door(glm::mat4 view_matrix) {
  draw_textured_object(view_matrix, &door_vao, "images/dark_wood.bmp", 100, 100, door_num_vertices);
  draw_textured_object(view_matrix, &door_front_vao, "images/door.bmp", 100, 300, door_front_num_vertices);
}
