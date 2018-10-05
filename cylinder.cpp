int c_tesselation=50;

const int c_num_vertices = 300;

int c_tri_idx=0;
glm::vec4 c_v_positions[c_num_vertices];
glm::vec4 c_v_colors[c_num_vertices];
glm::vec4 c_v_normals[c_num_vertices];

void cylinder(double radius_x, double radius_y, double height_z)
{
  double hl = height_z * 0.5f;
  double a = 0.0f;
  double step = (2* PI) / (double) c_tesselation;

  for (int i = 0; i < c_tesselation; ++i)
  {
    float x = cos(a) * radius_x;
    float y = sin(a) * radius_y;

    glm::vec4 pt_down(x, -hl, y, 1.0);
    glm::vec4 pt_up(x, hl, y, 1.0);

    c_v_colors[c_tri_idx] = red; c_v_positions[c_tri_idx] = pt_down; 
    c_v_normals[c_tri_idx] = pt_down; c_tri_idx++;

    c_v_colors[c_tri_idx] = red; c_v_positions[c_tri_idx] = pt_up; 
    c_v_normals[c_tri_idx] = pt_up; c_tri_idx++;

    a += step;
  }

  a = c_tesselation - step;
  for (int i = 0; i < c_tesselation; ++i)
  {
    float x = cos(a) * radius_x;
    float y = sin(a) * radius_y;

    glm::vec4 pt(x, hl, y, 1.0);
    glm::vec4 center(0.0, hl, 0.0, 1.0);

    c_v_colors[c_tri_idx] = red; c_v_positions[c_tri_idx] = pt; 
    c_v_normals[c_tri_idx] = pt; c_tri_idx++;

    c_v_colors[c_tri_idx] = red; c_v_positions[c_tri_idx] = center; 
    c_v_normals[c_tri_idx] = center; c_tri_idx++;

    a -= step;
  }

  a = step;
  for (int i = 0; i < c_tesselation; ++i)
  {
    float x = cos(a) * radius_x;
    float y = sin(a) * radius_y;

    glm::vec4 pt(x, -hl, y, 1.0);
    glm::vec4 center(0.0, -hl, y, 1.0);

    c_v_colors[c_tri_idx] = red; c_v_positions[c_tri_idx] = pt; 
    c_v_normals[c_tri_idx] = pt; c_tri_idx++;

    c_v_colors[c_tri_idx] = red; c_v_positions[c_tri_idx] = center; 
    c_v_normals[c_tri_idx] = center; c_tri_idx++;

    a += step;
  }

}

csX75::HNode* get_cylinder(double r1, double r2, double l, glm::vec3 myRotationAxis, float angle, glm::vec3 translateVector) {
  cylinder(r1, r2, l);

  glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), angle, myRotationAxis);
  glm::mat4 transMatrix = glm::translate(glm::mat4(), translateVector);

  for (int i = 0; i < c_num_vertices; i++) {
    c_v_positions[i] = transMatrix*rotMatrix*c_v_positions[i];
  }

  csX75::HNode* cylindrical_joint = new csX75::HNode(NULL, c_num_vertices, c_v_positions, c_v_colors, 
                  sizeof(c_v_positions), sizeof(c_v_colors), 
                  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
                  GL_TRIANGLE_STRIP);
  return cylindrical_joint;
}

