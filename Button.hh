#ifndef BUTTON_HH
#define BUTTON_HH

#include "Widget.hh"

#define sBUTTON_IDLE 0
#define sBUTTON_HOVER 1
#define sBUTTON_ACTIVE 2

class Button : public Widget {
    public:
    bool active = false;
    bool hover = false;

    int state = sBUTTON_IDLE;

    Button();
    Button(int x, int y);

    int notify_mouse(int cx, int cy, int rcx, int rcy, int button_left);
    virtual void on_click() = 0;

    void render(SDL_Renderer *rend);

};

#endif // BUTTON_HH