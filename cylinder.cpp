const int c_tesselation=50;
const int c_num_vertices = c_tesselation * 6;

void cylinder(double radius_x, double radius_y, double height_z, int c_tesselation,
              glm::vec4 c_color, glm::vec4* c_v_positions, glm::vec4* c_v_colors)
{
  int c_tri_idx = 0;
  double hl = height_z;
  double a = 0.0f;
  double step = (2* PI) / (double) c_tesselation;

  for (int i = 0; i < c_tesselation; ++i)
  {
    float x = cos(a) * radius_x;
    float y = sin(a) * radius_y;

    glm::vec4 pt_down(x, 0.0, y, 1.0);
    glm::vec4 pt_up(x, hl, y, 1.0);

    c_v_colors[c_tri_idx] = c_color; c_v_positions[c_tri_idx] = pt_down; 
    c_tri_idx++;

    c_v_colors[c_tri_idx] = c_color; c_v_positions[c_tri_idx] = pt_up; 
    c_tri_idx++;

    a += step;
  }

  a = c_tesselation - step;
  for (int i = 0; i < c_tesselation; ++i)
  {
    float x = cos(a) * radius_x;
    float y = sin(a) * radius_y;

    glm::vec4 pt(x, hl, y, 1.0);
    glm::vec4 center(0.0, hl, 0.0, 1.0);

    c_v_colors[c_tri_idx] = c_color; c_v_positions[c_tri_idx] = pt; 
    c_tri_idx++;

    c_v_colors[c_tri_idx] = c_color; c_v_positions[c_tri_idx] = center; 
    c_tri_idx++;

    a -= step;
  }

  a = step;
  for (int i = 0; i < c_tesselation; ++i)
  {
    float x = cos(a) * radius_x;
    float y = sin(a) * radius_y;

    glm::vec4 pt(x, 0.0, y, 1.0);
    glm::vec4 center(0.0, 0.0, y, 1.0);

    c_v_colors[c_tri_idx] = c_color; c_v_positions[c_tri_idx] = pt; 
    c_tri_idx++;

    c_v_colors[c_tri_idx] = c_color; c_v_positions[c_tri_idx] = center; 
    c_tri_idx++;

    a += step;
  }

}

csX75::HNode* get_cylinder(double r1, double r2, double l, glm::vec4 a_color,
                           GLfloat _min_rx=-1, GLfloat _max_rx=-1, 
                           GLfloat _min_ry=-1, GLfloat _max_ry=-1, 
                           GLfloat _min_rz=-1, GLfloat _max_rz=-1) {
  glm::vec4 c_v_positions[c_num_vertices];
  glm::vec4 c_v_colors[c_num_vertices];
  
  cylinder(r1, r2, l, c_tesselation, a_color, c_v_positions, c_v_colors);

  csX75::HNode* cylindrical_joint = new csX75::HNode(NULL, c_num_vertices, c_v_positions, c_v_colors, 
                  sizeof(c_v_positions), sizeof(c_v_colors), 
                  _min_rx, _max_rx, _min_ry, _max_ry, _min_rz, _max_rz,
                  GL_TRIANGLE_STRIP);
  return cylindrical_joint;
}