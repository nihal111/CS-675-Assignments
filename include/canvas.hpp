#pragma once

#include <string>

#include "brush.hpp"
#include "color.hpp"
#include "fill.hpp"
#include"primitive.hpp"

namespace mydraw
{
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


	class canvas_t
	{
	private:
		bool drw_file_present;
		std::string drwfilename;

		draw_context_t* context;

		int width;
		int height;

		float* store;
		unsigned int canvas_texture;
		unsigned int canvas_vao;
		unsigned int canvas_sp;

		void init_context(void);
		void make_store(void);

	public:
		canvas_t();
		canvas_t(int _w, int _h); 
		canvas_t(std::string _drwfile);

		int load(void);
		int save(void);

		color_t get_pixel(const unsigned int x, const unsigned int y) const;
		void set_pixel(const point_t &pt);
		void set_pixel(const unsigned int x, const unsigned int y);
		void erase_pixel(const point_t &pt);

		int get_width(void) const { return width; }
		int get_height(void) const { return height; }

		unsigned int get_canvas_texture(void) {return canvas_texture;}
		void set_canvas_texture(unsigned int _tex) { canvas_texture = _tex;}

		unsigned int get_canvas_vao(void) {return canvas_vao;}
		void set_canvas_vao(unsigned int _vao) { canvas_vao = _vao;}

		unsigned int get_canvas_sp(void) {return canvas_sp;}
		void set_canvas_sp(unsigned int _sp) { canvas_sp = _sp;}

		float *get_store(void) {return store;}
	};
}