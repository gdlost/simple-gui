#ifndef SLIDER_HH
#define SLIDER_HH

#include "Widget.hh"

#define sSLIDER_IDLE 0
#define sSLIDER_HOVER 1
#define sSLIDER_ACTIVE 2

class Slider : public Widget {
    public:
    Rect knob;
    Rect bar;
    int gapx;
    int gapy;

    float min, max, range;
    float current = 0;
    float step = 0.25;

    int state = sSLIDER_IDLE;

    Slider();
    Slider(int x, int y);
    void render(SDL_Renderer *rend);
    int notify_mouse(int cx, int cy, int rcx, int rcy, int button_left);
    void calculate_knob();
    virtual void on_click() = 0;
};

#endif // SLIDER_HH
