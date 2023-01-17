#ifndef HELPERS_HH
#define HELPERS_HH

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_render.h>
#include <iostream>

// Todas las ventanas son rectangulos :D
class Rect : public SDL_Rect {
    public:
    Rect();
    Rect(int w, int h);

    bool hasPointIn(int x, int y);
    void move(int x, int y);
    void moveRelative(int dx, int dy);
    void resize(int w, int h);
    void setBounds(int x, int y, int w, int h);
};

class RGBA {
    private:
    Uint8 r, g, b, a;

    public:

    static RGBA White();
    static RGBA Silver();
    static RGBA Gray();
    static RGBA Black();
    static RGBA Maroon();
    static RGBA Red();
    static RGBA Orange();
    static RGBA Yellow();
    static RGBA Olive();
    static RGBA Green();
    static RGBA Aqua();
    static RGBA Blue();
    static RGBA Navy();
    static RGBA Teal();
    static RGBA Fuchsia();
    static RGBA Purple();

    RGBA();
    RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void sdl2_SetRenderDrawColor(SDL_Renderer *rend);
};

#endif // HELPERS_HH