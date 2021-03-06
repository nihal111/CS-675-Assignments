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

#include "brush.hpp"
#include "canvas.hpp"
#include <vector>
#include <iostream>
#include <cmath>

namespace mydraw 
{
	std::vector<point_t*> get_square_points(unsigned int xpos, unsigned int ypos, int size)
	{
		std::vector<point_t*> points;
		if (size % 2 == 0)
		{
			for (int i = xpos - size/2; i < int(xpos + size/2); i++)
			{
				for (int j = ypos - size/2; j < int(ypos + size/2); j++)
				{
					if (i >= 0 && j >= 0) {
						point_t *pt = new point_t(i, j);
						points.push_back(pt);
					}
				}
			}
		} 
		else
		{
			for (int i = xpos -(size-1)/2; i <= int(xpos + (size-1)/2); i++)
			{
				for (int j = ypos -(size-1)/2; j <= int(ypos + (size-1)/2); j++)
				{
					if (i >= 0 && j >= 0) 
					{
						point_t *pt = new point_t(i, j);
						points.push_back(pt);
					}
				}
			}
		}
		return points;
	}

	std::vector<point_t*> get_circle_points(unsigned int xpos, unsigned int ypos, int size) {
		std::vector<point_t*> points;
		int radius_squared = size*size;
		for (int i = xpos - size -1; i <= int(xpos + size + 1); i++)
		{
			for (int j = ypos - size -1; j <= int(ypos + size + 1); j++)
			{
				if (i >= 0 && j >= 0 && int((xpos - i)*(xpos - i) + (ypos - j)*(ypos - j)) <= radius_squared)
				{
					point_t *pt = new point_t(i, j);
					points.push_back(pt);
				}
			}
		}
		return points;
	}

	void stroke_fill(std::vector<point_t*> points, canvas_t &canvas)
	{
		for(std::size_t i = 0; i < points.size(); i++)
		{
			canvas.set_pixel(*points[i]);
		}
	}

	void stroke_erase(std::vector<point_t*> points, canvas_t &canvas)
	{
		for(std::size_t i = 0; i < points.size(); i++)
		{
			canvas.erase_pixel(*points[i]);
		}
	}

	void point_brush_t::stroke (const point_t &pt, canvas_t &canvas)
	{
		if (get_size()==1)
			canvas.set_pixel(pt);
		else
		{
			std::vector<point_t*> points = get_circle_points(pt.x, pt.y, get_size());
			stroke_fill(points, canvas);
		}
	}

	void point_brush_t::stroke (unsigned int xpos, unsigned int ypos, canvas_t *canvas)
	 {
	 	if (get_size()==1) 
	 		canvas->set_pixel(xpos,ypos);
		else
		{
			std::vector<point_t*> points = get_circle_points(xpos, ypos, get_size());
			stroke_fill(points, *canvas);
		}
	 }
	  
	void eraser_point_brush_t::stroke (const point_t &pt, canvas_t &canvas)
	{
		if (get_size()==1)
			canvas.erase_pixel(pt);
		else
		{
			std::vector<point_t*> points = get_circle_points(pt.x, pt.y, get_size());
			stroke_erase(points, canvas);
		}
	}

	void eraser_point_brush_t::stroke (unsigned int xpos, unsigned int ypos, canvas_t *canvas)
	{
		if (get_size()==1)
			canvas->erase_pixel(xpos,ypos);
		else
		{
			std::vector<point_t*> points = get_circle_points(xpos, ypos, get_size());
			stroke_erase(points, *canvas);
		}
	}

	void smooth_brush_t::stroke (const point_t &pt, canvas_t &canvas)
	{
		if (get_size()==1)
			canvas.set_pixel(pt);
		else
		{
			std::vector<point_t*> points = get_circle_points(pt.x, pt.y, get_size());
			stroke_fill(points, canvas);
		}
	}

	float dist_points(const point_t &pt1, const point_t &pt2)
	{
		float length = sqrt((pt1.x - pt2.x)*(pt1.x - pt2.x) + (pt1.y - pt2.y)*(pt1.y - pt2.y));
		return length;
	}

	std::vector<point_t*> get_bezzier_curve_points(const point_t &pt1, const point_t &pt2, const point_t &pt3,canvas_t &canvas)
	{
		std::vector<point_t*> points;
		for (float t = 0; t <= 1; t = t + 0.001)
		{
			float xpos = (1-t)*(1-t)*pt1.x + 2*(1-t)*t*pt3.x + t*t*pt2.x;
			float ypos = (1-t)*(1-t)*pt1.y + 2*(1-t)*t*pt3.y + t*t*pt2.y;

			if (xpos >= 0 && ypos >= 0)
			{
				if ((unsigned int) xpos <= canvas.get_width() && (unsigned int) ypos <= canvas.get_height())
				{
					point_t *pt = new point_t(int(xpos), int(ypos));
					points.push_back(pt);
				}
			}
		}
		return points;
	}

	point_t calc_gradient_vector(const point_t &pt1, const point_t &pt2)
	{
		float length = dist_points(pt1, pt2);
		float xgrad = (pt2.x - pt1.x)/length;
		float ygrad = (pt2.y - pt1.y)/length;
		point_t grad(xgrad, ygrad);
		return grad;
	}

	void smooth_brush_t::stroke (unsigned int xpos, unsigned int ypos, canvas_t *canvas)
	{
		// A Spline interpolation is fitted between the points.
		point_t pt(xpos, ypos);
		buffer.push_back(pt);

		if (buffer.size() > 1)
		{
			point_t prev_point = buffer[buffer.size() - 2];
			point_t next_point = buffer[buffer.size() - 1];

			if (buffer.size() == 2)
			{
				point_t gradient_vector = calc_gradient_vector(prev_point, next_point);
				grad_buffer.push_back(gradient_vector);
				grad_buffer.push_back(gradient_vector);
			}

			point_t grad = grad_buffer[grad_buffer.size() - 1];

			// Calculate a intermediate point.
			float length = dist_points(prev_point, next_point)/3;
			float ix = prev_point.x + length*grad.x;
			float iy = prev_point.y + length*grad.y;
			point_t ipoint(ix, iy);

			std::vector<point_t*> points = get_bezzier_curve_points(prev_point, next_point, ipoint, *canvas);
			unsigned int total_points = points.size();

			// Take the size into account.
			if (get_size()!=1)
			{
				for(std::size_t i = 0; i < total_points; i++)
				{
					point_t pt = *points[i];
					std::vector<point_t*> circ_points = get_circle_points(pt.x, pt.y, get_size());
					points.insert(points.end(), circ_points.begin(), circ_points.end());
				}
			}

			// Draw the curved point.
			stroke_fill(points, *canvas);

			// Calculate the next gradient vector.
			point_t next_grad = calc_gradient_vector(ipoint, next_point);
			grad_buffer.push_back(next_grad);

		}
	}
}
