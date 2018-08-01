#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>


namespace csX75
{
  GLuint load_shader(GLenum eShaderType, const std::string &strFilename);
  GLuint create_shader(GLenum eShaderType, const std::string &strShaderFile);
  GLuint create_program(const std::vector<GLuint> &shaderList);
};
