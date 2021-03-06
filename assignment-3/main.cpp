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

#include "main.hpp"
#include "cmath"
#include "glm/ext.hpp"

#include "texture.cpp"
#include "quad.cpp"

#include "box.cpp"
#include "ellipsoid.cpp"
#include "cylinder.cpp"

#include "opening_box.cpp"
#include "humanoid.cpp"
#include "r2d2.cpp"

#include "furniture/room.cpp"
#include "furniture/door.cpp"
#include "furniture/cupboard.cpp"
#include "furniture/drawer.cpp"
#include "furniture/bed.cpp"
#include "furniture/table.cpp"
#include "furniture/chair.cpp"
#include "furniture/window.cpp"
#include "furniture/wall_light.cpp"
#include "furniture/lamp.cpp"

#include "save_animation.cpp"

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;

int camera_pos_count = 0;
int frame_number = 1;
bool no_update = false;

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("vshader.glsl");
  std::string fragment_shader_file("fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" );
  vNormal = glGetAttribLocation( shaderProgram, "vNormal" );
  texCoord = glGetAttribLocation( shaderProgram, "texCoord" );
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
  viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");
  normalMatrix =  glGetUniformLocation( shaderProgram, "normalMatrix");
  useTexture = glGetUniformLocation( shaderProgram, "useTexture");

  light0ON = glGetUniformLocation( shaderProgram, "light0ON");
  light1ON = glGetUniformLocation( shaderProgram, "light1ON");


  init_opening_box();
  init_humanoid();
  init_r2d2();

  init_room();
  init_door();
  init_drawer();
  init_cupboard();
  init_bed();
  init_table();
  init_chair();
  init_window();
  init_wall_light();
  init_lamp();
  
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;

   // Start the camera animation.
  if (camera_animation_start && !direct_box_animation)
  {
    glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0);
    no_update = true;
    if (camera_pos_count < num_interpolated_points - 2)
    {
      camera_pos_count = camera_pos_update(camera_pos_count);
      //Creating the lookat matrix
      lookat_matrix = glm::lookAt(glm::vec3(c_pos),base_box_position,glm::vec3(c_up));
    }
    else
    {
      playback_init();
      // Stop the camera animation.
      camera_animation_start = false;
      start_playback = true;
      c_pos = glm::vec4(-11.5, -1.0, 7.0, 1.0);
    }
  }
  else if (start_playback || playback_running || direct_box_animation)
  {
    if (direct_box_animation && !box_playback_initialized)
    {
      playback_init();
      box_playback_initialized = true;
    }
    playback_update();
    lookat_matrix = glm::lookAt(glm::vec3(c_pos),base_box_position,glm::vec3(c_up));
  }
  else
  {
    if (!no_update)
    {
      c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
      //Creating the lookat matrix
      lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));
    }
  }

  //creating the projection matrix
  if(enable_perspective)
    projection_matrix = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 50.0);
    // projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,10.0);
  else
    projection_matrix = glm::ortho(-3.0, 3.0, -3.0, 3.0, 1.0, 50.0);

  view_matrix = projection_matrix*lookat_matrix;
  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  matrixStack.push_back(view_matrix);


  // ---- Draw the Room
  draw_room(view_matrix);
  draw_door(view_matrix);
  draw_drawer(view_matrix);
  draw_cupboard(view_matrix);
  draw_bed(view_matrix);
  draw_table(view_matrix);
  draw_chair(view_matrix);
  draw_window(view_matrix);
  draw_lamp(view_matrix);
  draw_wall_light();

  // ---- Draw the models
  base_box->render_tree();

  // ---- Draw the mouse clicks.
  if (!camera_animation_start && !playback_running)
  {
    for (int i = 0; i < mouse_count; i++)
    {
      glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
      glBindVertexArray (mouse_clicks_vao[i]);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, 3600);
    }
  }

  // ----Draw the interpolated cuve once the points are in place.
  if (points_in_place && !camera_animation_start && !playback_running)
  {
    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
    glBindVertexArray (mouse_curve_vao);
    glDrawArrays(GL_LINES, 0, 2*num_interpolated_points - 2);
  }

  if ((camera_animation_start || playback_running) && animation_update)
  {
    // Store the frames as the animation starts.
    save("frames/" + std::to_string(frame_number) + ".tga");
    frame_number++;

    // Combine TGA files to generate video.
    // ffmpeg -r 20 -f image2 -s 1920x1080 -i %d.tga -vcodec libx264 -crf 25  -pix_fmt yuv420p test.mp4
  }
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
  window = glfwCreateWindow(800, 800, "CS475/CS675 Tutorial 7: Hierarchical Modelling", NULL, NULL);
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

  glfwSetMouseButtonCallback(window, csX75::mouse_button_callback);

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

