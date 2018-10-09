/*
  CSX75 Tutorial 3

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by - 
               Harshavardhan Kode
*/

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "07_hierarchical_modelling.hpp"
#include "opening_box.cpp"
#include "box.cpp"
#include "cmath"
#include "ellipsoid.cpp"
#include "glm/ext.hpp"
#include "cylinder.cpp"

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;


//-----------------------------------------------------------------

glm::vec4 torso_vertices[8] = {
  glm::vec4(-0.1, -0.15, 0.03, 1.0),
  glm::vec4(-0.1, 0.15, 0.03, 1.0),
  glm::vec4(0.1, 0.15, 0.03, 1.0),
  glm::vec4(0.1, -0.15, 0.03, 1.0),
  glm::vec4(-0.1, -0.15, -0.03, 1.0),
  glm::vec4(-0.1, 0.15, -0.03, 1.0),
  glm::vec4(0.1, 0.15, -0.03, 1.0),
  glm::vec4(0.1, -0.15, -0.03, 1.0),
};

glm::vec4 left_arm_vertices[8] = {
  glm::vec4(-0.2, -0.04, 0.02, 1.0),
  glm::vec4(-0.2, 0.04, 0.02, 1.0),
  glm::vec4(0.0, 0.04, 0.02, 1.0),
  glm::vec4(0.0, -0.04, 0.02, 1.0),
  glm::vec4(-0.2, -0.04, -0.02, 1.0),
  glm::vec4(-0.2, 0.04, -0.02, 1.0),
  glm::vec4(0.0, 0.04, -0.02, 1.0),
  glm::vec4(0.0, -0.04, -0.02, 1.0),
};

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

glm::vec4 right_arm_vertices[8] = {
  glm::vec4(0.0, -0.04, 0.02, 1.0),
  glm::vec4(0.0, 0.04, 0.02, 1.0),
  glm::vec4(0.2, 0.04, 0.02, 1.0),
  glm::vec4(0.2, -0.04, 0.02, 1.0),
  glm::vec4(0.0, -0.04, -0.02, 1.0),
  glm::vec4(0.0, 0.04, -0.02, 1.0),
  glm::vec4(0.2, 0.04, -0.02, 1.0),
  glm::vec4(0.2, -0.04, -0.02, 1.0),
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

glm::vec4 leg_vertices[8] = {
  glm::vec4(-0.04, -0.2, 0.02, 1.0),
  glm::vec4(-0.04, 0.0, 0.02, 1.0),
  glm::vec4(0.04, 0.0, 0.02, 1.0),
  glm::vec4(0.04, -0.2, 0.02, 1.0),
  glm::vec4(-0.04, -0.2, -0.02, 1.0),
  glm::vec4(-0.04, 0.0, -0.02, 1.0),
  glm::vec4(0.04, 0.0, -0.02, 1.0),
  glm::vec4(0.04, -0.2, -0.02, 1.0),
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

glm::vec4 neck_vertices[8] = {
  glm::vec4(-0.03, 0.0, 0.02, 1.0),
  glm::vec4(-0.03, 0.02, 0.02, 1.0),
  glm::vec4(0.03, 0.02, 0.02, 1.0),
  glm::vec4(0.03, 0.0, 0.02, 1.0),
  glm::vec4(-0.03, 0.0, -0.02, 1.0),
  glm::vec4(-0.03, 0.02, -0.02, 1.0),
  glm::vec4(0.03, 0.02, -0.02, 1.0),
  glm::vec4(0.03, 0.0, -0.02, 1.0),
};

glm::vec4 head_vertices[8] = {
  glm::vec4(-0.06, 0.0, 0.02, 1.0),
  glm::vec4(-0.06, 0.12, 0.02, 1.0),
  glm::vec4(0.06, 0.12, 0.02, 1.0),
  glm::vec4(0.06, 0.0, 0.02, 1.0),
  glm::vec4(-0.06, 0.0, -0.02, 1.0),
  glm::vec4(-0.06, 0.12, -0.02, 1.0),
  glm::vec4(0.06, 0.12, -0.02, 1.0),
  glm::vec4(0.06, 0.0, -0.02, 1.0),
};

// Humanoid -------------------
csX75::HNode* torso;
csX75::HNode* neck;
csX75::HNode* head;

csX75::HNode* left_upper_arm;
csX75::HNode* left_lower_arm;
csX75::HNode* left_hand;
csX75::HNode* right_upper_arm;
csX75::HNode* right_lower_arm;
csX75::HNode* right_hand;

csX75::HNode* left_upper_leg;
csX75::HNode* left_lower_leg;
csX75::HNode* left_feet;
csX75::HNode* right_upper_leg;
csX75::HNode* right_lower_leg;
csX75::HNode* right_feet;

// R2D2 -----------------------
csX75::HNode* r2d2_body;
csX75::HNode* r2d2_head;
csX75::HNode* r2d2_left_arm;
csX75::HNode* r2d2_right_arm;
csX75::HNode* r2d2_left_hand;
csX75::HNode* r2d2_right_hand;

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

//-----------------------------------------------------------------

void init_humanoid()
{
  // -------------- TORSO
  torso = get_cylinder(0.1, 0.03, 0.30, dark_blue);
  torso->change_parameters(-1.35,0.0,0.0,  // translation
                            0.0,0.0,0.0);

  //--------------- ARMS

  left_upper_arm = get_cylinder(0.04, 0.04, 0.2, dark_blue,
                          -80.0,80.0,
                          -90.0,90.0,
                          0.0,180.0);
  left_upper_arm->set_parent(torso);
  left_upper_arm->change_parameters(-0.1,0.26,0.0,  // translation
                               0.0,0.0,90.0);   // rotation


  left_lower_arm = get_cylinder(0.04, 0.04, 0.2, light_blue,
                          0.0,170.0,
                          0.0,160.0,
                          0.0,0.0);
  left_lower_arm->set_parent(left_upper_arm);
  left_lower_arm->change_parameters(0.0,0.2,0.0,  // translation
                               0.0,0.0,0.0);   // rotation

  left_hand = get_box(left_hand_vertices, skin,
                          -80.0,80.0,
                          -10.0,10.0,
                          -120.0,-60.0);
  left_hand->set_parent(left_lower_arm);
  left_hand->change_parameters(0.0,0.2,0.0,  // translation
                               0.0,0.0, -90);   // rotation

  right_upper_arm = get_cylinder(0.04, 0.04, 0.2, dark_blue,
                          -80.0,80.0,
                          -90.0,90.0,
                          -180.0,0.0);
  right_upper_arm->set_parent(torso);
  right_upper_arm->change_parameters(0.1,0.26,0.0,  // translation
                               0.0,0.0,-90.0);   // rotation


  right_lower_arm = get_cylinder(0.04, 0.04, 0.2, light_blue,
                          0.0,170.0,
                          0.0,160.0,
                          0.0,0.0);
  right_lower_arm->set_parent(right_upper_arm);
  right_lower_arm->change_parameters(0.0,0.2,0.0,  // translation
                               0.0,0.0,0.0);   // rotation

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
                          0.0,0.0,
                          0.0,0.0,
                          0.0,0.0);
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

void init_r2d2()
{
  // -------------- BODY
  r2d2_body = get_cylinder(0.1, 0.1, 0.3, white);
  r2d2_body->change_parameters(1.5, 0.0, 0.0,
                               0.0, 0.0, 0.0);

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

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("07_vshader.glsl");
  std::string fragment_shader_file("07_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

  init_opening_box();

  init_humanoid();

  init_r2d2();
  
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    projection_matrix = glm::frustum(-2.0, 2.0, -2.0, 2.0, 1.0, 5.0);
    //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-2.0, 2.0, -2.0, 2.0, -5.0, 5.0);

  view_matrix = projection_matrix*lookat_matrix;

  matrixStack.push_back(view_matrix);

  base_box->render_tree();
  
  torso->render_tree();

  r2d2_body->render_tree();

}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(1024, 1024, "CS475/CS675 Tutorial 7: Hierarchical Modelling", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------

