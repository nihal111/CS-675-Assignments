#include "hierarchy_node.hpp"
#include "texture.hpp"

#include <iostream>

extern GLuint vPosition,vColor,vNormal,uModelViewMatrix,useTexture,normalMatrix,texCoord;
extern std::vector<glm::mat4> matrixStack;

namespace csX75
{

	HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_colours, glm::vec4* a_normals, std::size_t v_size, std::size_t c_size, std::size_t n_size,
				GLfloat _min_rx=-1, GLfloat _max_rx=-1, GLfloat _min_ry=-1, GLfloat _max_ry=-1, GLfloat _min_rz=-1, GLfloat _max_rz=-1,
				GLenum _render_mode){

		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size = c_size;
		tex_coords_buffer_size = 0;
		normal_buffer_size = n_size;

		min_rx = _min_rx;
		max_rx = _max_rx;
		min_ry = _min_ry;
		max_ry = _max_ry;
		min_rz = _min_rz;
		max_rz = _max_rz;

		render_mode = _render_mode;


		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		
		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + normal_buffer_size + color_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, normal_buffer_size, a_normals );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + normal_buffer_size, color_buffer_size, a_colours );

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
		
		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size + normal_buffer_size));

		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=btx=bty=btz=0;

		update_matrices();
	}

	HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec2* a_tex_coords, glm::vec4* a_normals, std::size_t v_size, std::size_t c_size, std::size_t n_size,
				const char* filename, int w, int h,
				GLfloat _min_rx=-1, GLfloat _max_rx=-1, GLfloat _min_ry=-1, GLfloat _max_ry=-1, GLfloat _min_rz=-1, GLfloat _max_rz=-1,
				GLenum _render_mode){

		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size = 0;
		tex_coords_buffer_size = c_size;
		normal_buffer_size = n_size;

		min_rx = _min_rx;
		max_rx = _max_rx;
		min_ry = _min_ry;
		max_ry = _max_ry;
		min_rz = _min_rz;
		max_rz = _max_rz;

		render_mode = _render_mode;

		texture_file = filename;
		width = w;
		height = h;

		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		
		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + normal_buffer_size + tex_coords_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, normal_buffer_size, a_normals );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + normal_buffer_size, tex_coords_buffer_size, a_tex_coords );

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
		
		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		glEnableVertexAttribArray( texCoord );
		glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size + normal_buffer_size));

		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=btx=bty=btz=0;

		update_matrices();
	}

	void HNode::set_parent(HNode* a_parent) {
		parent = a_parent;
		parent->add_child(this);
	}

	void HNode::update_matrices(){

		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));

	}

	void HNode::add_child(HNode* a_child){
		children.push_back(a_child);

	}

	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
	}

	void HNode::render(){

		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);

		if (color_buffer_size == 0) { // Texture
			GLuint tex = LoadTexture(texture_file, width, height);
			glBindTexture(GL_TEXTURE_2D, tex);
			glUniform1i(useTexture, 1);
		} else { // Color
	  		glUniform1i(useTexture, 0);
		}

		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		glm::mat3 normal_matrix = glm::transpose (glm::inverse(glm::mat3(*ms_mult)));
  		glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));

		glBindVertexArray (vao);
		glDrawArrays(render_mode, 0, num_vertices);
		// for memory 
		delete ms_mult;

	}

	void HNode::render_tree(){
		
		matrixStack.push_back(translation);
		matrixStack.push_back(rotation);

		render();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();

	}

	void HNode::inc_rx(){
		if (max_rx == -1 || rx + 1 <= max_rx) {
			rx++;
			update_matrices();
		}
	}


	void HNode::inc_ry(){
		if (max_ry == -1 || ry + 1 <= max_ry) {
			ry++;
			update_matrices();
		}
	}

	void HNode::inc_rz(){
		if (max_rz == -1 || rz + 1 <= max_rz) {
			rz++;
			update_matrices();
		}
	}

	void HNode::dec_rx(){
		if (min_rx == -1 || rx - 1 >= min_rx) {
			rx--;
			update_matrices();
		}
	}

	void HNode::dec_ry(){
		if (min_ry == -1 || ry - 1 >= min_ry) {
			ry--;
			update_matrices();
		}
	}

	void HNode::dec_rz(){
		if (min_rz == -1 || rz - 1 >= min_rz) {
			rz--;
			update_matrices();
		}
	}


	// Getters

	float HNode::get_rx() {
		return rx;
	}

	float HNode::get_ry() {
		return ry;
	}

	float HNode::get_rz() {
		return rz;
	}

	float HNode::get_tx() {
		return tx;
	}

	float HNode::get_ty() {
		return ty;
	}

	float HNode::get_tz() {
		return tz;
	}

	// Setters

	void HNode::set_rx(float k) {
		rx = k;
		update_matrices();
	}

	void HNode::set_ry(float k) {
		ry = k;
		update_matrices();
	}

	void HNode::set_rz(float k) {
		rz = k;
		update_matrices();
	}

	void HNode::set_tx(float k) {
		tx = k;
		update_matrices();
	}

	void HNode::set_ty(float k) {
		ty = k;
		update_matrices();
	}

	void HNode::set_tz(float k) {
		tz = k;
		update_matrices();
	}


	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}