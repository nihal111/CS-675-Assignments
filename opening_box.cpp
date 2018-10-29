const int base_box_num_vertices = 36;

glm::vec4 opening_box_base_vertices[8] = {
  glm::vec4(-1.0, -0.5, 0.5, 1.0),
  glm::vec4(-1.0, 0.5, 0.5, 1.0),
  glm::vec4(1.0, 0.5, 0.5, 1.0),
  glm::vec4(1.0, -0.5, 0.5, 1.0),
  glm::vec4(-1.0, -0.5, -0.5, 1.0),
  glm::vec4(-1.0, 0.5, -0.5, 1.0),
  glm::vec4(1.0, 0.5, -0.5, 1.0),
  glm::vec4(1.0, -0.5, -0.5, 1.0)
};

glm::vec4 opening_box_lid_vertices[4] = {
  glm::vec4(-1.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 0.0, 1.0, 1.0),
  glm::vec4(-1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0)
};

int opening_box_base_tri_idx=0;
glm::vec4 opening_box_base_positions[base_box_num_vertices];
glm::vec4 opening_box_base_colors[base_box_num_vertices];
glm::vec4 opening_box_base_normals[base_box_num_vertices];


// quad generates two triangles for each face and assigns colors to the vertices
void box_quad(int a, int b, int c, int d, glm::vec4 color)
{
  opening_box_base_colors[opening_box_base_tri_idx] = color; opening_box_base_positions[opening_box_base_tri_idx] = opening_box_base_vertices[a];
  opening_box_base_normals[opening_box_base_tri_idx] = opening_box_base_vertices[a];
  opening_box_base_tri_idx++;
  opening_box_base_colors[opening_box_base_tri_idx] = color; opening_box_base_positions[opening_box_base_tri_idx] = opening_box_base_vertices[b];
  opening_box_base_normals[opening_box_base_tri_idx] = opening_box_base_vertices[b];
  opening_box_base_tri_idx++;
  opening_box_base_colors[opening_box_base_tri_idx] = color; opening_box_base_positions[opening_box_base_tri_idx] = opening_box_base_vertices[c];
  opening_box_base_normals[opening_box_base_tri_idx] = opening_box_base_vertices[c];
  opening_box_base_tri_idx++;
  opening_box_base_colors[opening_box_base_tri_idx] = color; opening_box_base_positions[opening_box_base_tri_idx] = opening_box_base_vertices[a];
  opening_box_base_normals[opening_box_base_tri_idx] = opening_box_base_vertices[a];
  opening_box_base_tri_idx++;
  opening_box_base_colors[opening_box_base_tri_idx] = color; opening_box_base_positions[opening_box_base_tri_idx] = opening_box_base_vertices[c];
  opening_box_base_normals[opening_box_base_tri_idx] = opening_box_base_vertices[c];
  opening_box_base_tri_idx++;
  opening_box_base_colors[opening_box_base_tri_idx] = color; opening_box_base_positions[opening_box_base_tri_idx] = opening_box_base_vertices[d];
  opening_box_base_normals[opening_box_base_tri_idx] = opening_box_base_vertices[d];
  opening_box_base_tri_idx++;
 }


static const int lid_num_vertices = 6;
int opening_box_lid_tri_idx=0;
glm::vec4 opening_box_lid_positions[lid_num_vertices];
glm::vec4 opening_box_lid_colors[lid_num_vertices];
glm::vec4 opening_box_lid_normals[lid_num_vertices];

void lid_quad(int a, int b, int c, int d, glm::vec4 color)
{
  opening_box_lid_colors[opening_box_lid_tri_idx] = color; opening_box_lid_positions[opening_box_lid_tri_idx] = opening_box_lid_vertices[a];
  opening_box_lid_normals[opening_box_lid_tri_idx] = opening_box_lid_vertices[a];
  opening_box_lid_tri_idx++;
  opening_box_lid_colors[opening_box_lid_tri_idx] = color; opening_box_lid_positions[opening_box_lid_tri_idx] = opening_box_lid_vertices[b];
  opening_box_lid_normals[opening_box_lid_tri_idx] = opening_box_lid_vertices[b];
  opening_box_lid_tri_idx++;
  opening_box_lid_colors[opening_box_lid_tri_idx] = color; opening_box_lid_positions[opening_box_lid_tri_idx] = opening_box_lid_vertices[c];
  opening_box_lid_normals[opening_box_lid_tri_idx] = opening_box_lid_vertices[c];
  opening_box_lid_tri_idx++;
  opening_box_lid_colors[opening_box_lid_tri_idx] = color; opening_box_lid_positions[opening_box_lid_tri_idx] = opening_box_lid_vertices[a];
  opening_box_lid_normals[opening_box_lid_tri_idx] = opening_box_lid_vertices[a];
  opening_box_lid_tri_idx++;
  opening_box_lid_colors[opening_box_lid_tri_idx] = color; opening_box_lid_positions[opening_box_lid_tri_idx] = opening_box_lid_vertices[c];
  opening_box_lid_normals[opening_box_lid_tri_idx] = opening_box_lid_vertices[c];
  opening_box_lid_tri_idx++;
  opening_box_lid_colors[opening_box_lid_tri_idx] = color; opening_box_lid_positions[opening_box_lid_tri_idx] = opening_box_lid_vertices[d];
  opening_box_lid_normals[opening_box_lid_tri_idx] = opening_box_lid_vertices[d];
  opening_box_lid_tri_idx++;
 }

// generate 12 triangles: 36 vertices and 36 colors
void colorcube(void)
{
  box_quad( 1, 0, 3, 2, red);
  box_quad( 2, 3, 7, 6, green);
  box_quad( 3, 0, 4, 7, white);
  box_quad( 4, 5, 6, 7, grey);
  box_quad( 5, 4, 0, 1, blue);

  lid_quad( 3, 2, 0, 1, yellow);
}

void init_opening_box(void)
{
  colorcube();

  base_box = new csX75::HNode(NULL, base_box_num_vertices, opening_box_base_positions, opening_box_base_colors, opening_box_base_normals, 
    						  sizeof(opening_box_base_positions), sizeof(opening_box_base_colors), sizeof(opening_box_base_normals),
    						  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f);
  base_box->change_parameters(0.3,0.0,0.0,  // translation
                         0.0,0.0,0.0);   // rotation
  lid = new csX75::HNode(base_box, lid_num_vertices, opening_box_lid_positions, opening_box_lid_colors, opening_box_lid_normals,
    					 sizeof(opening_box_lid_positions), sizeof(opening_box_lid_colors), sizeof(opening_box_lid_normals),
    					 -180.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  lid->change_parameters(0.0,0.5,-0.5,  // translation
                         0.0,0.0,0.0);   // rotation
  curr_node = lid;

}