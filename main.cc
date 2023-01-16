#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <vector>
#include <iostream>

#include "Window.hh"
#include "Button.hh"
#include "Slider.hh"

SDL_Window *win;
SDL_Renderer *rend;
class MyButton1 : public Button {
	public:
		void on_click() {
			std::cout << "onclick\n";
		}
};

class MySlider : public Slider {
	public:
	void on_click() {
		std::cout<<"Slider click\n";
	}
};

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_CreateWindow("Hello world", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			2*640,2*480,
			SDL_WINDOW_SHOWN);
	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event ev;
	bool running = true;

    Window wnd(rend, 1,1, 200, 200);
    MyButton1 btn0;
	MySlider sl0;
    //wnd.add_widget(&btn0);
	wnd.add_widget(&sl0);
	while (running) {
		int cx, cy;
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
				case SDL_QUIT: running = false; break;
				case SDL_MOUSEBUTTONUP: {
					wnd.input_mouse(ev.button.x, ev.button.y, BUTTON_UP); break;
				}
				case SDL_MOUSEBUTTONDOWN: wnd.input_mouse(ev.button.x, ev.button.y, BUTTON_DOWN); break;
				case SDL_MOUSEMOTION: wnd.input_mouse(ev.motion.x, ev.motion.y, BUTTON_NO_CHANGE); break;

			}
		}

        wnd.update();

		SDL_SetRenderDrawColor(rend,255, 255, 255, 255);
		SDL_RenderClear(rend);

        wnd.render();

		SDL_RenderPresent(rend);
		SDL_Delay(1000/60);
	} 
    return 0;
}