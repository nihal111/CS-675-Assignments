#include "bed_base.cpp"
#include "bed_headrest.cpp"
#include "bed_mattress.cpp"

void init_bed() {
  init_bed_base();
  init_bed_headrest();
  init_bed_mattress();
}

void draw_bed(glm::mat4 view_matrix) {
  draw_bed_base(view_matrix);
  draw_bed_headrest(view_matrix);
  draw_bed_mattress(view_matrix);
}
