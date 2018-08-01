#version 330 core

layout (location = 0) in vec2 i_pos;
layout (location = 1) in vec2 i_tex_coords;

out vec2 tex_coords;

void main()
{
    tex_coords = i_tex_coords;
    gl_Position = vec4(i_pos.x, i_pos.y, 0.0, 1.0); 
}  
