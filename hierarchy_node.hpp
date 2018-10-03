#ifndef _HNODE_HPP_
#define _HNODE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "gl_framework.hpp"


namespace csX75	 { 

	// A simple class that represents a node in the hierarchy tree
	class HNode {
		//glm::vec4 * vertices;
		//glm::vec4 * colors;
		GLfloat tx,ty,tz,rx,ry,rz,btx,bty,btz;
		GLfloat min_rx, max_rx, min_ry, max_ry, min_rz, max_rz;

		std::size_t vertex_buffer_size;
		std::size_t color_buffer_size;

		GLuint num_vertices;
		GLuint vao,vbo;

		glm::mat4 rotation;
		glm::mat4 translation;
		glm::mat4 back_translation;
		
		std::vector<HNode*> children;
		HNode* parent;

		void update_matrices();

	  public:
		HNode (HNode*, GLuint, glm::vec4*,  glm::vec4*, std::size_t, std::size_t, 
			GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
		//HNode (HNode* , glm::vec4*,  glm::vec4*,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);

		void set_parent(HNode*);
		void add_child(HNode*);
		void render();
		void change_parameters(GLfloat,GLfloat,GLfloat,
			GLfloat _min_rx=-1, GLfloat _max_rx=-1, GLfloat _min_ry=-1, GLfloat _max_ry=-1, GLfloat _min_rz=-1, GLfloat _max_rz=-1);
		void render_tree();
		void inc_rx();
		void inc_ry();
		void inc_rz();
		void dec_rx();
		void dec_ry();
		void dec_rz();
	};

	glm::mat4* multiply_stack(std::vector <glm::mat4> );
};	

#endif