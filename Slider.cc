#include "Slider.hh"
#include "Window.hh"
#include <SDL2/SDL_render.h>

#define GAPY 4
#define KNOB_H (29 - 2*GAPY)
#define KNOB_W 9
#define GAPX (KNOB_W - 1)/2

Slider::Slider() {
    this->outline = Rect(200, 29);
    
    this->bar = Rect(200 - 2*GAPX, 3);
    this->bar.x = GAPX;
    this->bar.y = GAPY + KNOB_H/2;

    this->knob = Rect(KNOB_W, KNOB_H);
    this->knob.x = GAPX;
    this->knob.y = GAPY;

    this->min = 0;
    this->max = 100;
    this->range = 100;
}

Slider::Slider(int x, int y) {
    this->outline = Rect(200, 29);
    this->outline.x = x;
    this->outline.y = y;

    this->bar = Rect(200 - 2*GAPX, 3);
    this->bar.x = this->outline.x + GAPX;
    this->bar.y = this->outline.y + GAPY + KNOB_H/2;

    this->knob = Rect(5, 21);
    this->knob.x = this->outline.x + GAPX;
    this->knob.y = this->outline.y + GAPY;

    this->min = 0;
    this->max = 100;
    this->range = 100;
}

void Slider::calculate_knob() {

}

int old_cx = 0;
int old_cy = 0;

int Slider::notify_mouse(int cx, int cy, int button_left) {
    switch (this->state) {
        case sSLIDER_IDLE: {
            if (this->knob.hasPointIn(cx, cy)) {
                this->state = sSLIDER_HOVER;    
            }
            // Cuando pasa a hover, se necesita saber si es que el cursor
            // se salio
            return 1;
            break;
        }
        case sSLIDER_HOVER: {
            if (!this->knob.hasPointIn(cx, cy)) {
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
            } else if (!this->inside_my_bounds(cx, cy)) {
                this->state = sSLIDER_IDLE;
                return 0;
            } else if (button_left == BUTTON_NO_CHANGE) {
                int dcx = cx - old_cx;
				old_cx = cx;

				// TODO: Calcular esto de mejor manera
				if (this->knob.x < (GAPX - (this->knob.w-1)/2)) {
					this->knob.x = (GAPX - (this->knob.w-1)/2);
				} else if (this->knob.x + this->knob.w > (this->bar.w + GAPX + (this->knob.w-1)/2)) {
					this->knob.x = (this->bar.w + GAPX + (this->knob.w-1)/2);
				}else {
					this->knob.x += dcx;
				}
                std::cout << "dcx: " << dcx 
				<< '\n';
				float a = this->range / this->bar.w;
				if (a >= this->step) {
					this->current = (this->knob.x - this->bar.x) * a;
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
    SDL_RenderFillRect(rend, &(this->outline));
    bar_bg.sdl2_SetRenderDrawColor(rend);
    SDL_RenderFillRect(rend, &(this->bar));
    knob_bg.sdl2_SetRenderDrawColor(rend);
//    SDL_RenderFillRect(rend, &(this->knob));
	SDL_RenderDrawRect(rend, &(this->knob));

    SDL_RestoreRenderDrawColor();
}
