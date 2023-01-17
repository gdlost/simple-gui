#ifndef WIDGET_HH
#define WIDGET_HH

#include "Helpers.hh"

// Todo widget cubre un area, que es un rectangulo. Esto no impide
// que un widget pueda poseer rectangulos dentro de si mismo. Tal es el caso
// del Slider.
class Widget : public Rect {
	public:
		virtual void render(SDL_Renderer *rend) = 0;
		virtual int notify_mouse(int cx, int cy, int rcx, int rcy, int button_left) = 0;
};

#endif // WIGET_HH