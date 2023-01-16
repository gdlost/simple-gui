#ifndef WIDGET_HH
#define WIDGET_HH

#include "Helpers.hh"

class Widget {
	public:
		Rect outline;

        //virtual void step();
		virtual void render(SDL_Renderer *rend) = 0;
		virtual int notify_mouse(int cx, int cy, int button_left) = 0;
		bool inside_my_bounds(int x, int y);

};

#endif // WIGET_HH