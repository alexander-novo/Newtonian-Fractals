
#include "engine.h"

Engine::Engine(const Context &a) : _ctx(a), ctx(_ctx), windowWidth(_ctx.width), windowHeight(_ctx.height) {}

Engine::~Engine() {
	if(m_window != nullptr)
	{
		delete m_window;
		m_window = nullptr;
	}
	if(m_graphics != nullptr)
	{
		delete m_graphics;
		m_graphics = nullptr;
	}
}

bool Engine::Initialize() {
	// Start a window
	m_window = new Window();
	if (!m_window->Initialize(_ctx.name, &_ctx.width, &_ctx.height)) {
		printf("The window failed to initialize.\n");
		return false;
	}

	//Start the menu and connect it to the window
	m_menu = new Menu(*m_window);

	// Start the graphics
	m_graphics = new Graphics(*m_menu, _ctx.width, _ctx.height);

	if (!m_graphics->Initialize(_ctx.width, _ctx.height)) {
		printf("The graphics failed to initialize.\n");
		return false;
	}

	// Set the time
	m_currentTimeMillis = GetCurrentTimeMillis();

	// No errors
	return true;
}

void Engine::Run() {
	m_running = true;

	while (m_running) {
		// Update the DT
		m_DT = getDT();
		
		while (SDL_PollEvent(&m_event) != 0) {
			eventHandler(m_DT);
			ImGui_ImplSdlGL3_ProcessEvent(&m_event);
		}

		// Check the keyboard input
		Keyboard(m_DT);

		// Update menu options and labels
		m_menu->update(m_DT, _ctx.width, _ctx.height);

		//Render everything
		m_graphics->Render();
		m_menu->render();

		// Swap to the Window
		m_window->Swap();
	}

	ImGui_ImplSdlGL3_Shutdown();
}

void Engine::Keyboard(unsigned dt) {
	const Uint8* keyState = SDL_GetKeyboardState(nullptr);
}

void Engine::eventHandler(unsigned dt) {
	//Quit program
	if (m_event.type == SDL_QUIT
		|| m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_ESCAPE) {
		m_running = false;
	}
}

unsigned int Engine::getDT() {
	long long TimeNowMillis = GetCurrentTimeMillis();
	assert(TimeNowMillis >= m_currentTimeMillis);
	unsigned int DeltaTimeMillis = (unsigned int) (TimeNowMillis - m_currentTimeMillis);
	m_currentTimeMillis = TimeNowMillis;
	return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis() {
	timeval t;
	gettimeofday(&t, nullptr);
	long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
	return ret;
}