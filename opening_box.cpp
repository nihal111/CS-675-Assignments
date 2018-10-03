
const int base_box_num_vertices = 36;

glm::vec4 box_vertices[8] = {
  glm::vec4(-1.0, -0.5, 0.5, 1.0),
  glm::vec4(-1.0, 0.5, 0.5, 1.0),
  glm::vec4(1.0, 0.5, 0.5, 1.0),
  glm::vec4(1.0, -0.5, 0.5, 1.0),
  glm::vec4(-1.0, -0.5, -0.5, 1.0),
  glm::vec4(-1.0, 0.5, -0.5, 1.0),
  glm::vec4(1.0, 0.5, -0.5, 1.0),
  glm::vec4(1.0, -0.5, -0.5, 1.0)
};

glm::vec4 lid_vertices[4] = {
  glm::vec4(-1.0, 0.5, 0.5, 1.0),
  glm::vec4(1.0, 0.5, 0.5, 1.0),
  glm::vec4(-1.0, 0.5, -0.5, 1.0),
  glm::vec4(1.0, 0.5, -0.5, 1.0)
};

glm::vec4 color = glm::vec4(0.6, 0.6, 0.6, 1.0);
glm::vec4 grey = glm::vec4(0.3, 0.3, 0.3, 1.0);
glm::vec4 white = glm::vec4(0.2, 0.7, 0.7, 1.0);
glm::vec4 red = glm::vec4(1.0, 0.2, 0.2, 1.0);
glm::vec4 yellow = glm::vec4(0.8, 0.8, 0.0, 1.0);
glm::vec4 green = glm::vec4(0.2, 0.7, 0.2, 1.0);
glm::vec4 blue = glm::vec4(0.2, 0.2, 0.7, 1.0);

int tri_idx=0;
glm::vec4 base_box_positions[base_box_num_vertices];
glm::vec4 base_box_colors[base_box_num_vertices];


// quad generates two triangles for each face and assigns colors to the vertices
void box_quad(int a, int b, int c, int d, glm::vec4 color)
{
  base_box_colors[tri_idx] = color; base_box_positions[tri_idx] = box_vertices[a];
  tri_idx++;
  base_box_colors[tri_idx] = color; base_box_positions[tri_idx] = box_vertices[b];
  tri_idx++;
  base_box_colors[tri_idx] = color; base_box_positions[tri_idx] = box_vertices[c];
  tri_idx++;
  base_box_colors[tri_idx] = color; base_box_positions[tri_idx] = box_vertices[a];
  tri_idx++;
  base_box_colors[tri_idx] = color; base_box_positions[tri_idx] = box_vertices[c];
  tri_idx++;
  base_box_colors[tri_idx] = color; base_box_positions[tri_idx] = box_vertices[d];
  tri_idx++;
 }


static const int lid_num_vertices = 6;
int lid_tri_idx=0;
glm::vec4 lid_positions[lid_num_vertices];
glm::vec4 lid_colors[lid_num_vertices];

void lid_quad(int a, int b, int c, int d, glm::vec4 color)
{
  lid_colors[lid_tri_idx] = color; lid_positions[lid_tri_idx] = lid_vertices[a];
  lid_tri_idx++;
  lid_colors[lid_tri_idx] = color; lid_positions[lid_tri_idx] = lid_vertices[b];
  lid_tri_idx++;
  lid_colors[lid_tri_idx] = color; lid_positions[lid_tri_idx] = lid_vertices[c];
  lid_tri_idx++;
  lid_colors[lid_tri_idx] = color; lid_positions[lid_tri_idx] = lid_vertices[a];
  lid_tri_idx++;
  lid_colors[lid_tri_idx] = color; lid_positions[lid_tri_idx] = lid_vertices[c];
  lid_tri_idx++;
  lid_colors[lid_tri_idx] = color; lid_positions[lid_tri_idx] = lid_vertices[d];
  lid_tri_idx++;
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

  base_box = new csX75::HNode(NULL, base_box_num_vertices, base_box_positions, base_box_colors, 
    						  sizeof(base_box_positions), sizeof(base_box_colors),-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f);
  lid = new csX75::HNode(base_box, lid_num_vertices, lid_positions, lid_colors, 
    					 sizeof(lid_positions), sizeof(lid_colors),
    					 -180.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  lid->change_parameters(0.0,-0.5,0.5,  // translation
                         0.0,0.0,0.0,   // rotation
                         0.0,0.5,-0.5); // back translation
  curr_node = lid;

}