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
#include "opening_box.cpp"
#include "box.cpp"
#include "cmath"
#include "ellipsoid.cpp"
#include "glm/ext.hpp"
#include "cylinder.cpp"
#include "texture.cpp"

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;
glm::mat3 normal_matrix;

GLuint uModelViewMatrix;

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

//-----------------------------------------------------------------
GLuint roomUModelViewMatrix;
GLuint roomViewMatrix;
GLuint roomNormalMatrix;
GLuint vbo[2], vao[2];

glm::vec4 room_positions[8] = {
  glm::vec4(-0.5, -0.5, 0.5, 1.0),
  glm::vec4(-0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, -0.5, 0.5, 1.0),
  glm::vec4(-0.5, -0.5, -0.5, 1.0),
  glm::vec4(-0.5, 0.5, -0.5, 1.0),
  glm::vec4(0.5, 0.5, -0.5, 1.0),
  glm::vec4(0.5, -0.5, -0.5, 1.0)
};

glm::vec4 room_normals[8] = {
  glm::vec4(-0.5, -0.5, 0.5, 1.0),
  glm::vec4(-0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, 0.5, 0.5, 1.0),
  glm::vec4(0.5, -0.5, 0.5, 1.0),
  glm::vec4(-0.5, -0.5, -0.5, 1.0),
   glm::vec4(-0.5, 0.5, -0.5, 1.0),
  glm::vec4(0.5, 0.5, -0.5, 1.0),
  glm::vec4(0.5, -0.5, -0.5, 1.0)
};
//RGBA colors
glm::vec4 room_colors[8] = {
  glm::vec4(0.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(0.0, 1.0, 1.0, 1.0)
};

glm::vec2 room_t_coords[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0)
};

//6 faces, 2 triangles/face, 3 vertices/triangle
const int room_num_vertices = 36;

// generate 12 triangles: 36 vertices and 36 colors
int room_tri_idx=0;
glm::vec4 room_v_positions[room_num_vertices];
glm::vec4 room_v_colors[room_num_vertices];
glm::vec4 room_v_normals[room_num_vertices];
glm::vec2 room_tex_coords[room_num_vertices];
void quad(int a, int b, int c, int d, glm::vec4 color)
{
  room_v_colors[room_tri_idx] = color; room_v_positions[room_tri_idx] = room_positions[a];
  room_v_normals[room_tri_idx] = room_normals[a];
  room_tex_coords[room_tri_idx] = room_t_coords[1];
  room_tri_idx++;
  room_v_colors[room_tri_idx] = color; room_v_positions[room_tri_idx] = room_positions[b];
  room_v_normals[room_tri_idx] = room_normals[b]; 
  room_tex_coords[room_tri_idx] = room_t_coords[0];
  room_tri_idx++;
  room_v_colors[room_tri_idx] = color; room_v_positions[room_tri_idx] = room_positions[c];
  room_v_normals[room_tri_idx] = room_normals[c];
  room_tex_coords[room_tri_idx] = room_t_coords[2];
  room_tri_idx++;
  room_v_colors[room_tri_idx] = color; room_v_positions[room_tri_idx] = room_positions[a];
  room_v_normals[room_tri_idx] = room_normals[a];
  room_tex_coords[room_tri_idx] = room_t_coords[1];
  room_tri_idx++;
  room_v_colors[room_tri_idx] = color; room_v_positions[room_tri_idx] = room_positions[c]; 
  room_v_normals[room_tri_idx] = room_normals[c]; 
  room_tex_coords[room_tri_idx] = room_t_coords[2];
  room_tri_idx++;
  room_v_colors[room_tri_idx] = color; room_v_positions[room_tri_idx] = room_positions[d]; 
  room_v_normals[room_tri_idx] = room_normals[d]; 
  room_tex_coords[room_tri_idx] = room_t_coords[3];
  room_tri_idx++;
}

void room_colorcube(void)
{
  quad( 1, 0, 3, 2, red);
  quad( 2, 3, 7, 6, green);
  quad( 3, 0, 4, 7, white);
  quad( 6, 5, 1, 2, yellow);
  quad( 4, 5, 6, 7, black);
  quad( 5, 4, 0, 1, blue);
}

void init_room()
{
  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("06_vshader.glsl");
  std::string fragment_shader_file("06_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
  GLuint vNormal = glGetAttribLocation( shaderProgram, "vNormal" );
  GLuint texCoord = glGetAttribLocation( shaderProgram, "texCoord" );
  roomUModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
  roomNormalMatrix =  glGetUniformLocation( shaderProgram, "normalMatrix");
  roomViewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");

  // Load Textures
  GLuint tex = LoadTexture("images/all.bmp",256,256);
  glBindTexture(GL_TEXTURE_2D, tex);

  //Ask GL for two Vertex Attribute Objects (vao) , one for the sphere and one for the wireframe
  glGenVertexArrays (2, vao);
  //Ask GL for two Vertex Buffer Object (vbo)
  glGenBuffers (2, vbo);

  //Set 0 as the current array to be used by binding it
  glBindVertexArray (vao[0]);
  //Set 0 as the current buffer to be used by binding it
  glBindBuffer (GL_ARRAY_BUFFER, vbo[0]);

  room_colorcube();

  //Copy the points into the current buffer
  glBufferData (GL_ARRAY_BUFFER, sizeof (room_v_positions) + sizeof(room_tex_coords) + sizeof(room_v_normals), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(room_v_positions), room_v_positions );
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(room_v_positions), sizeof(room_tex_coords), room_tex_coords);
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(room_tex_coords)+sizeof(room_v_positions), sizeof(room_v_normals), room_v_normals );
  // set up vertex array
  //Position
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  //Textures
  glEnableVertexAttribArray( texCoord );
  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(room_v_positions)) );

  //Normal
  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(room_v_positions)+sizeof(room_tex_coords)) );
}

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
  torso->change_parameters(-2.0,0.0,0.0,  // translation
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
  r2d2_body->change_parameters(2.0,0.0,0.0,  // translation
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
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

  init_opening_box();

  init_humanoid();

  init_r2d2();

  init_room();
  
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));
  model_matrix = c_rotation_matrix; 

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    projection_matrix = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
    // projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,10.0);
  else
    projection_matrix = glm::ortho(-3.0, 3.0, -3.0, 3.0, 1.0, 10.0);

  view_matrix = projection_matrix*lookat_matrix;

  matrixStack.push_back(view_matrix);

  glUniformMatrix4fv(roomViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

 // Draw the sphere
  modelview_matrix = view_matrix*model_matrix;
  glUniformMatrix4fv(roomUModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  normal_matrix = glm::transpose (glm::inverse(glm::mat3(modelview_matrix)));
  glUniformMatrix3fv(roomNormalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  //  glBindTexture(GL_TEXTURE_2D, tex);
  glBindVertexArray (vao[0]);
  glDrawArrays(GL_TRIANGLES, 0, room_num_vertices);

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

