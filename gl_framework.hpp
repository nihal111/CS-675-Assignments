#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "canvas.hpp"
#include "shader_util.hpp"

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

namespace csX75
{
  //! Initialize GL State
  void initGL(mydraw::canvas_t* mycanvas);
 
  //!GLFW Error Callback
  void error_callback(int error, const char* description);
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  //!GLFW mouse button callback
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
  //!GLFW display callback
  void display_callback(mydraw::canvas_t* mycanvas);

  //!Setup GL context and start main event loop  
  int render_gl(int argc, char** argv, mydraw::canvas_t* mycanvas);
};

