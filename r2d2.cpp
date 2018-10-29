
void init_r2d2()
{
  glm::vec4 r2d2_arm_vertices[8] = {
    glm::vec4(-0.02, -0.37, 0.05, 1.0),
    glm::vec4(-0.02, 0.0, 0.05, 1.0),
    glm::vec4(0.02, 0.0, 0.05, 1.0),
    glm::vec4(0.02, -0.37, 0.05, 1.0),
    glm::vec4(-0.02, -0.37, -0.05, 1.0),
    glm::vec4(-0.02, 0.0, -0.05, 1.0),
    glm::vec4(0.02, 0.0, -0.05, 1.0),
    glm::vec4(0.02, -0.37, -0.05, 1.0),
  };

  glm::vec4 r2d2_hand_vertices[8] = {
    glm::vec4(-0.019, -0.05, 0.1, 1.0),
    glm::vec4(-0.019, 0.0, 0.1, 1.0),
    glm::vec4(0.019, 0.0, 0.1, 1.0),
    glm::vec4(0.019, -0.05, 0.1, 1.0),
    glm::vec4(-0.019, -0.05, -0.1, 1.0),
    glm::vec4(-0.019, 0.0, -0.1, 1.0),
    glm::vec4(0.019, 0.0, -0.1, 1.0),
    glm::vec4(0.019, -0.05, -0.1, 1.0),
  };

  // -------------- BODY
  r2d2_body = get_cylinder(0.1, 0.1, 0.3, white);
  r2d2_body->set_parent(platform);
  r2d2_body->change_parameters(0.7,0.0,0.0,  // translation
                               0.0,0.0,0.0);   // rotation

  r2d2_head = get_ellipsoid(0.1, 0.1, 0.1, light_blue);
  r2d2_head->set_parent(r2d2_body);
  r2d2_head->change_parameters(0.0, 0.3, 0.0,
                          0.0, 0.0, 0.0);

  r2d2_left_arm = get_box(r2d2_arm_vertices, dark_blue,
                          -1,-1,
                          0.0,0.0,
                          0.0,0.0);
  r2d2_left_arm->set_parent(r2d2_body);
  r2d2_left_arm->change_parameters(-0.12, 0.3, 0.0,
                          0.0, 0.0, 0.0);

  r2d2_right_arm = get_box(r2d2_arm_vertices, dark_blue,
                          -1,-1,
                          0.0,0.0,                          
                          0.0,0.0);
  r2d2_right_arm->set_parent(r2d2_body);
  r2d2_right_arm->change_parameters(0.12, 0.3, 0.0,
                          0.0, 0.0, 0.0);

  r2d2_left_hand = get_box(r2d2_hand_vertices, blue,
                          -45.0,45.0,
                          0.0,0.0,                          
                          0.0,0.0);
  r2d2_left_hand->set_parent(r2d2_left_arm);
  r2d2_left_hand->change_parameters(0.0, -0.37, 0.0,
                          0.0, 0.0, 0.0);

  r2d2_right_hand = get_box(r2d2_hand_vertices, blue,
                          -45.0,45.0,
                          0.0,0.0,                          
                          0.0,0.0);
  r2d2_right_hand->set_parent(r2d2_right_arm);
  r2d2_right_hand->change_parameters(0.0, -0.37, 0.0,
                          0.0, 0.0, 0.0);
}