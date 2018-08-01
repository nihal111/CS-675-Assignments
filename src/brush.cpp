#include "brush.hpp"
#include "canvas.hpp"

namespace mydraw 
{
 void point_brush_t::stroke (const point_t &pt, canvas_t &canvas)
		{
			if (get_size()==1)
				canvas.set_pixel(pt);
		}

 void eraser_point_brush_t::stroke (const point_t &pt, canvas_t &canvas)
		{
			if (get_size()==1)
				canvas.erase_pixel(pt);
		}
}