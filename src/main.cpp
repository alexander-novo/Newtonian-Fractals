#include "main.h"

int main(int argc, char** argv) {
	srand(time(nullptr));
	
	//Stores the properties of our engine, such as window name/size, fullscreen, and shader info
	Engine::Context ctx;
	
	// Start an engine and run it then cleanup after
	Engine* engine = new Engine(ctx);
	if (!engine->Initialize()) {
		printf("The engine failed to start.\n");
		delete engine;
		engine = nullptr;
		return 1;
	}
	
	engine->Run();
	
	delete engine;
	engine = nullptr;
	
	return 0;
}

std::ostream& operator<<(std::ostream& stream, const glm::vec3 & vector) {
	stream << "(" << vector.x << "," << vector.y << "," << vector.z << ")";
	return stream;
}