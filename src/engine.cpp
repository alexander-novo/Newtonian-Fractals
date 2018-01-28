
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

comp easy(const comp& num) {
	return pow(num, 3) + 1.0l;
	//return pow(num, 5) + 1.0l;
	//return sinh(num);
	//return (long double) log(abs(num));
	//return pow(num, 3) + exp(num);
	//return sin(exp(num) * num);
	//return pow(num,5) + 4.0l * pow(num,4) + 3.0l * pow(num,2) - 12.0l;
	//return num * exp(-3.0l * pow(num, 5)) * sin(pow(num, 2));
	//return log(abs(sin(num)));
	//return tan(num);
	//return sin(tan(num));
	//return tan(num * exp(num));
}

comp easyPrime(const comp& num) {
	return 3.0l * pow(num, 2);
	//return 5.0l * pow(num, 4);
	//return cosh(num);
	//return 1.0l / num;
	//return 3.0l * pow(num, 2) + exp(num);
	//return exp(num) * cos(exp(num) * num) * (1.0l + num);
	//return 5.0l * pow(num,4) + 16.0l * pow(num,3) + 6.0l * num;
	//return -1.0l * exp(-3.0l * pow(num, 5)) * ((15.0l * pow(num, 5) - 1.0l) * sin(pow(num, 2)) - 2.0l * pow(num, 2) * cos(pow(num, 2)));
	//return cos(num) / sin(num);
	//return pow(1.0l / cos(num), 2);
	//return cos(tan(num)) * pow(1.0l / cos(num), 2);
	//return 1.0l / pow(cos(num * exp(num)), 2) * (exp(num) + num * exp(num));
}

std::string ErrorString(GLenum error) {
	if (error == GL_INVALID_ENUM) {
		return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
	} else if (error == GL_INVALID_VALUE) {
		return "GL_INVALID_VALUE: A numeric argument is out of range.";
	} else if (error == GL_INVALID_OPERATION) {
		return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
	} else if (error == GL_INVALID_FRAMEBUFFER_OPERATION) {
		return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
	} else if (error == GL_OUT_OF_MEMORY) {
		return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
	} else {
		return "None";
	}
}

void Engine::Run() {
	m_running = true;
	
	double radius = 1;
	//double delta = 0.0025;
	double delta = radius / 1600.0;
	comp num;
	comp _num;
	comp prev_num;
	glm::vec3 hsv;
	glm::vec3 rgb;
	float multiplier = 180 / M_PI;
	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;
	GLuint VB;
	GLuint IB;
	int vertexDimensions = radius / delta * 2;
	Shader* shader = Shader::load("shaders/default.vert", "shaders/default.frag");
	
	shader->Initialize();
	shader->Enable();
	
	time_t now = time(NULL);
	
	vertices.reserve(vertexDimensions * vertexDimensions);
	
	long long numNewtonMethod = 0;
	long long numCalced = 0;
	long long numPerCent = vertexDimensions * vertexDimensions / 100;
	int perCents = 0;
	long long counter = 0;
	
	std::cout << "Calculated: 0%\r" << std::flush;
	//generate our vertices
	for(int x = 0; x < vertexDimensions; x ++) {
		for(int y = 0; y < vertexDimensions; y ++) {
			num = comp(-radius + x * delta, -radius + y * delta);
			_num = num;
			int i;
			for(i = 0; i < 20; i++) {
				prev_num = num;
				num = newtonMethod(num, &easy, &easyPrime);
				numNewtonMethod++;
				if(prev_num == num) {
					break;
				}
			}
			numCalced++;
			hsv.r = std::arg(num) * multiplier;
			hsv.g = std::abs(num) / radius;
			hsv.b = 1.0;
			rgb = Graphics::hsv2rgb(hsv);
			Vertex vert({_num.real() / radius, _num.imag() / radius, 0.0}, rgb);
			vertices.push_back(vert);
			//std::cout << _num << " converges to " << num << " which is " << hsv << " or " << rgb << '\n';
			counter++;
			if(counter == numPerCent) {
				perCents++;
				std::cout << "Calculated: " << perCents << "%\r" << std::flush;
				counter = 0;
			}
		}
	}
	
	std::cout << "Time taken to generate vertices: " << time(NULL) - now << " s" << std::endl;
	now = time(NULL);
	
	//Now generate faces
	unsigned vertexIndex;
	for(unsigned x = 0; x < vertexDimensions - 1; x++) {
		for(unsigned y = 0; y < vertexDimensions - 1; y++) {
			vertexIndex = x * vertexDimensions + y;
			
			//Each grid square split into two triangles, following CCW winding order
			indices.push_back(vertexIndex);
			indices.push_back(vertexIndex + vertexDimensions);
			indices.push_back(vertexIndex + vertexDimensions + 1);
			
			indices.push_back(vertexIndex);
			indices.push_back(vertexIndex + vertexDimensions + 1);
			indices.push_back(vertexIndex + 1);
		}
	}
	
	//Now send it all to OpenGL
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * indices.size(), &indices[0], GL_STATIC_DRAW);
	
	std::cout << std::flush;
	
	//m_window->Swap();
	
	shader->Enable();
	
	glClear(GL_DEPTH_BUFFER_BIT);
	
	//Switch to rendering on the screen
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//clear the screen
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	//Now send vertices, uvs, and normals
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, color));
	
	//Send all our face information
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	
	//Now draw everything
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	m_window->Swap();
	
	std::cout << "Time taken to render: " << time(NULL) - now << " s" << std::endl;
	
	while(m_running) {
		while (SDL_PollEvent(&m_event) != 0) {
			eventHandler(m_DT);
			ImGui_ImplSdlGL3_ProcessEvent(&m_event);
		}
		
		auto error = glGetError();
		if (error != GL_NO_ERROR) {
			std::string val = ErrorString(error);
			std::cout << "Error initializing OpenGL! " << error << ", " << val << std::endl;
		}
	}

	ImGui_ImplSdlGL3_Shutdown();
}

comp Engine::newtonMethod(comp num, comp(*func)(const comp&), comp(*prime)(const comp&)) {
	return num - func(num) / prime(num);
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
