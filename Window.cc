#include "Window.hh"
#include <SDL2/SDL_render.h>
#include <iostream>

Window::Window(SDL_Renderer *rend, int x, int y, int w, int h)
    : rend(rend) {

	titlebar.setBounds(x, y, w, 18);
	bounds.setBounds(x, y + titlebar.h, w, h);

	// https://www.pinterest.cl/pin/313352086567898841/
	titlebar_color = RGBA(0x30, 0x3a, 0x52, 0xff);
}

void Window::add_widget(Widget *w) {
	w->moveRelative(bounds.x, bounds.y);
	wlist.push_back(w);
}

void Window::add_widget(Widget *w, int x, int y) {
	// No se usa LM por
	w->move(x + bounds.x, y + bounds.y);
	wlist.push_back(w);
}

void Window::move(int x, int y) {
	titlebar.move(x, y);
	bounds.move(x, y + titlebar.h);
}

void Window::move_relative(int dx, int dy) {
	titlebar.moveRelative(dx, dy);
	bounds.moveRelative(dx, dy);
}

void Window::input_mouse(int cx, int cy, int button_left) {
	static int old_cx = 0;
	static int old_cy = 0;
	
	// Procesar mouse para el widget que quedo en cola, por si acaso :D
	if (wprocessing.size() > 0) {
		Widget *wid = wprocessing.at(0);
     	int x = (wid)->x;
		int y = (wid)->y;
		int rcx = cx - x;
		int rcy = cy - y;
		wid->notify_mouse(cx, cy, rcx, rcy, button_left);
		wprocessing.pop_back();
	}

	if (this->titlebar.hasPointIn(cx, cy)) {
		switch (this->titlebar_state) {
			case TITLEBAR_NORMAL: {
				if (button_left == BUTTON_DOWN) {
					this->titlebar_state = TITLEBAR_CLICKED;
					// Aqui empieza el movimiento!
					old_cx = cx;
					old_cy = cy;
					return;
				}
				break;
			}
			case TITLEBAR_CLICKED: {				
				if (button_left == BUTTON_NO_CHANGE) {
					//this->titlebar.x += (cx - old_cx);
					//this->titlebar.y += (cy - old_cy);
					move_relative(cx - old_cx, cy - old_cy);
					for (auto it = this->wlist.begin(); it != this->wlist.end(); it++) {
						(*it)->moveRelative(cx - old_cx, cy - old_cy);
					}
					old_cx = cx;
					old_cy = cy;
					return;
				}
				if (button_left == BUTTON_UP) {
					this->titlebar_state = TITLEBAR_NORMAL;
					return;
				}
			}
		}
		return;
	} else {
		if (this->titlebar_state == TITLEBAR_CLICKED) {
			this->titlebar_state = TITLEBAR_NORMAL;
			return;
		}
	}

    for (auto it = this->wlist.begin(); it != this->wlist.end(); it++) {
        int retval;

		if ((*it)->hasPointIn(cx, cy)) 
		{
			// Calcular posicion relativa
			int x = (*it)->x;
			int y = (*it)->y;
			int rcx = cx - x;
			int rcy = cy - y;
            // Notificarle sobre una accion del mouse en el
		    retval = (*it)->notify_mouse(cx, cy, rcx, rcy, button_left);
			if (retval)
				wprocessing.push_back(*it);
			break;
		} 
    }
}

void Window::update() {

}

void Window::render() {
	SDL_SaveRenderDrawColor();
	this->titlebar_color.sdl2_SetRenderDrawColor(this->rend);
	SDL_RenderFillRect(rend, &(this->titlebar));
	SDL_SetRenderDrawColor(rend, 0x40, 0x80, 0x80, 0xff);	
	SDL_RenderFillRect(rend, &(this->bounds));
	for (auto it = this->wlist.begin(); it != this->wlist.end(); it++) {
		(*it)->render(this->rend);
	}
	SDL_RestoreRenderDrawColor();
}