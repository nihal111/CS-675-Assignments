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
#include <vector>
#include "primitive.hpp"

/**
 * \brief Everything in mydraw is a part of this namespace.
 */
namespace mydraw
{
	//! Forward Declaration to prevent a circular dependency
	class canvas_t;

	//! Define more brush enumerations here
	enum class brush_type_t {point, eraser_point, smooth};

	/**
	 * \brief An abstract base brush class
	 */
	class brush_t
	{
	private:
		//! Brush size
		int size;

		//! Brush type
		brush_type_t type;

	public:
		virtual ~brush_t() { }
		virtual void stroke (const point_t &pt, canvas_t &canvas) = 0;
	        virtual void stroke (unsigned int xpos, unsigned int ypos, canvas_t *canvas) = 0;

		void set_size(int _size) {size = _size;}
		void set_type(brush_type_t _type) { type = _type;}
		const int get_size(void) const { return size; }
		const brush_type_t get_type(void) const {return type;}
		std::vector<point_t> buffer;
	};

	/**
	 * \brief A point brush - each brush stroke is made up of points of the current size in the current draw color.
	 * 
	 * A point brush of size 1 is implemented by default. Extend to implement other point sizes.
	 *
	 */
	class point_brush_t: public brush_t
	{
	public:
		point_brush_t()
		{
			set_size(1);
			set_type(brush_type_t::point);
		}

		~point_brush_t() { }

		void stroke (const point_t &pt, canvas_t &canvas);
	        void stroke (unsigned int xpos, unsigned int ypos, canvas_t *canvas); 
	};

	/**
	 * \brief A point eraser - each brush stroke is made up of points of the current size in the current background color.
	 * 
	 * An eraser point brush of size 1 is implemented by default. Extend to implement other point sizes.
	 *
	 */
	class eraser_point_brush_t: public brush_t
	{
	public:
		eraser_point_brush_t()
		{
			set_size(1);
			set_type(brush_type_t::eraser_point);
		}

		~eraser_point_brush_t() { }

		void stroke (const point_t &pt, canvas_t &canvas);
	        void stroke (unsigned int xpos, unsigned int ypos, canvas_t *canvas);
	};

	/**
	 * \brief A smooth brush
	 */
	class smooth_brush_t: public brush_t
	{
	public:
		smooth_brush_t()
		{
			set_size(1);
			set_type(brush_type_t::smooth);
		}

		~smooth_brush_t() { }

		void stroke (const point_t &pt, canvas_t &canvas);
	        void stroke (unsigned int xpos, unsigned int ypos, canvas_t *canvas);
	};


}
