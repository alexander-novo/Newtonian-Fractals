#ifndef TUTORIAL_MENU_H
#define TUTORIAL_MENU_H

#include "graphics_headers.h"
#include "window.h"
#include "imgui.h"
#include "imgui_internal.h"

class Object;

class Menu {
	public:
		//All the different options the menu changes
		struct Options {};
		
		Menu(Window& window);
		
		//Add stuff to the menu and check if anything has changed since last time
		void update(int dt, float width, float height);
		//Draw everything
		void render();

		//Read-only menu options
		const Options& options;
	private:
		//Keep track of where we're rendering and the sun
		Window& window;
		
		Options _options;
};

#endif //TUTORIAL_MENU_H
