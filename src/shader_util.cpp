/*
    This file is part of the mydraw.

    mydraw is a simple, interactive drawing program written using OpenGL. 
    
    This code base is meant to serve as a starter code for an assignment in a 
    Computer Graphics course.

    Copyright (c) 2018 by Parag Chaudhuri

    mydraw is free software; you can redistribute it and/or modify it under the 
    terms of the MIT License.

    Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include <GL/glew.h>
#include "shader_util.hpp"

namespace csX75
{
  GLuint load_shader(GLenum eShaderType, const std::string &strFilename)
  {
    std::ifstream shaderFile(strFilename.c_str());
    if (!shaderFile.is_open())
      throw std::runtime_error("Cannot find file: " + strFilename);
   
    std::stringstream shaderData;
    shaderData << shaderFile.rdbuf();
    shaderFile.close();
    
    try
      {
	     return create_shader(eShaderType, shaderData.str());
      }
    catch(std::exception &e)
      {
	     std::cerr<<e.what()<<std::endl;
	     throw;
      }
  }
  
  GLuint create_shader(GLenum eShaderType, const std::string &strShaderFile)
  {
    GLuint shader = glCreateShader(eShaderType);
    const char *strFileData = strShaderFile.c_str();
    glShaderSource(shader, 1, &strFileData, NULL);
    
    glCompileShader(shader);
    
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
      {
      	GLint infoLogLength;
      	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
      	
      	GLchar *strInfoLog = new GLchar[infoLogLength + 1];
      	glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
      	
      	const char *strShaderType = NULL;
      	switch(eShaderType)
      	  {
      	  case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
      	  case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
      	  case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
      	  }
      	
      	std::cerr<<"Compile failure in "<<strShaderType<<" shader:"<<std::endl<<strInfoLog<<std::endl;
      	delete[] strInfoLog;
      }
    
    return shader;
  }
  
  GLuint create_program(const std::vector<GLuint> &shaderList)
  {
    GLuint program = glCreateProgram();
    
    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
      glAttachShader(program, shaderList[iLoop]);
    
    glLinkProgram(program);
    
    GLint status;
    glGetProgramiv (program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
      {
      	GLint infoLogLength;
      	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
      	
      	GLchar *strInfoLog = new GLchar[infoLogLength + 1];
      	glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
      	std::cerr<<"GLSL Linker failure: "<<strInfoLog<<std::endl;
      	delete[] strInfoLog;
      }
    
    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
      glDetachShader(program, shaderList[iLoop]);
    
    return program;
  }

};
