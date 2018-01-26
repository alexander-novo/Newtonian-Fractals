#ifndef ENGINE_H
#define ENGINE_H

#include <sys/time.h>
#include <assert.h>
#include <random>
#include <complex>

#include "window.h"
#include "graphics.h"
#include "Menu.h"

#define ENGINE_NAME_DEFAULT "Newtonian Method Fractals"
#define ENGINE_WIDTH_DEFAULT 1600
#define ENGINE_HEIGHT_DEFAULT 1600
#define ENGINE_FULLSCREEN_DEFAULT false

typedef  std::complex<long double> comp;

class Engine {
	public:
		struct Context {
			std::string name = ENGINE_NAME_DEFAULT;
			int width = ENGINE_WIDTH_DEFAULT;
			int height = ENGINE_HEIGHT_DEFAULT;
			bool fullscreen = ENGINE_FULLSCREEN_DEFAULT;
		};
		
		Engine(const Context &ctx);
		
		~Engine();
		
		//Initialise OpenGL
		//Call after starting OpenGL
		bool Initialize();
		
		//Run the actual program
		void Run();
		
		//Get number of milliseconds since last frame
		unsigned int getDT();
		//Get the current time in milliseconds
		long long GetCurrentTimeMillis();
		
		//Read-only
		const int& windowWidth;
		const int& windowHeight;
		
		const Context& ctx;
	
	private:
		
		Context _ctx;
		Window *m_window;
		SDL_Event m_event;
		
		Graphics *m_graphics = nullptr;
		unsigned int m_DT;
		long long m_currentTimeMillis;
		bool m_running;

		Menu *m_menu;
		
		//Handle keyboard controls
		void Keyboard(unsigned dt);
		//Handle other events (mouse, etc.)
		void eventHandler(unsigned dt);
		
		comp newtonMethod(comp, comp(*func)(const comp&), comp(*prime)(const comp&));
};

#endif // ENGINE_H
