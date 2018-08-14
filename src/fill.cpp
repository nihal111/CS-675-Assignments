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

#include "fill.hpp"
#include "canvas.hpp"
#include <queue>
#include <iostream>

namespace mydraw
{
	void floodfill_t::fill_canvas (unsigned int xpos, unsigned int ypos, canvas_t *canvas)
	{
		std::queue<point_t> buffer;

		unsigned int visited[canvas->get_width()][canvas->get_height()];

		for (int i = 0; (unsigned int) i < canvas->get_width(); i++)
		{
			for (int j = 0; (unsigned int) j < canvas->get_height(); j++)
			{
				visited[i][j] = 0;
			}
		}

		// Mark the current pixel as visited.
		visited[xpos][ypos] = 1;
		point_t current_pixel(xpos, ypos);
		buffer.push(current_pixel);

		// Get the color of the current pixel.
		color_t current_color = canvas->get_pixel(xpos, ypos);


		while(!buffer.empty())
		{
			point_t pt = buffer.front();
			unsigned int cx = (unsigned int) pt.x;
			unsigned int cy = (unsigned int) pt.y;

			buffer.pop();
			canvas->set_pixel(cx, cy);

			if (visited[cx - 1][cy] != 1 && (cx - 1) > 0)
			{
				if (canvas->get_pixel(cx - 1, cy) == current_color)
				{
					visited[cx - 1][cy] = 1;
					point_t temp(cx - 1, cy);
					buffer.push(temp);
				}
			}

			if (visited[cx][cy - 1] != 1 && (cy - 1) > 0)
			{
				if (canvas->get_pixel(cx, cy - 1) == current_color)
				{
					visited[cx - 1][cy] = 1;
					point_t temp(cx, cy - 1);
					buffer.push(temp);
				}
			}

			if (visited[cx + 1][cy] != 1 && (cx + 1) < canvas->get_width())
			{
				if (canvas->get_pixel(cx + 1, cy) == current_color)
				{
					visited[cx + 1][cy] = 1;
					point_t temp(cx + 1, cy);
					buffer.push(temp);
				}
			}

			if (visited[cx][cy + 1] != 1 && (cy + 1) < canvas->get_height())
			{
				if (canvas->get_pixel(cx, cy + 1) == current_color)
				{
					visited[cx][cy + 1] = 1;
					point_t temp(cx, cy + 1);
					buffer.push(temp);
				}
			}
		}

	}
}