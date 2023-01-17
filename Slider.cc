#include "Slider.hh"
#include "Window.hh"
#include <SDL2/SDL_render.h>

#define GAPY 4
#define KNOB_H (23 - 2*GAPY)
#define KNOB_W 9
#define GAPX (KNOB_W - 1)/2

Slider::Slider() {
    resize(200, 29);
    
    bar.setBounds(GAPX, GAPY + KNOB_H/2, 200 - 2 * GAPX, 3);
    knob.setBounds(GAPX, GAPY, KNOB_W, KNOB_H);

    this->min = 0;
    this->max = 100;
    this->range = 100;
}

Slider::Slider(int x, int y) {
    setBounds(x, y, 200, 29);

    bar.setBounds(this->x + GAPX, this->y + GAPY + KNOB_H/2, 200 - 2 * GAPX, 3);
    knob.setBounds(this->x + GAPX, this->y + GAPY, 5, 21);

    this->min = 0;
    this->max = 100;
    this->range = 100;
}

void Slider::calculate_knob() {

}

static int old_cx = 0;
static int old_cy = 0;

int Slider::notify_mouse(int cx, int cy, int rcx, int rcy, int button_left) {
    switch (state) {
        case sSLIDER_IDLE: {
            if (knob.hasPointIn(cx, cy)) {
                this->state = sSLIDER_HOVER;    
            }
            // Cuando pasa a hover, se necesita saber si es que el cursor
            // se salio
            return 1;
            break;
        }
        case sSLIDER_HOVER: {
            if (!knob.hasPointIn(cx, cy)) {
                this->state = sSLIDER_IDLE;
                return 0;
            } else if (button_left == BUTTON_DOWN && this->knob.hasPointIn(cx, cy)) {
                this->state = sSLIDER_ACTIVE;
                old_cx = cx;
                old_cy = cy;
                return 1;
            }
            return 1;
            break;
        }
        case sSLIDER_ACTIVE: {
            if (button_left == BUTTON_UP) {
                this->state = sSLIDER_HOVER;
                this->on_click();
                return 1;
            } else if (!hasPointIn(cx, cy)) {
                this->state = sSLIDER_IDLE;
                return 0;
            } else if (button_left == BUTTON_NO_CHANGE) {
                int dcx = cx - old_cx;
				old_cx = cx;

				// TODO: Calcular esto de mejor manera
				if (this->knob.x < (GAPX - (this->knob.w-1)/2)) {
					this->knob.x = (GAPX - (this->knob.w-1)/2);
				} else if (this->knob.x + this->knob.w > (this->bar.w + this->bar.x + (this->knob.w-1)/2) + 1) {
					this->knob.x = (this->bar.w + this->bar.x - (this->knob.w-1)/2);
				}else {
					this->knob.x += dcx;
				}
                std::cout << "dcx: " << dcx 
				<< '\n';
				float a = this->range / this->bar.w;
				if (a >= this->step) {
					this->current = (this->knob.x + (this->knob.w-1)/2 - this->bar.x) * a;
					std::cout << "current value is: " << this->current << '\n';
				} else {

				}
            }
            return 1;
        }
    }
}

void Slider::render(SDL_Renderer *rend) {
    RGBA outline_bg = RGBA::White();
    RGBA bar_bg = RGBA::Red();
    RGBA knob_bg = RGBA::Green();
    if (this->state == sSLIDER_HOVER) {
        knob_bg = RGBA::Aqua();
    }

    SDL_SaveRenderDrawColor();

    outline_bg.sdl2_SetRenderDrawColor(rend);
    SDL_RenderFillRect(rend, (this));
    bar_bg.sdl2_SetRenderDrawColor(rend);
    SDL_RenderFillRect(rend, &(this->bar));
    knob_bg.sdl2_SetRenderDrawColor(rend);
//    SDL_RenderFillRect(rend, &(this->knob));
	SDL_RenderDrawRect(rend, &(this->knob));

    SDL_RestoreRenderDrawColor();
}
