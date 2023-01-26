#ifndef CHECKBOX_HH
#define CHECKBOX_HH

#include "Window.hh"
#include "Widget.hh"

#define sBUTTON_IDLE 0
#define sBUTTON_HOVER 1
#define sBUTTON_ACTIVE 2

class Checkbox : public Widget {
	public:
	bool checked = false;
	int state = sBUTTON_IDLE;

	Checkbox(int x, int y);
	Checkbox(bool checked);

	void render(SDL_Renderer *rend);
	int notify_mouse(int cx, int cy, int rcx, int rcy, int button_left);
};

#endif // CHECKBOX_HH
