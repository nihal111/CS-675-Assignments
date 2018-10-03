#include "glm/ext.hpp"
// quad generates two triangles for each face and assigns colors to the vertices
int box_quad(int a, int b, int c, int d, glm::vec4* box_vertices, glm::vec4 color, int tri_idx, 
  glm::vec4* box_positions, glm::vec4* box_colors)
{
  box_colors[tri_idx] = color; box_positions[tri_idx] = box_vertices[a];
  tri_idx++;
  box_colors[tri_idx] = color; box_positions[tri_idx] = box_vertices[b];
  tri_idx++;
  box_colors[tri_idx] = color; box_positions[tri_idx] = box_vertices[c];
  tri_idx++;
  box_colors[tri_idx] = color; box_positions[tri_idx] = box_vertices[a];
  tri_idx++;
  box_colors[tri_idx] = color; box_positions[tri_idx] = box_vertices[c];
  tri_idx++;
  box_colors[tri_idx] = color; box_positions[tri_idx] = box_vertices[d];
  tri_idx++;
  return tri_idx;
 }

csX75::HNode* get_box(glm::vec4* a_vertices, glm::vec4 a_color) {
  int box_num_vertices = 36;
  int tri_id=0;
  glm::vec4 box_positions[36];
  glm::vec4 box_colors[36];

  tri_id = box_quad( 1, 0, 3, 2, a_vertices, a_color, tri_id, box_positions, box_colors);
  tri_id = box_quad( 2, 3, 7, 6, a_vertices, a_color, tri_id, box_positions, box_colors);
  tri_id = box_quad( 3, 0, 4, 7, a_vertices, a_color, tri_id, box_positions, box_colors);
  tri_id = box_quad( 6, 5, 1, 2, a_vertices, a_color, tri_id, box_positions, box_colors);
  tri_id = box_quad( 4, 5, 6, 7, a_vertices, a_color, tri_id, box_positions, box_colors);
  tri_id = box_quad( 5, 4, 0, 1, a_vertices, a_color, tri_id, box_positions, box_colors);

  std::cout<<glm::to_string(box_positions[4])<<std::endl;
  std::cout<<sizeof(box_positions) / sizeof(box_positions[0])<<std::endl;

  csX75::HNode* box = new csX75::HNode(NULL, box_num_vertices, box_positions, box_colors, 
                  sizeof(box_positions), sizeof(box_colors), 
                  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f);
  return box;
}