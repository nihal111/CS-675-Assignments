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

#include <iostream>
#include <string>
#include <unistd.h>
#include <exception>

#include "canvas.hpp"
#include "gl_framework.hpp"

//-----------------------------------------------------------------------

/*!
  \fn void usage(void)
  \brief This function displays the usage message
*/
void usage(std::string progname) 
{
  std::cerr<< "usage: "<<progname<<" [-h] [-i drwfile]"<<std::endl<<std::endl;
  std::cerr<< "\t-h\t\t\tprint usage"<<std::endl;  
  std::cerr<< "\t-i tgafile\t\t.tga (RGBA) file to load\n";
  exit(0);
}

//-----------------------------------------------------------------------

int main(int argc, char** argv)
{
  std::string drwfilename;
  std::string progname = argv[0];

  bool drwf_flag = false;

  char c;
  while ((c = getopt(argc, argv, "h?i:")) != EOF)
    {
      switch (c) 
        {
          case 'h':
          case '?':
            usage(progname);
            break;
          case 'i':
            drwfilename =  optarg;   
            drwf_flag = true;
            break;
          default:
            usage(progname);
        }
    }

  mydraw::canvas_t* mycanvas; 
  if (drwf_flag)
    mycanvas = new mydraw::canvas_t(drwfilename);
  else
    mycanvas = new mydraw::canvas_t;

  int returncode = csX75::render_gl(argc, argv, mycanvas);

  return returncode;
}