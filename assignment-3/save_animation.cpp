#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_TGA
#include "stb_image_read.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.hpp"

int width = 800;
int height = 800;

unsigned char* reverse(unsigned char* ustore, int start, int end) 
{
	unsigned char* r_ustore = new unsigned char[width*height*4];
	int count = 0;
	for (int i=end-1; i >= 0; i--) // Count backwards in order to flip
    {
        for( int j = 0; j < end; j++)
        {
        	r_ustore[count] = ustore[(i*end+j)*4];
        	count++;
        	r_ustore[count] = ustore[(i*end+j)*4 + 1];
        	count++;
        	r_ustore[count] = ustore[(i*end+j)*4 + 2];
        	count++;
        	r_ustore[count] = ustore[(i*end+j)*4 + 3];
        	count++;
        }
    }
    return r_ustore;
}  

int save(std::string drwfilename)
{
	int num_bytes_written = 0;
	
	unsigned char* ustore = new unsigned char[width*height*4];

	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, ustore);

	ustore = reverse(ustore, 0, width);

	num_bytes_written = stbi_write_tga( drwfilename.c_str(), width, height, 4, (void*)ustore );

	if (ustore != NULL)
	  delete[] ustore;
	
	return num_bytes_written;
}