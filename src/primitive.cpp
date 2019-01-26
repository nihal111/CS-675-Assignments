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

#include "primitive.hpp"
#include "canvas.hpp"

namespace mydraw {

	void bresenham_draw_line(const point_t &pt1, const point_t &pt2, canvas_t *canvas, brush_t *brush)
	{	int x1, x2, y1, y2;
		float slope, error;
		if (pt2.y > pt1.y)
		{
			x1 = pt1.x, y1 = pt1.y;
			x2 = pt2.x, y2 = pt2.y;
		} else {
			x1 = pt2.x, y1 = pt2.y;
			x2 = pt1.x, y2 = pt1.y;
		}

		if (x1 == x2)
		{
			for (int y = y1; y <= y2; y++)
			{
				brush->stroke((unsigned int) x1, (unsigned int) y, canvas);
			}
			return;
		}

		if (y1 == y2)
		{
			for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++)
			{
				brush->stroke((unsigned int) x, (unsigned int) y1, canvas);
			}
			return;
		}

		if (x1 < x2) {
			slope = 1.0*(y2 - y1)/(x2 - x1);

			if (slope < 1)
			{
				error = 0;

				int y = y1;

				for (int x = x1; x <= x2; x++)
				{
					brush->stroke((unsigned int) x, (unsigned int) y, canvas);
					error = error + slope;
					if (error >= 0.5)
					{
						y = y + 1;
						error = error - 1.0;
					}
				}
				return;
			}
			else
			{
				slope = 1.0*(x2 - x1)/(y2 - y1);
				error = 0;

				int x = x1;

				for (int y = y1; y <= y2; y++)
				{
					brush->stroke((unsigned int) x, (unsigned int) y, canvas);
					error = error + slope;
					if (error >= 0.5)
					{
						x = x + 1;
						error = error - 1.0;
					}
				}
				return;
			}
		} 
		else
		{
			slope = -1.0*(y2 - y1)/(x2 - x1);

			if (slope < 1)
			{
				error = 0;

				int y = y1;
				for (int x = x1; x >= x2; x--)
				{
					brush->stroke((unsigned int) x, (unsigned int) y, canvas);
					error = error + slope;
					if (error >= 0.5)
					{
						y = y + 1;
						error = error - 1.0;
					}
				}
				return;
			} 
			else
			{
				slope = -1.0*(x2 - x1)/(y2 - y1);
				error = 0;
				int x = x2;
				for (int y = y2; y >= y1; y--)
				{
					brush->stroke((unsigned int) x, (unsigned int) y, canvas);
					error = error + slope;
					if (error >= 0.5)
					{
						x = x + 1;
						error = error - 1.0;
					}
				}
			}
		}
	}

	void create_triangle(const point_t &pt1, const point_t &pt2, const point_t &pt3, canvas_t *canvas, brush_t *brush)
	{
		bresenham_draw_line(pt1, pt2, canvas, brush);
		bresenham_draw_line(pt2, pt3, canvas, brush);
		bresenham_draw_line(pt1, pt3, canvas, brush);
	}

	void draw_line(const unsigned int x, const unsigned int y, canvas_t *canvas, brush_t *brush)
	{	
		point_t pt(x, y);
		canvas->get_context()->buffer.push_back(pt);

		if (canvas->get_context()->buffer.size() == 2) {
			//draw line
			bresenham_draw_line(canvas->get_context()->buffer[0], 
				canvas->get_context()->buffer[1],
				canvas, 
				brush);

			//clear first pt from buffer
			canvas->get_context()->buffer.erase(canvas->get_context()->buffer.begin());
		}
	}

	void draw_triangle(const unsigned int x, const unsigned int y, canvas_t *canvas, brush_t *brush)
	{
		point_t pt(x, y);
		canvas->get_context()->buffer.push_back(pt);

		if (canvas->get_context()->buffer.size() == 3) {
			//draw line
			create_triangle(canvas->get_context()->buffer[0], 
				canvas->get_context()->buffer[1], 
				canvas->get_context()->buffer[2],
				canvas,
				brush);

			//clear first pt from buffer
			canvas->get_context()->buffer.erase(canvas->get_context()->buffer.begin());
		}
	}
}