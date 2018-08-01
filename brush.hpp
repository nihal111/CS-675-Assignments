#pragma once

#include "primitive.hpp"

namespace mydraw
{
	class canvas_t;

	enum class brush_type_t {point, eraser_point};

	class brush_t
	{
	private:
		int size;
		brush_type_t type;

	public:
		virtual ~brush_t() { }
		virtual void stroke (const point_t &pt, canvas_t &canvas) = 0;

		void set_size(int _size) {size = _size;}
		void set_type(brush_type_t _type) { type = _type;}
		const int get_size(void) const { return size; }
		const brush_type_t get_type(void) const {return type;}
	};

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

	};

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
	};


}