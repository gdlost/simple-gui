#ifndef WINDOW_HH
#define WINDOW_HH
#include <SDL2/SDL.h>
#include <vector>

#include "Widget.hh"

#define BUTTON_UP 0
#define BUTTON_DOWN 1
#define BUTTON_NO_CHANGE 2

#define SDL_SaveRenderDrawColor() \
	Uint8 rxx, gxx, bxx, axx; \
	SDL_GetRenderDrawColor(rend, &rxx, &gxx, &bxx, &axx);
#define SDL_RestoreRenderDrawColor() \
	SDL_SetRenderDrawColor(rend, rxx, gxx, bxx, axx);

class Window {
    public:
    // Variables
    SDL_Renderer *rend;
    int x, y, w, h;
    Rect bounds;
    std::vector<Widget*> wlist;

    // Widgets que estan procesando eventos
    std::vector<Widget*> wprocessing;
    
    Window(SDL_Renderer *rend, int x, int y, int w, int h);

    void add_widget(Widget *w);
    void add_widget(Widget *w, int x, int y);

    void input_mouse(int cx, int cy, int button_left);

    void update();
    void render();
};

#endif 