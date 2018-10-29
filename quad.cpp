
void create_quad(int a, int b, int c, int d, 
               glm::vec4* v_positions, glm::vec4* v_normals,
               glm::vec2* tex_coords,
               glm::vec4* positions, glm::vec2* tex, 
               int& tri_idx, glm::vec4 center)
{
  v_positions[tri_idx] = positions[a];
  v_normals[tri_idx] = positions[a] - center;
  tex_coords[tri_idx] = tex[0];
  tri_idx++;
  v_positions[tri_idx] = positions[b];
  v_normals[tri_idx] = positions[b] - center;
  tex_coords[tri_idx] = tex[1];
  tri_idx++;
  v_positions[tri_idx] = positions[c];
  v_normals[tri_idx] = positions[c] - center;
  tex_coords[tri_idx] = tex[3];
  tri_idx++;
  v_positions[tri_idx] = positions[a];
  v_normals[tri_idx] = positions[a] - center;
  tex_coords[tri_idx] = tex[0];
  tri_idx++;
  v_positions[tri_idx] = positions[c]; 
  v_normals[tri_idx] = positions[c]; - center; 
  tex_coords[tri_idx] = tex[3];
  tri_idx++;
  v_positions[tri_idx] = positions[d]; 
  v_normals[tri_idx] = positions[d]; - center;
  tex_coords[tri_idx] = tex[2];
  tri_idx++;
}

glm::vec4 find_center(glm::vec4* positions)
{
  glm::vec4 center = glm::vec4(0.0, 0.0, 0.0, 0.0);
  for (int i = 0; i < 8; i++) {
    center += positions[i];
  }
  return center;
}

void front_quad(glm::vec4* v_positions, glm::vec4* v_normals, glm::vec2* tex_coords, glm::vec4* positions, glm::vec2* tex_uv)
{ 
  int tri_idx=0;
  glm::vec4 center = find_center(positions);
  create_quad( 4, 5, 6, 7, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
}

void top_quad(glm::vec4* v_positions, glm::vec4* v_normals, glm::vec2* tex_coords, glm::vec4* positions, glm::vec2* tex_uv)
{ 
  int tri_idx=0;
  glm::vec4 center = find_center(positions);
  create_quad( 6, 5, 1, 2, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
}

void bottom_quad(glm::vec4* v_positions, glm::vec4* v_normals, glm::vec2* tex_coords, glm::vec4* positions, glm::vec2* tex_uv)
{ 
  int tri_idx=0;
  glm::vec4 center = find_center(positions);
  create_quad( 3, 0, 4, 7, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
}

void all_but_front_quads(glm::vec4* v_positions, glm::vec4* v_normals, glm::vec2* tex_coords, glm::vec4* positions, glm::vec2* tex_uv)
{ 
  int tri_idx=0;
  glm::vec4 center = find_center(positions);

  // Back
  create_quad( 1, 0, 3, 2, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // Right
  create_quad( 2, 3, 7, 6, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // Front
  // create_quad( 4, 5, 6, 7, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // Left
  create_quad( 5, 4, 0, 1, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // Top
  create_quad( 6, 5, 1, 2, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // Bottom
  create_quad( 3, 0, 4, 7, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
}

void sides_quads(glm::vec4* v_positions, glm::vec4* v_normals, glm::vec2* tex_coords, glm::vec4* positions, glm::vec2* tex_uv)
{ 
  int tri_idx=0;
  glm::vec4 center = find_center(positions);

  // Back
  create_quad( 1, 0, 3, 2, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // Right
  create_quad( 2, 3, 7, 6, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // Front
  create_quad( 4, 5, 6, 7, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // Left
  create_quad( 5, 4, 0, 1, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // // Top
  // create_quad( 6, 5, 1, 2, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // // Bottom
  // create_quad( 3, 0, 4, 7, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
}

void all_quads(glm::vec4* v_positions, glm::vec4* v_normals, glm::vec2* tex_coords, glm::vec4* positions, glm::vec2* tex_uv)
{ 
  int tri_idx=0;
  glm::vec4 center = find_center(positions);

  // Back
  create_quad( 1, 0, 3, 2, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // Right
  create_quad( 2, 3, 7, 6, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // Front
  create_quad( 4, 5, 6, 7, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // Left
  create_quad( 5, 4, 0, 1, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // Top
  create_quad( 6, 5, 1, 2, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
  // Bottom
  create_quad( 3, 0, 4, 7, v_positions, v_normals, tex_coords, positions, tex_uv, tri_idx, center);
}


const int texcub_num_vertices = 36;

glm::vec2 tex_texcub[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0)
};

void init_texcub(GLuint* texcub_vao, GLuint* texcub_vbo, glm::vec4* texcub_positions)
{
  glGenVertexArrays (1, texcub_vao);
  glGenBuffers (1, texcub_vbo);

  glBindVertexArray (*texcub_vao);
  glBindBuffer (GL_ARRAY_BUFFER, *texcub_vbo);

  glm::vec4 texcub_v_positions[texcub_num_vertices];
  glm::vec4 texcub_v_normals[texcub_num_vertices];
  glm::vec2 texcub_tex_coords[texcub_num_vertices];
  all_quads(texcub_v_positions, texcub_v_normals, texcub_tex_coords, texcub_positions, tex_texcub);

  glBufferData (GL_ARRAY_BUFFER, sizeof (texcub_v_positions) + sizeof(texcub_v_normals) + sizeof(texcub_tex_coords), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(texcub_v_positions), texcub_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(texcub_v_positions), sizeof(texcub_v_normals), texcub_v_normals );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(texcub_v_positions) + sizeof(texcub_v_normals), sizeof(texcub_tex_coords), texcub_tex_coords);

  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(texcub_v_positions)) );
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(texcub_v_positions) + sizeof(texcub_v_normals)) );
}
