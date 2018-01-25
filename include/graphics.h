#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <algorithm>

#include "graphics_headers.h"
#include "shader.h"
#include "Menu.h"

class Graphics {
	public:
		Graphics(Menu& menu, const int& w, const int& h);
		~Graphics();
		
		//Initialise OpenGL
		bool Initialize(int width, int height);
		
		void Render();
	private:
		const int& windowWidth;
		const int& windowHeight;
		
		std::string ErrorString(GLenum error);
		
		Menu& m_menu;
};

#endif /* GRAPHICS_H */
