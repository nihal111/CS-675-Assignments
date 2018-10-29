/*
  A program which opens a window and draws three arms in a hierarchy

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Written by - 
               Harshavardhan Kode
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"

/*// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;*/
// Camera position and rotation Parameters
glm::vec4 c_pos;
GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 5.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=true;
//Shader program attribs
GLuint vPosition, vColor, texCoord;
GLuint uModelViewMatrix, useTexture;

glm::mat4 view_matrix;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;

csX75::HNode* root_node;
csX75::HNode* curr_node;

// ---- Opening Box
csX75::HNode* lid;
csX75::HNode* base_box;

// ---- Humanoid
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

// ---- R2D2
csX75::HNode* r2d2_body;
csX75::HNode* r2d2_head;
csX75::HNode* r2d2_left_arm;
csX75::HNode* r2d2_right_arm;
csX75::HNode* r2d2_left_hand;
csX75::HNode* r2d2_right_hand;


// ---- Mouse Points
GLuint mouse_clicks_vbo[50], mouse_clicks_vao[50];
int mouse_count = 0;

// Interpolated points of mouse curve
int num_interpolated_points = 101;
GLuint mouse_curve_vbo, mouse_curve_vao;

// ----- Control points are in place.
bool animation_started = false;

// ---- Colors
glm::vec4 color = glm::vec4(0.6, 0.6, 0.6, 1.0);
glm::vec4 grey = glm::vec4(0.3, 0.3, 0.3, 1.0);
glm::vec4 white = glm::vec4(0.9, 0.9, 0.9, 1.0);
glm::vec4 red = glm::vec4(1.0, 0.2, 0.2, 1.0);
glm::vec4 yellow = glm::vec4(0.8, 0.8, 0.0, 1.0);
glm::vec4 orange = glm::vec4(0.9, 0.5, 0.1, 1.0);
glm::vec4 green = glm::vec4(0.2, 0.7, 0.2, 1.0);
glm::vec4 blue = glm::vec4(0.2, 0.2, 0.7, 1.0);
glm::vec4 black = glm::vec4(0.2, 0.2, 0.2, 1.0);
glm::vec4 light_blue = glm::vec4(0.0, 0.749, 1.0, 1.0);
glm::vec4 dark_blue = glm::vec4(0.11, 0.564, 1.0, 1.0);
glm::vec4 skin = glm::vec4(0.9, 0.7, 0.3, 1.0);

//-------------------------------------------------------------------------

#endif
