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

#pragma once

#include <string>

#include "brush.hpp"
#include "color.hpp"
#include "fill.hpp"
#include"primitive.hpp"

namespace mydraw
{
	/**
	 * \brief Data that makes up mydraw's current context
	 */
	class draw_context_t
	{
	public:
		color_t brush_color;
		color_t bg_color;
	
		brush_t *current_brush;
		brush_t *current_eraser;

		primitive_mode_t current_pmode;
		fill_t	*current_fill;
	};

	/**
	 * \brief The mydraw canvas class
	 *
	 * The canvas is stored as a float buffer array that is drawn to the screen as an OpenGL texture. 
	 * All drawing operations in mydraw are implemented as rasterization modules that act on the float buffer
	 * and do not involve any OpenGL.
	 * The buffer is used to texture a screen aligned quad made up of two triangles.
	 */
	class canvas_t
	{
	private:
		//! Flag to signal if a file has been loaded
		bool drw_file_present;
		//! Filename to load/save the canvas
		std::string drwfilename;

		//! The drawing context for the canvas
		draw_context_t* context;

		unsigned int width;
		unsigned int height;

		//! Pixel data for the canvas is stored in this array of size 4*width*height
		float* store;

		//! Canvas texture
		unsigned int canvas_texture;
		//! Canvas VAO
		unsigned int canvas_vao;
		//! Canvas Shader Program
		unsigned int canvas_sp;

		void init_context(void);
		void make_store(void);
		void set_store(unsigned char *ustore, int w, int h, int c);

	public:
		canvas_t();
		canvas_t(int _w, int _h); 
		canvas_t(std::string _drwfile);

		//! Loads the canvas with the contents of the .tga file given on the command line. 
		//! Make sure the tga has 4 channels for things to work correctly.
		int load(void);
		
		//! Saves the canvas to default.tga
		int save(void);

		color_t get_pixel(const unsigned int x, const unsigned int y) const;
		void set_pixel(const point_t &pt);
		void set_pixel(const unsigned int x, const unsigned int y);
		void erase_pixel(const point_t &pt);

	        draw_context_t* get_context(void) { return context; }

		unsigned int get_width(void) const { return width; }
		unsigned int get_height(void) const { return height; }

		unsigned int get_canvas_texture(void) {return canvas_texture;}
		void set_canvas_texture(unsigned int _tex) { canvas_texture = _tex;}

		unsigned int get_canvas_vao(void) {return canvas_vao;}
		void set_canvas_vao(unsigned int _vao) { canvas_vao = _vao;}

		unsigned int get_canvas_sp(void) {return canvas_sp;}
		void set_canvas_sp(unsigned int _sp) { canvas_sp = _sp;}

		float *get_store(void) {return store;}
	};
}
