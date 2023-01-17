#include "Button.hh"
#include "Window.hh"
#include <SDL2/SDL_render.h>

Button::Button() {
    resize(100, 28);
}

Button::Button(int x, int y) {
    setBounds(x, y, 100, 28);
}

// Esta funcion, solo se llama en caso de que el cursor este DENTRO del
// boton, o en caso de que processing_events = true
// Retorna 1, si es que en el siguiente frame se debe verificar algo
int Button::notify_mouse(int cx, int cy, int rcx, int rcy, int button_left) {
    switch (this->state) {
        case sBUTTON_IDLE: {
            this->state = sBUTTON_HOVER;
            // Cuando pasa a hover, se necesita saber si es que el cursor
            // se salio
            return 1;
            break;
        }
        case sBUTTON_HOVER: {
            if (!hasPointIn(cx, cy)) {
                this->state = sBUTTON_IDLE;
                return 0;
            } else if (button_left == BUTTON_DOWN) {
                this->state = sBUTTON_ACTIVE;
                return 1;
            }
            return 1;
            break;
        }
        case sBUTTON_ACTIVE: {
            if (button_left == BUTTON_UP) {
                this->state = sBUTTON_HOVER;
                this->on_click();
                return 1;
            } else if (!hasPointIn(cx, cy)) {
                this->state = sBUTTON_IDLE;
                return 0;
            }
            return 1;
        }
    }
}

void Button::render(SDL_Renderer *rend) {
    RGBA default_color(0x80, 0x80, 0x80, 0xff);
    RGBA hover_color(0x32, 0x2d, 0x31, 0xff);
    RGBA active_color(0xff, 0x00, 0x80, 0xff);

    SDL_SaveRenderDrawColor();
    switch (this->state) {
        case sBUTTON_IDLE: default_color.sdl2_SetRenderDrawColor(rend); break;
        case sBUTTON_ACTIVE: active_color.sdl2_SetRenderDrawColor(rend); break;
        case sBUTTON_HOVER: hover_color.sdl2_SetRenderDrawColor(rend); break;
    }
    SDL_RenderFillRect(rend, (this));
    SDL_RestoreRenderDrawColor();

}