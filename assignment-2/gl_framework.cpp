#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;
extern csX75::HNode *base_box, *lid, *curr_node;
extern csX75::HNode *left_upper_arm, *left_lower_arm, *right_upper_arm, *right_lower_arm, *left_hand, *right_hand,
                    *left_upper_leg, *left_lower_leg, *right_upper_leg, *right_lower_leg, *left_feet, *right_feet, 
                    *torso, *neck, *head;
extern csX75::HNode *r2d2_body, *r2d2_head, *r2d2_left_arm, *r2d2_right_arm, *r2d2_left_hand, *r2d2_right_hand;

namespace csX75
{
  enum Model
  {
    MUSIC_BOX,
    HUMAN,
    R2D2
  };

  Model model = MUSIC_BOX;

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
    
    else if (key == GLFW_KEY_1) {
      model = MUSIC_BOX;
      curr_node = lid;
      std::cout<<"Selected model MUSIC_BOX"<<std::endl;
    }
    else if (key == GLFW_KEY_2) {
      model = HUMAN;
      curr_node = torso;
      std::cout<<"Selected model HUMAN"<<std::endl;
    }
    else if (key == GLFW_KEY_3) {
      model = R2D2;
      curr_node = r2d2_body;
      std::cout<<"Selected model R2D2"<<std::endl;
    }

    else if (key == GLFW_KEY_P)
      enable_perspective = !enable_perspective;   

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

    else if (model == MUSIC_BOX) {
      if (key == GLFW_KEY_L) {
        curr_node = lid;
        std::cout<<"Model- MUSIC_BOX. Bone- lid"<<std::endl;
      }

      else if (key == GLFW_KEY_B) {
        curr_node = base_box;
        std::cout<<"Model- MUSIC_BOX. Bone- base_box"<<std::endl;
      }
    }

    else if (model == HUMAN) {
      if (key == GLFW_KEY_T) {
        curr_node = torso;
        std::cout<<"Model- Human. Bone- torso"<<std::endl;
      }
      else if (key == GLFW_KEY_Y) {
        curr_node = left_upper_arm;
        std::cout<<"Model- Human. Bone- left_upper_arm"<<std::endl;
      }
      else if (key == GLFW_KEY_U) {
        curr_node = left_lower_arm;
        std::cout<<"Model- Human. Bone- left_lower_arm"<<std::endl;
      }
      else if (key == GLFW_KEY_I) {
        curr_node = right_upper_arm;
        std::cout<<"Model- Human. Bone- right_upper_arm"<<std::endl;
      }
      else if (key == GLFW_KEY_O) {
        curr_node = right_lower_arm;
        std::cout<<"Model- Human. Bone- right_lower_arm"<<std::endl;
      }

      else if (key == GLFW_KEY_G) {
        curr_node = left_upper_leg;
        std::cout<<"Model- Human. Bone- left_upper_leg"<<std::endl;
      }
      else if (key == GLFW_KEY_H) {
        curr_node = left_lower_leg;
        std::cout<<"Model- Human. Bone- left_lower_leg"<<std::endl;
      }
      else if (key == GLFW_KEY_J) {
        curr_node = right_upper_leg;
        std::cout<<"Model- Human. Bone- right_upper_leg"<<std::endl;
      }
      else if (key == GLFW_KEY_K) {
        curr_node = right_lower_leg;
        std::cout<<"Model- Human. Bone- right_lower_leg"<<std::endl;
      }

      else if (key == GLFW_KEY_Z) {
        curr_node = left_hand;
        std::cout<<"Model- Human. Bone- left_hand"<<std::endl;
      }
      else if (key == GLFW_KEY_X) {
        curr_node = right_hand;
        std::cout<<"Model- Human. Bone- right_hand"<<std::endl;
      }
      else if (key == GLFW_KEY_C) {
        curr_node = left_feet;
        std::cout<<"Model- Human. Bone- left_feet"<<std::endl;
      }
      else if (key == GLFW_KEY_V) {
        curr_node = right_feet;
        std::cout<<"Model- Human. Bone- right_feet"<<std::endl;
      }

      else if (key == GLFW_KEY_N) {
        curr_node = neck;
        std::cout<<"Model- Human. Bone- neck"<<std::endl;
      }
      else if (key == GLFW_KEY_M) {
        curr_node = head;
        std::cout<<"Model- Human. Bone- head"<<std::endl;
      }
    }

    else if (model == R2D2) {
      if (key == GLFW_KEY_T) {
        curr_node = r2d2_body;
        std::cout<<"Model- R2D2. Bone- body"<<std::endl;
      }

      else if (key == GLFW_KEY_Y) {
        curr_node = r2d2_left_arm;
        std::cout<<"Model- R2D2. Bone- left_arm"<<std::endl;
      }
      else if (key == GLFW_KEY_U) {
        curr_node = r2d2_left_hand;
        std::cout<<"Model- R2D2. Bone- left_hand"<<std::endl;
      }
      else if (key == GLFW_KEY_I) {
        curr_node = r2d2_right_arm;
        std::cout<<"Model- R2D2. Bone- right_arm"<<std::endl;
      }
      else if (key == GLFW_KEY_O) {
        curr_node = r2d2_right_hand;
        std::cout<<"Model- R2D2. Bone- right_hand"<<std::endl;
      }

      else if (key == GLFW_KEY_H) {
        curr_node = r2d2_head;
        std::cout<<"Model- R2D2. Bone- head"<<std::endl;
      }
    }
  }
};  
  


