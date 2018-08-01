#include "canvas.hpp"

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

	canvas_t::canvas_t()
	{
		drw_file_present=false;
		width=1024;
		height=768;
		init_context();
		make_store();
	}

	canvas_t::canvas_t(int _w, int _h):width(_w), height(_h)
	{
		drw_file_present=false;
		init_context();
		make_store();
	}

	canvas_t::canvas_t(std::string _drwfilename):drwfilename(_drwfilename)
	{
		drw_file_present=true;
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
		return num_bytes_read;
	}

	int canvas_t::save(void)
	{
		int num_bytes_written=0;
		return num_bytes_written;
	}
}