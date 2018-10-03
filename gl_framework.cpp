#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;
extern csX75::HNode *base_box, *lid, *curr_node, *upper_arm, *lower_arm;
namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_1)
      curr_node = upper_arm;  
    else if (key == GLFW_KEY_2)
      curr_node = lower_arm;
    else if (key == GLFW_KEY_LEFT)
      curr_node->dec_ry();
    else if (key == GLFW_KEY_RIGHT)
      curr_node->inc_ry();
    else if (key == GLFW_KEY_UP)
      curr_node->dec_rx();
    else if (key == GLFW_KEY_DOWN)
      curr_node->inc_rx();
    else if (key == GLFW_KEY_PAGE_UP)
      curr_node->dec_rz();
    else if (key == GLFW_KEY_PAGE_DOWN)
      curr_node->inc_rz();
    else if (key == GLFW_KEY_P)
      enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_A)
      c_yrot -= 1.0;
    else if (key == GLFW_KEY_D)
      c_yrot += 1.0;
    else if (key == GLFW_KEY_W)
      c_xrot -= 1.0;
    else if (key == GLFW_KEY_S)
      c_xrot += 1.0;        
    else if (key == GLFW_KEY_Q)
      c_zrot -= 1.0;
    else if (key == GLFW_KEY_E)
      c_zrot += 1.0;   
  }
};  
  


