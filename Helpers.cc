#include "Helpers.hh"
#include <SDL2/SDL_render.h>

Rect::Rect() {}

Rect::Rect(int w, int h) {
    this->x = 0;
    this->y = 0;
    this->w = w;
    this->h = h;
}

bool Rect::hasPointIn(int x, int y) {
#if 0
    std::cout << "x: " << x
        << ", y: " << y
        << ", this->x: " << this->x
        << ", this->y: " << this->y
        << ", this->w: " << this->w
        << ", this->h: " << this->h
        << '\n';
    bool cond = ((this->x < x && x < this->x + this->w)
        && (this->y < y && y < this->y + this->w));
    std::cout << cond << '\n';
#endif
    return ((x >= this->x && x <= this->x + this->w)
        && (y >= this->y && y <= this->y + this->h));
}

// ---

RGBA RGBA::White() {
    return RGBA(0xff, 0xff, 0xff, 0xff);
}

RGBA RGBA::Silver() {
    return RGBA(0xc0, 0xc0, 0xc0, 0xc0);
}

RGBA RGBA::Gray() {
    return RGBA(0x80, 0x80, 0x80, 0xff);
}

RGBA RGBA::Black() {
    return RGBA(0x00, 0x00, 0x00, 0xff);
}

RGBA RGBA::Maroon() {
    return RGBA(0x80, 0x00, 0x00, 0xff);
}

RGBA RGBA::Red() {
    return RGBA(0xff, 0x00, 0x00, 0xff);
}

RGBA RGBA::Orange() {
    return RGBA(0xff, 0xa5, 0x00, 0xff);
}

RGBA RGBA::Yellow() {
    return RGBA(0xff, 0xff, 0x00, 0xff);
}

RGBA RGBA::Olive() {
    return RGBA(0x80, 0x80, 0x00, 0xff);
}

RGBA RGBA::Green() {
    return RGBA(0x00, 0x80, 0x00, 0xff);
}

RGBA RGBA::Aqua() {
    return RGBA(0x00, 0xff, 0xff, 0xff);
}

RGBA RGBA::Blue() {
    return RGBA(0x00, 0x00, 0xff, 0xff);
}

RGBA RGBA::Navy() {
    return RGBA(0x00, 0x00, 0x80, 0xff);
}

RGBA RGBA::Teal() {
    return RGBA(0x00, 0x80, 0x80, 0xff);
}

RGBA RGBA::Fuchsia() {
    return RGBA(0xff, 0x00, 0xff, 0xff);
}

RGBA RGBA::Purple() {
    return RGBA(0x80, 0x00, 0x80, 0xff);
}


RGBA::RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
        : r(r), g(g), b(b), a(a) {}

void RGBA::sdl2_SetRenderDrawColor(SDL_Renderer *rend) {
    SDL_SetRenderDrawColor(rend, this->r, this->g, this->b, this->a);
}