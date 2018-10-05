int tesselation=50;
int Lats = tesselation;
int Longs = tesselation;

double PI=3.14159265;
const int num_vertices = 3600;

int tri_idx=0;
glm::vec4 v_positions[num_vertices];
glm::vec4 v_colors[num_vertices];
glm::vec4 v_normals[num_vertices];

float phi_step=(180/(float(Lats)*10))/2;
float theta_step=(180/(float(Longs)*10))/2;

void sphere(double radius_x, double radius_y, double radius_z, int Lats, int Longs, glm::vec4 color)
{
  float theta, phi;

  // float phi_step=float(Lats)/100;
  // float theta_step=float(Longs)/100;


  float l;

  for (theta = 0.0; theta <= PI - theta_step / 2; theta+=theta_step)  
  {
    for(phi = 0.0; phi <= 2.0*PI + phi_step / 2; phi+=phi_step)
    {
      float x = radius_x * sin(theta) * cos(phi);
      float y = radius_y * sin(theta) * sin(phi);
      float z = radius_z * cos(theta);
      glm::vec4 pt(x, y, z, 1.0);

      v_colors[tri_idx] = color; v_positions[tri_idx] = pt; 
      v_normals[tri_idx] = pt; tri_idx++;

      if(theta+theta_step>PI)
        l=PI;
      else
        l=theta+theta_step;
      x = radius_x * sin(l) * cos(phi);
      y = radius_y * sin(l) * sin(phi);
      z = radius_z * cos(l);
      pt =glm::vec4(x, y, z, 1.0);
      v_colors[tri_idx] = red; v_positions[tri_idx] = pt; 
      v_normals[tri_idx] = pt; tri_idx++;
    }
  }
}

csX75::HNode* get_ellipsoid(double radius_x, double radius_y, double radius_z, glm::vec4 a_color,
                           GLfloat _min_rx=-1, GLfloat _max_rx=-1, 
                           GLfloat _min_ry=-1, GLfloat _max_ry=-1, 
                           GLfloat _min_rz=-1, GLfloat _max_rz=-1) {
  sphere(radius_x, radius_y, radius_z, Lats, Longs, a_color);

  csX75::HNode* ellipsoid = new csX75::HNode(NULL, num_vertices, v_positions, v_colors, 
                  sizeof(v_positions), sizeof(v_colors), 
                  _min_rx, _max_rx, _min_ry, _max_ry, _min_rz, _max_rz,
                  GL_TRIANGLE_STRIP);
  return ellipsoid;
}