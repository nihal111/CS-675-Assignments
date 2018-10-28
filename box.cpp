#include "glm/ext.hpp"
// quad generates two triangles for each face and assigns colors to the vertices
int box_quad(int a, int b, int c, int d, glm::vec4* box_vertices, glm::vec4 color, int tri_idx, 
  glm::vec4* box_positions, glm::vec4* box_colors, glm::vec4* box_normals)
{
  box_colors[tri_idx] = color; box_positions[tri_idx] = box_vertices[a];
  box_normals[tri_idx] = box_vertices[a];
  tri_idx++;
  box_colors[tri_idx] = color; box_positions[tri_idx] = box_vertices[b];
  box_normals[tri_idx] = box_vertices[b];
  tri_idx++;
  box_colors[tri_idx] = color; box_positions[tri_idx] = box_vertices[c];
  box_normals[tri_idx] = box_vertices[c];
  tri_idx++;
  box_colors[tri_idx] = color; box_positions[tri_idx] = box_vertices[a];
  box_normals[tri_idx] = box_vertices[a];
  tri_idx++;
  box_colors[tri_idx] = color; box_positions[tri_idx] = box_vertices[c];
  box_normals[tri_idx] = box_vertices[c];
  tri_idx++;
  box_colors[tri_idx] = color; box_positions[tri_idx] = box_vertices[d];
  box_normals[tri_idx] = box_vertices[d];
  tri_idx++;
  return tri_idx;
 }

csX75::HNode* get_box(glm::vec4* a_vertices, glm::vec4 a_color,
                      GLfloat _min_rx=-1, GLfloat _max_rx=-1, 
                      GLfloat _min_ry=-1, GLfloat _max_ry=-1, 
                      GLfloat _min_rz=-1, GLfloat _max_rz=-1) {
  int box_num_vertices = 36;
  int tri_id=0;
  glm::vec4 box_positions[36];
  glm::vec4 box_colors[36];
  glm::vec4 box_normals[36];

  tri_id = box_quad( 1, 0, 3, 2, a_vertices, a_color, tri_id, box_positions, box_colors, box_normals);
  tri_id = box_quad( 2, 3, 7, 6, a_vertices, a_color, tri_id, box_positions, box_colors, box_normals);
  tri_id = box_quad( 3, 0, 4, 7, a_vertices, a_color, tri_id, box_positions, box_colors, box_normals);
  tri_id = box_quad( 6, 5, 1, 2, a_vertices, a_color, tri_id, box_positions, box_colors, box_normals);
  tri_id = box_quad( 4, 5, 6, 7, a_vertices, a_color, tri_id, box_positions, box_colors, box_normals);
  tri_id = box_quad( 5, 4, 0, 1, a_vertices, a_color, tri_id, box_positions, box_colors, box_normals);

  csX75::HNode* box = new csX75::HNode(NULL, box_num_vertices, box_positions, box_colors, box_normals,
                  sizeof(box_positions), sizeof(box_colors), sizeof(box_normals),
                  _min_rx, _max_rx, _min_ry, _max_ry, _min_rz, _max_rz);
  return box;
}