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
  std::cerr<< "\t-i drwfile\t\t.drw file to load\n";
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