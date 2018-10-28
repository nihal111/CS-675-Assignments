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

const int room_walls_num_vertices = 30;
int room_walls_tri_idx=0;
glm::vec4 room_walls_v_positions[room_walls_num_vertices];
glm::vec4 room_walls_v_colors[room_walls_num_vertices];
glm::vec4 room_walls_v_normals[room_walls_num_vertices];
glm::vec2 room_walls_tex_coords[room_walls_num_vertices];

void wall_quad(int a, int b, int c, int d, glm::vec2* tex_coords)
{
  room_walls_v_positions[room_walls_tri_idx] = room_positions[a];
  room_walls_tex_coords[room_walls_tri_idx] = tex_coords[1];
  room_walls_tri_idx++;
  room_walls_v_positions[room_walls_tri_idx] = room_positions[b];
  room_walls_tex_coords[room_walls_tri_idx] = tex_coords[0];
  room_walls_tri_idx++;
  room_walls_v_positions[room_walls_tri_idx] = room_positions[c];
  room_walls_tex_coords[room_walls_tri_idx] = tex_coords[2];
  room_walls_tri_idx++;
  room_walls_v_positions[room_walls_tri_idx] = room_positions[a];
  room_walls_tex_coords[room_walls_tri_idx] = tex_coords[1];
  room_walls_tri_idx++;
  room_walls_v_positions[room_walls_tri_idx] = room_positions[c]; 
  room_walls_tex_coords[room_walls_tri_idx] = tex_coords[2];
  room_walls_tri_idx++;
  room_walls_v_positions[room_walls_tri_idx] = room_positions[d]; 
  room_walls_tex_coords[room_walls_tri_idx] = tex_coords[3];
  room_walls_tri_idx++;
}

glm::vec2 tex_coords[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 5.0),
  glm::vec2( 5.0, 0.0),
  glm::vec2( 5.0, 5.0)
};

void room_walls(void)
{ 
   // Back
  wall_quad( 1, 0, 3, 2, tex_coords);
  // Right
  wall_quad( 2, 3, 7, 6, tex_coords);
  // Front
  wall_quad( 4, 5, 6, 7, tex_coords);
  // Left
  wall_quad( 5, 4, 0, 1, tex_coords);
  // // Top
  // wall_quad( 6, 5, 1, 2, tex_coords);
  // // Bottom
  // wall_quad( 3, 0, 4, 7, tex_coords);
}

const int room_floor_num_vertices = 6;

int room_floor_tri_idx=0;
glm::vec4 room_floor_v_positions[room_floor_num_vertices];
glm::vec4 room_floor_v_colors[room_floor_num_vertices];
glm::vec4 room_floor_v_normals[room_floor_num_vertices];
glm::vec2 room_floor_tex_coords[room_floor_num_vertices];

void room_floor(void)
{ 
  // Bottom
  // quad( 3, 0, 4, 7, tex_coords);
  room_floor_v_positions[room_floor_tri_idx] = room_positions[3];
  room_floor_tex_coords[room_floor_tri_idx] = tex_coords[1];
  room_floor_tri_idx++;
  room_floor_v_positions[room_floor_tri_idx] = room_positions[0];
  room_floor_tex_coords[room_floor_tri_idx] = tex_coords[0];
  room_floor_tri_idx++;
  room_floor_v_positions[room_floor_tri_idx] = room_positions[4];
  room_floor_tex_coords[room_floor_tri_idx] = tex_coords[2];
  room_floor_tri_idx++;
  room_floor_v_positions[room_floor_tri_idx] = room_positions[3];
  room_floor_tex_coords[room_floor_tri_idx] = tex_coords[1];
  room_floor_tri_idx++;
  room_floor_v_positions[room_floor_tri_idx] = room_positions[4]; 
  room_floor_tex_coords[room_floor_tri_idx] = tex_coords[2];
  room_floor_tri_idx++;
  room_floor_v_positions[room_floor_tri_idx] = room_positions[7]; 
  room_floor_tex_coords[room_floor_tri_idx] = tex_coords[3];
  room_floor_tri_idx++;
}

const int room_roof_num_vertices = 6;

int room_roof_tri_idx=0;
glm::vec4 room_roof_v_positions[room_roof_num_vertices];
glm::vec4 room_roof_v_colors[room_roof_num_vertices];
glm::vec4 room_roof_v_normals[room_roof_num_vertices];
glm::vec2 room_roof_tex_coords[room_roof_num_vertices];

void room_roof(void)
{ 
  // Bottom
  // quad( 3, 0, 4, 7, tex_coords);
  room_roof_v_positions[room_roof_tri_idx] = room_positions[6];
  room_roof_tex_coords[room_roof_tri_idx] = tex_coords[1];
  room_roof_tri_idx++;
  room_roof_v_positions[room_roof_tri_idx] = room_positions[5];
  room_roof_tex_coords[room_roof_tri_idx] = tex_coords[0];
  room_roof_tri_idx++;
  room_roof_v_positions[room_roof_tri_idx] = room_positions[1];
  room_roof_tex_coords[room_roof_tri_idx] = tex_coords[2];
  room_roof_tri_idx++;
  room_roof_v_positions[room_roof_tri_idx] = room_positions[6];
  room_roof_tex_coords[room_roof_tri_idx] = tex_coords[1];
  room_roof_tri_idx++;
  room_roof_v_positions[room_roof_tri_idx] = room_positions[1]; 
  room_roof_tex_coords[room_roof_tri_idx] = tex_coords[2];
  room_roof_tri_idx++;
  room_roof_v_positions[room_roof_tri_idx] = room_positions[2]; 
  room_roof_tex_coords[room_roof_tri_idx] = tex_coords[3];
  room_roof_tri_idx++;
}

void init_room()
{
  // ---- Create Room walls. Four sides.

  glGenVertexArrays (1, &room_walls_vao);
  glGenBuffers (1, &room_walls_vbo);

  glBindVertexArray (room_walls_vao);
  glBindBuffer (GL_ARRAY_BUFFER, room_walls_vbo);

  room_walls();

  glBufferData (GL_ARRAY_BUFFER, sizeof (room_walls_v_positions) + sizeof(room_walls_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(room_walls_v_positions), room_walls_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(room_walls_v_positions), sizeof(room_walls_tex_coords), room_walls_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(room_walls_v_positions)) );



  // ---- Create Room Floor. Bottom of the Cube

  glGenVertexArrays (1, &room_floor_vao);
  glGenBuffers (1, &room_floor_vbo);

  glBindVertexArray (room_floor_vao);
  glBindBuffer (GL_ARRAY_BUFFER, room_floor_vbo);

  room_floor();

  glBufferData (GL_ARRAY_BUFFER, sizeof (room_floor_v_positions) + sizeof(room_floor_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(room_floor_v_positions), room_floor_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(room_floor_v_positions), sizeof(room_floor_tex_coords), room_floor_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(room_floor_v_positions)) );


  // ---- Create Room Roof. Top of the Cube
  glGenVertexArrays (1, &room_roof_vao);
  glGenBuffers (1, &room_roof_vbo);

  glBindVertexArray (room_roof_vao);
  glBindBuffer (GL_ARRAY_BUFFER, room_roof_vbo);

  room_roof();

  glBufferData (GL_ARRAY_BUFFER, sizeof (room_roof_v_positions) + sizeof(room_roof_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(room_roof_v_positions), room_roof_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(room_roof_v_positions), sizeof(room_roof_tex_coords), room_roof_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(room_roof_v_positions)) );
}

void draw_room_walls(glm::mat4 view_matrix) {
  GLuint tex = LoadTexture("images/wall.bmp", 256, 256);
  glBindTexture(GL_TEXTURE_2D, tex);

  glUniform1i(useTexture, 1);
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  glBindVertexArray (room_walls_vao);
  glDrawArrays(GL_TRIANGLES, 0, room_walls_num_vertices);
}

void draw_room_floor(glm::mat4 view_matrix) {
  GLuint tex = LoadTexture("images/floor.bmp", 256, 256);
  glBindTexture(GL_TEXTURE_2D, tex);

  glUniform1i(useTexture, 1);
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  glBindVertexArray (room_floor_vao);
  glDrawArrays(GL_TRIANGLES, 0, room_floor_num_vertices);
}

void draw_room_roof(glm::mat4 view_matrix) {
  GLuint tex = LoadTexture("images/roof.bmp", 256, 256);
  glBindTexture(GL_TEXTURE_2D, tex);

  glUniform1i(useTexture, 1);
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  glBindVertexArray (room_roof_vao);
  glDrawArrays(GL_TRIANGLES, 0, room_roof_num_vertices);
}

void draw_room(glm::mat4 view_matrix) {
  draw_room_walls(view_matrix);
  draw_room_roof(view_matrix);
  draw_room_floor(view_matrix);
}
