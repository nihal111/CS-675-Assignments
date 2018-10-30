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

glm::vec4 opening_box_platform_vertices[8] = {
  glm::vec4(-0.99, -0.05, 0.49, 1.0),
  glm::vec4(-0.99, 0.05, 0.49, 1.0),
  glm::vec4(0.99, 0.05, 0.49, 1.0),
  glm::vec4(0.99, -0.05, 0.49, 1.0),
  glm::vec4(-0.99, -0.05, -0.49, 1.0),
  glm::vec4(-0.99, 0.05, -0.49, 1.0),
  glm::vec4(0.99, 0.05, -0.49, 1.0),
  glm::vec4(0.99, -0.05, -0.49, 1.0)
};

glm::vec4 opening_box_lid_vertices[8] = {
  glm::vec4(-1.0, -0.05, 1.0, 1.0),
  glm::vec4(-1.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 0.0, 1.0, 1.0), 
  glm::vec4(1.0, -0.05, 1.0, 1.0),
  glm::vec4(-1.0, -0.05, 0.0, 1.0),
  glm::vec4(-1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0), 
  glm::vec4(1.0, -0.05, 0.0, 1.0)
};

glm::vec2 tex_box[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0)
};

const int base_box_num_vertices = 30;
const int lid_num_vertices = 36;
const int platform_num_vertices = 36;


void init_opening_box(void)
{
  glm::vec4 opening_box_base_positions[base_box_num_vertices];
  glm::vec2 opening_box_base_tex_coords[base_box_num_vertices];
  glm::vec4 opening_box_base_normals[base_box_num_vertices];

  all_but_top_quads(opening_box_base_positions, opening_box_base_normals, opening_box_base_tex_coords, opening_box_base_vertices, tex_box);

  base_box = new csX75::HNode(NULL, base_box_num_vertices, opening_box_base_positions, opening_box_base_tex_coords, opening_box_base_normals, 
    						  sizeof(opening_box_base_positions), sizeof(opening_box_base_tex_coords), sizeof(opening_box_base_normals),
    						  "images/dark_wood2.bmp", 100, 100, 
                  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f);
  base_box->change_parameters(-15,-3.49,7,  // translation
                         0.0,90.0,0.0);   // rotation

  glm::vec4 opening_box_lid_positions[lid_num_vertices];
  glm::vec2 opening_box_lid_tex_coords[lid_num_vertices];
  glm::vec4 opening_box_lid_normals[lid_num_vertices];

  all_quads(opening_box_lid_positions, opening_box_lid_normals, opening_box_lid_tex_coords, opening_box_lid_vertices, tex_box);

  lid = new csX75::HNode(base_box, lid_num_vertices, opening_box_lid_positions, opening_box_lid_tex_coords, opening_box_lid_normals,
                  sizeof(opening_box_lid_positions), sizeof(opening_box_lid_tex_coords), sizeof(opening_box_lid_normals),
                  "images/dark_wood2.bmp", 100, 100, 
                  -180.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  lid->change_parameters(0.0,0.5,-0.5,  // translation
                         0.0,0.0,0.0);   // rotation

  glm::vec4 opening_box_platform_positions[platform_num_vertices];
  glm::vec2 opening_box_platform_tex_coords[platform_num_vertices];
  glm::vec4 opening_box_platform_normals[platform_num_vertices];

  all_quads(opening_box_platform_positions, opening_box_platform_normals, opening_box_platform_tex_coords, opening_box_platform_vertices, tex_box);

  platform = new csX75::HNode(base_box, platform_num_vertices, opening_box_platform_positions, opening_box_platform_tex_coords, opening_box_platform_normals,
                  sizeof(opening_box_platform_positions), sizeof(opening_box_platform_tex_coords), sizeof(opening_box_platform_normals),
                  "images/light_wood.bmp", 100, 100, 
                  -180.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  platform->change_parameters(0.0,-0.45,0.0,  // translation
                         0.0,0.0,0.0);   // rotation

  curr_node = lid;

}

void box_state(float angle) {
  if (angle > 0 || angle < -180)
    return;
  lid->set_rx(angle);
  float platform_elev = -0.45 - 0.9 * angle/180.0;
  platform->set_ty(platform_elev);
}