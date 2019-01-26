#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_
GLuint LoadTexture( const char * filename, int width, int height );
void FreeTexture( GLuint texture );
void draw_textured_object(glm::mat4 view_matrix, GLuint* texcub_vao, 
                          const char* filename, 
                          int width, int height,
                          int texcub_num_vertices);
#endif 
