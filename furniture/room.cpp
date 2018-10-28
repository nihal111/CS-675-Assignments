GLuint room_walls_vbo, room_walls_vao;
GLuint room_floor_vbo, room_floor_vao;
GLuint room_roof_vbo, room_roof_vao;

glm::vec4 room_positions[8] = {
  glm::vec4(-20, -10, 15, 1.0),
  glm::vec4(-20, 10, 15, 1.0),
  glm::vec4(20, 10, 15, 1.0),
  glm::vec4(20, -10, 15, 1.0),
  glm::vec4(-20, -10, -15, 1.0),
  glm::vec4(-20, 10, -15, 1.0),
  glm::vec4(20, 10, -15, 1.0),
  glm::vec4(20, -10, -15, 1.0)
};

glm::vec2 tex_room[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 5.0),
  glm::vec2( 5.0, 0.0),
  glm::vec2( 5.0, 5.0)
};

const int room_walls_num_vertices = 30;
const int room_floor_num_vertices = 6;
const int room_roof_num_vertices = 6;

void init_room()
{
  // ---- Create Room walls. Four sides.

  glGenVertexArrays (1, &room_walls_vao);
  glGenBuffers (1, &room_walls_vbo);

  glBindVertexArray (room_walls_vao);
  glBindBuffer (GL_ARRAY_BUFFER, room_walls_vbo);

  glm::vec4 room_walls_v_positions[room_walls_num_vertices];
  glm::vec4 room_walls_v_normals[room_walls_num_vertices];
  glm::vec2 room_walls_tex_coords[room_walls_num_vertices];
  sides_quads(room_walls_v_positions, room_walls_v_normals, room_walls_tex_coords, room_positions, tex_room);

  glBufferData (GL_ARRAY_BUFFER, sizeof (room_walls_v_positions) + sizeof (room_walls_v_normals) + sizeof(room_walls_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(room_walls_v_positions), room_walls_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(room_walls_v_positions), sizeof(room_walls_v_normals), room_walls_v_normals );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(room_walls_v_positions) + sizeof(room_walls_v_normals), sizeof(room_walls_tex_coords), room_walls_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(room_walls_v_positions)) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(room_walls_v_positions) + sizeof(room_walls_v_normals)) );



  // ---- Create Room Floor. Bottom of the Cube

  glGenVertexArrays (1, &room_floor_vao);
  glGenBuffers (1, &room_floor_vbo);

  glBindVertexArray (room_floor_vao);
  glBindBuffer (GL_ARRAY_BUFFER, room_floor_vbo);

  glm::vec4 room_floor_v_positions[room_floor_num_vertices];
  glm::vec4 room_floor_v_normals[room_floor_num_vertices];
  glm::vec2 room_floor_tex_coords[room_floor_num_vertices];
  bottom_quad(room_floor_v_positions, room_floor_v_normals, room_floor_tex_coords, room_positions, tex_room);

  glBufferData (GL_ARRAY_BUFFER, sizeof (room_floor_v_positions) + sizeof (room_floor_v_normals) + sizeof(room_floor_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(room_floor_v_positions), room_floor_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(room_floor_v_positions), sizeof(room_floor_v_normals), room_floor_v_normals );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(room_floor_v_positions) + sizeof(room_floor_v_normals), sizeof(room_floor_tex_coords), room_floor_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(room_floor_v_positions)) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(room_floor_v_positions) + sizeof(room_floor_v_normals)) );


  // ---- Create Room Roof. Top of the Cube
  glGenVertexArrays (1, &room_roof_vao);
  glGenBuffers (1, &room_roof_vbo);

  glBindVertexArray (room_roof_vao);
  glBindBuffer (GL_ARRAY_BUFFER, room_roof_vbo);

  glm::vec4 room_roof_v_positions[room_roof_num_vertices];
  glm::vec4 room_roof_v_normals[room_roof_num_vertices];
  glm::vec2 room_roof_tex_coords[room_roof_num_vertices];
  top_quad(room_roof_v_positions, room_roof_v_normals, room_roof_tex_coords, room_positions, tex_room);

  glBufferData (GL_ARRAY_BUFFER, sizeof (room_roof_v_positions) + sizeof (room_roof_v_normals) + sizeof(room_roof_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(room_roof_v_positions), room_roof_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(room_roof_v_positions), sizeof(room_roof_v_normals), room_roof_v_normals );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(room_roof_v_positions) + sizeof(room_roof_v_normals), sizeof(room_roof_tex_coords), room_roof_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(room_roof_v_positions)) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(room_roof_v_positions) + sizeof(room_roof_v_normals)) );
}

void draw_room(glm::mat4 view_matrix) {
  draw_textured_object(view_matrix, &room_walls_vao, "images/wall.bmp", 256, 256, room_walls_num_vertices);
  draw_textured_object(view_matrix, &room_floor_vao, "images/floor.bmp", 256, 256, room_floor_num_vertices);
  draw_textured_object(view_matrix, &room_roof_vao, "images/roof.bmp", 256, 256, room_roof_num_vertices);
}
