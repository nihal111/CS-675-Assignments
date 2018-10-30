void init_humanoid()
{

  glm::vec4 left_hand_vertices[8] = {
    glm::vec4(-0.1, -0.04, 0.02, 1.0),
    glm::vec4(-0.1, 0.04, 0.02, 1.0),
    glm::vec4(0.0, 0.04, 0.02, 1.0),
    glm::vec4(0.0, -0.04, 0.02, 1.0),
    glm::vec4(-0.1, -0.04, -0.02, 1.0),
    glm::vec4(-0.1, 0.04, -0.02, 1.0),
    glm::vec4(0.0, 0.04, -0.02, 1.0),
    glm::vec4(0.0, -0.04, -0.02, 1.0),
  };

  glm::vec4 right_hand_vertices[8] = {
    glm::vec4(0.0, -0.04, 0.02, 1.0),
    glm::vec4(0.0, 0.04, 0.02, 1.0),
    glm::vec4(0.1, 0.04, 0.02, 1.0),
    glm::vec4(0.1, -0.04, 0.02, 1.0),
    glm::vec4(0.0, -0.04, -0.02, 1.0),
    glm::vec4(0.0, 0.04, -0.02, 1.0),
    glm::vec4(0.1, 0.04, -0.02, 1.0),
    glm::vec4(0.1, -0.04, -0.02, 1.0),
  };

  glm::vec4 feet_vertices[8] = {
    glm::vec4(-0.04, -0.02, -0.02, 1.0),
    glm::vec4(-0.04, 0.02, -0.02, 1.0),
    glm::vec4(0.04, 0.02, -0.02, 1.0),
    glm::vec4(0.04, -0.02, -0.02, 1.0),
    glm::vec4(-0.04, -0.02, 0.1, 1.0),
    glm::vec4(-0.04, 0.02, 0.1, 1.0),
    glm::vec4(0.04, 0.02, 0.1, 1.0),
    glm::vec4(0.04, -0.02, 0.1, 1.0),
  };

  // -------------- TORSO
  torso = get_cylinder(0.1, 0.03, 0.30, dark_blue);
  torso->set_parent(platform);
  torso->change_parameters(-0.5,0.46,0.0,  // translation
                            0.0,0.0,0.0);

  //--------------- ARMS

  left_upper_arm = get_cylinder(0.04, 0.04, 0.2, dark_blue,
                          -1,-1,
                          -1,-1,
                          -1,-1);
  left_upper_arm->set_parent(torso);
  left_upper_arm->change_parameters(-0.08,0.26,0.0,  // translation
                               90.0,30.0,90.0);   // rotation


  left_lower_arm = get_cylinder(0.04, 0.04, 0.2, light_blue,
                          0.0,170.0,
                          0.0,160.0,
                          0.0,0.0);
  left_lower_arm->set_parent(left_upper_arm);
  left_lower_arm->change_parameters(0.0,0.16,0.0,  // translation
                               70.0,0.0,0.0);   // rotation

  left_hand = get_box(left_hand_vertices, skin,
                          -80.0,80.0,
                          -10.0,10.0,
                          -120.0,-60.0);
  left_hand->set_parent(left_lower_arm);
  left_hand->change_parameters(0.0,0.2,0.0,  // translation
                               0.0,0.0, -90);   // rotation

  right_upper_arm = get_cylinder(0.04, 0.04, 0.2, dark_blue,
                          -1,-1,
                          -1,-1,
                          -1,-1);
  right_upper_arm->set_parent(torso);
  right_upper_arm->change_parameters(0.08,0.26,0.0,  // translation
                               90.0,-30.0,-90.0);   // rotation


  right_lower_arm = get_cylinder(0.04, 0.04, 0.2, light_blue,
                          0.0,170.0,
                          0.0,160.0,
                          0.0,0.0);
  right_lower_arm->set_parent(right_upper_arm);
  right_lower_arm->change_parameters(0.0,0.16,0.0,  // translation
                               70.0,0.0,0.0);   // rotation

  right_hand = get_box(right_hand_vertices, skin,
                          -80.0,80.0,
                          -10.0,10.0,
                          60.0,120.0);
  right_hand->set_parent(right_lower_arm);
  right_hand->change_parameters(0.0,0.2,0.0,  // translation
                               0.0,0.0, 90);   // rotation

  //--------------- LEGS

  left_upper_leg = get_cylinder(0.04, 0.04, 0.2, blue,
                          90.0,270.0,
                          -45.0, 45.0,
                          -45.0,45.0);
  left_upper_leg->set_parent(torso);
  left_upper_leg->change_parameters(-0.06,0.0,0.0,  // translation
                               180,0.0,0.0);   // rotation


  left_lower_leg = get_cylinder(0.04, 0.04, 0.2, blue,
                          0.0,160.0,
                          0.0,0.0,
                          0.0,0.0);
  left_lower_leg->set_parent(left_upper_leg);
  left_lower_leg->change_parameters(0.0, 0.2,0.0,  // translation
                               0.0,0.0,0.0);   // rotation

  left_feet = get_box(feet_vertices, black,
                          -30.0,30.0,
                          150.0,210.0,
                          -5.0,5.0);
  left_feet->set_parent(left_lower_leg);
  left_feet->change_parameters(0.0,0.22,0.0,  // translation
                               0.0,180,0.0);   // rotation

  right_upper_leg = get_cylinder(0.04, 0.04, 0.2, blue,
                          90.0,270.0,
                          -45.0, 45.0,
                          -45.0,45.0);
  right_upper_leg->set_parent(torso);
  right_upper_leg->change_parameters(0.06,0.0,0.0,  // translation
                               180,0.0,0.0);   // rotation


  right_lower_leg = get_cylinder(0.04, 0.04, 0.2, blue,
                          0.0,160.0,
                          0.0,0.0,
                          0.0,0.0);
  right_lower_leg->set_parent(right_upper_leg);
  right_lower_leg->change_parameters(0.0,0.2,0.0,  // translation
                               0.0,0.0,0.0);   // rotation

  right_feet = get_box(feet_vertices, black,
                          -30.0,30.0,
                          150.0,210.0,
                          -5.0,5.0);
  right_feet->set_parent(right_lower_leg);
  right_feet->change_parameters(0.0,0.22,0.0,  // translation
                               0.0,180,0.0);   // rotation

  //--------------- NECK

  neck = get_cylinder(0.03, 0.03, 0.02, skin,
                          -30.0,30.0,
                          -30.0,30.0,
                          -30.0,30.0);
  neck->set_parent(torso);
  neck->change_parameters(0.0, 0.3, 0.0,
                          0.0, 0.0, 0.0);

  //--------------- HEAD

  head = get_ellipsoid(0.06, 0.06, 0.06, skin,
                          -50.0,50.0,
                          -90.0,90.0,
                          0.0,0.0);
  head->set_parent(neck);
  head->change_parameters(0.0, 0.08, 0.0,
                          0.0, 0.0, 0.0);
}