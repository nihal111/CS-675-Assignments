#include <iostream>
#include "glm/ext.hpp"

extern GLuint vPosition,vColor,uModelViewMatrix, useTexture;
extern glm::mat4 view_matrix;
extern GLuint mouse_clicks_vbo[50], mouse_clicks_vao[50];
extern int mouse_count;

void sphere_points(double radius, double xpos, double ypos, double zpos, int Lats, int Longs, glm::vec4 color, float phi_step, float theta_step, glm::vec4* v_positions, glm::vec4* v_colors)
{
    float theta, phi;
    int tri_idx = 0;
    double PI=3.14159265;

    // float phi_step=float(Lats)/100;
    // float theta_step=float(Longs)/100;

    float l;

    for (theta = 0.0; theta <= PI - theta_step / 2; theta+=theta_step)  
    {
        for(phi = 0.0; phi <= 2.0*PI + phi_step / 2; phi+=phi_step)
        {
            float x = xpos + radius * sin(theta) * cos(phi);
            float y = ypos + radius * sin(theta) * sin(phi);
            float z = zpos + radius * cos(theta);
            glm::vec4 pt(x, y, z, 1.0);

            v_colors[tri_idx] = color; v_positions[tri_idx] = pt; 
            tri_idx++;

            if(theta+theta_step>PI)
                l=PI;
            else
            l=theta+theta_step;
            x = xpos + radius * sin(l) * cos(phi);
            y = ypos + radius * sin(l) * sin(phi);
            z = zpos + radius * cos(l);
            pt =glm::vec4(x, y, z, 1.0);
            v_colors[tri_idx] = color; v_positions[tri_idx] = pt; 
            tri_idx++;
        }
    }
}

void draw_sphere(double xpos, double ypos, double zpos)
{
    GLuint vao,vbo;
    double r = 0.2;  
    int tesselation=50;
    int Lats = tesselation;
    int Longs = tesselation;
    float phi_step=(180/(float(Lats)*10))/2;
    float theta_step=(180/(float(Longs)*10))/2;

    int num_vertices = 3600;

    glGenVertexArrays (1, &vao);
    //Ask GL for aVertex Buffer Object (vbo)
    glGenBuffers (1, &vbo);

    //bind them
    glBindVertexArray (vao);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);

    glm::vec4 v_positions[num_vertices];
    glm::vec4 v_colors[num_vertices];

    sphere_points(r, xpos, ypos, zpos, Lats, Longs, glm::vec4(0.2, 0.2, 0.7, 1.0), phi_step, theta_step, v_positions, v_colors);

    std::size_t vertex_buffer_size = sizeof(v_positions);
    std::size_t color_buffer_size = sizeof(v_colors);

    glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size, NULL, GL_STATIC_DRAW);
    glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, v_positions );
    glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, v_colors );

    glUniform1i(useTexture, 0);
    //setup the vertex array as per the shader
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
    glBindVertexArray (vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, num_vertices);
}

void add_sphere_points(double xpos, double ypos, double zpos)
{

    GLuint vao,vbo;
    double r = 0.2;  
    int tesselation=50;
    int Lats = tesselation;
    int Longs = tesselation;
    float phi_step=(180/(float(Lats)*10))/2;
    float theta_step=(180/(float(Longs)*10))/2;

    int num_vertices = 3600;

    glGenVertexArrays (1, &vao);
    //Ask GL for aVertex Buffer Object (vbo)
    glGenBuffers (1, &vbo);

    //bind them
    glBindVertexArray (vao);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);

    glm::vec4 v_positions[num_vertices];
    glm::vec4 v_colors[num_vertices];

    sphere_points(r, xpos, ypos, zpos, Lats, Longs, glm::vec4(0.2, 0.2, 0.7, 1.0), phi_step, theta_step, v_positions, v_colors);

    std::size_t vertex_buffer_size = sizeof(v_positions);
    std::size_t color_buffer_size = sizeof(v_colors);

    glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size, NULL, GL_STATIC_DRAW);
    glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, v_positions );
    glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, v_colors );

    glUniform1i(useTexture, 0);
    //setup the vertex array as per the shader
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size)); 

    mouse_clicks_vao[mouse_count] = vao;
    mouse_clicks_vao[mouse_count] = vbo;
    mouse_count = mouse_count + 1;
}