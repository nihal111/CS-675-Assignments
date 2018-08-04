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

#include "canvas.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_TGA
#include "stb_image_read.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.hpp"


#include <iostream>

namespace mydraw
{
	void canvas_t::init_context(void)
	{
		context = new draw_context_t;
		
		context->bg_color = color_t(0.0f,0.0f,0.0f,1.0f);
		context->brush_color = color_t(1.0f,1.0f,1.0f,1.0f);

		context->current_brush = new point_brush_t;
		context->current_eraser = new eraser_point_brush_t;

		context->current_pmode = primitive_mode_t::point;
		context->current_fill = new floodfill_t;
	}

	void canvas_t::make_store(void)
	{
		store = new float[4*width*height];
		for(unsigned int x=0; x<width; x++)
			for(unsigned int y=0;y<height; y++)
			{
				unsigned int index=0;
				index=(4*width*y) + (4*x);
				store[index]=context->bg_color.r;
				store[index+1]=context->bg_color.g;
				store[index+2]=context->bg_color.b;
				store[index+3]=context->bg_color.a;
			}
	}

	void canvas_t::set_store(unsigned char *ustore, int w, int h, int c)
	{
		if (store != NULL) delete[] store;
		width = w;
		height = h;
		store = new float[c*width*height];

		for(unsigned int x=0; x<width; x++)
			for(unsigned int y=0;y<height; y++)
			{
				unsigned int index=0, uindex=0;
				index=(4*width*y) + (4*x);
				uindex=(4*width*(height-1-y)) + (4*x);
				store[index]=float(ustore[uindex])/255.0f;
				store[index+1]=float(ustore[uindex+1])/255.0f;
				store[index+2]=float(ustore[uindex+2])/255.0f;
				store[index+3]=float(ustore[uindex+3])/255.0f;
			}
	}

	canvas_t::canvas_t()
	{
		drw_file_present=false;
		width=1024;
		height=768;
		init_context();
		store = NULL;
		make_store();
	}

	canvas_t::canvas_t(int _w, int _h):width(_w), height(_h)
	{
		drw_file_present=false;
		init_context();
		store = NULL;
		make_store();
	}

	canvas_t::canvas_t(std::string _drwfilename):drwfilename(_drwfilename)
	{
		drw_file_present=true;
		init_context();
		store = NULL;
		load();
	}

	color_t canvas_t::get_pixel(const unsigned int x, const unsigned int y) const
	{
		unsigned int index=0;
		index=(4*width*y) + (4*x);

		float r = store[index];
		float g = store[index+1];
		float b = store[index+2];
		float a = store[index+3];
		return color_t(r,g,b,a);
	}

	void canvas_t::set_pixel(const point_t &pt)
	{
		unsigned int x=pt.x;
		unsigned int y=pt.y;
		unsigned int index=0;
		index=(4*width*y) + (4*x);

		store[index]=context->brush_color.r;
		store[index+1]=context->brush_color.g;
		store[index+2]=context->brush_color.b;
		store[index+3]=context->brush_color.a;
	}

	void canvas_t::set_pixel(const unsigned int x, const unsigned int y)
	{
		unsigned int index=0;
		index=(4*width*y) + (4*x);


		store[index]=context->brush_color.r;
		store[index+1]=context->brush_color.g;
		store[index+2]=context->brush_color.b;
		store[index+3]=context->brush_color.a;
	}
	
	void canvas_t::erase_pixel(const point_t &pt)
	{
		unsigned int x=pt.x;
		unsigned int y=pt.y;

		unsigned int index=0;
		index=(4*width*y) + (4*x);


		store[index]=context->bg_color.r;
		store[index+1]=context->bg_color.g;
		store[index+2]=context->bg_color.b;
		store[index+3]=context->bg_color.a;
	}

	int canvas_t::load(void)
	{
		int num_bytes_read=0;
		int w, h, c;

		if (drw_file_present)
		{
			unsigned char *ustore = stbi_load( drwfilename.c_str(), &w, &h, &c, 0 );
			if (ustore == NULL)
			{
				std::cerr<<"ERROR: Could not load file - "<<drwfilename<<std::endl;
				std::cerr<<"Proceeding with empty canvas."<<std::endl;
				drw_file_present=false;
				width=1024;
				height=768;
				make_store();
			}
			else
			{
				num_bytes_read = w*h*c;
				set_store(ustore,w,h,c);
				delete[] ustore;
			}
		}

		return num_bytes_read;
	}

	int canvas_t::save(void)
	{
		int num_bytes_written = 0;
		if (!drw_file_present)
		{
			drwfilename="default.tga"; drw_file_present=true;
		}

		
		unsigned char* ustore = new unsigned char[width*height*4];
		for(unsigned int x=0; x<width; x++)
			for(unsigned int y=0;y<height; y++)
			{
				unsigned int index=0, uindex=0;
				index=(4*width*y) + (4*x);
				uindex=(4*width*(height-1-y)) + (4*x);
				ustore[uindex] = (unsigned char)(255.0f*store[index]);
				ustore[uindex+1]=(unsigned char)(255.0f*store[index+1]);
				ustore[uindex+2]=(unsigned char)(255.0f*store[index+2]);
				ustore[uindex+3]=(unsigned char)(255.0f*store[index+3]);
			}
	
		num_bytes_written = stbi_write_tga( drwfilename.c_str(), width, height, 4, (void*)ustore );

		if (ustore != NULL)
		  delete[] ustore;
		
		return num_bytes_written;
	}
}
