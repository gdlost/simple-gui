#include "Window.hh"

Window::Window(SDL_Renderer *rend, int x, int y, int w, int h)
    : rend(rend), x(x), y(y), w(w), h(h) {}

void Window::add_widget(Widget *w) {
	wlist.push_back(w);
}

void Window::add_widget(Widget *w, int x, int y) {
	// Por ahora, asumir lm nulo
	w->outline.x = x;
	w->outline.y = y;
	wlist.push_back(w);
}

void Window::input_mouse(int cx, int cy, int button_left) {
	// Procesar mouse para el widget que quedo en cola, por si acaso :D
	if (wprocessing.size() > 0) {
		wprocessing.at(0)->notify_mouse(cx, cy, button_left);
		wprocessing.pop_back();
	}
    for (auto it = this->wlist.begin(); it != this->wlist.end(); it++) {
     	int x = (*it)->outline.x;
		int y = (*it)->outline.y;
		int w = (*it)->outline.w;
		int h = (*it)->outline.h;
        int retval;

		if ((x < cx && cx < x + w) && (y < cy && cy < y + h)) 
		{
            // Notificarle sobre una accion del mouse en el
		    retval = (*it)->notify_mouse(cx, cy, button_left);
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
	SDL_Rect bg = {
		.x = this->x,
		.y = this->y,
		.w = this->w,
		.h = this->h
	};
	SDL_SetRenderDrawColor(rend, 0x40, 0x80, 0x80, 0xff);	
	SDL_RenderFillRect(rend, &bg);
	for (auto it = this->wlist.begin(); it != this->wlist.end(); it++) {
		(*it)->render(this->rend);
	}
	SDL_RestoreRenderDrawColor();
}