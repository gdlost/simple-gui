#include "Checkbox.hh"

Checkbox::Checkbox(int x, int y) {
	resize(25, 25);
	move(x, y);
}

Checkbox::Checkbox(bool checked) {
	resize(25, 25);
	this->checked = checked;
}

void Checkbox::render(SDL_Renderer *rend) {
	RGBA default_color = RGBA::Gray();
	RGBA hover_color = RGBA::Silver();
	RGBA checked_color = RGBA::Red();

	SDL_SaveRenderDrawColor();
	// TODO: cambiar los colores
	switch (this->state) {
		case sBUTTON_IDLE: {
			if (!this->checked) {
				default_color.sdl2_SetRenderDrawColor(rend); break;
			}
			else  {
				checked_color.sdl2_SetRenderDrawColor(rend); break;
			}
		}
		case sBUTTON_HOVER: {
			if (!this->checked) {
				hover_color.sdl2_SetRenderDrawColor(rend); break;
			} else {
				hover_color = RGBA::Maroon();
				hover_color.sdl2_SetRenderDrawColor(rend); break;
			}
		}
		case sBUTTON_ACTIVE: {
			if (!this->checked) {
				default_color = RGBA::Maroon();
				default_color.sdl2_SetRenderDrawColor(rend); break;
			} else {
				checked_color = RGBA::Olive();
				checked_color.sdl2_SetRenderDrawColor(rend); break;
			}
		}
	}
	SDL_RenderFillRect(rend, this);
	SDL_RestoreRenderDrawColor();
}

int Checkbox::notify_mouse(int cx, int cy, int rcx, int rcy, int button_left) {
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
				this->checked = !this->checked;
                return 1;
            }
            return 1;
            break;
        }
        case sBUTTON_ACTIVE: {
            if (button_left == BUTTON_UP) {
                this->state = sBUTTON_HOVER;
                return 1;
            } else if (!hasPointIn(cx, cy)) {
                this->state = sBUTTON_IDLE;
                return 0;
            }
            return 1;
        }
    }
}


