#include "graphics.h"

Graphics::Graphics(Menu& menu, const int& w, const int& h) : windowWidth(w),
                                                             windowHeight(h),
                                                             m_menu(menu) {}

Graphics::~Graphics() {}

bool Graphics::Initialize(int width, int height) {
	// Used for the linux OS
#if !defined(__APPLE__) && !defined(MACOSX)
	// cout << glewGetString(GLEW_VERSION) << endl;
	glewExperimental = GL_TRUE;
	
	auto status = glewInit();
	
	// This is here to grab the error that comes from glew init.
	// This error is an GL_INVALID_ENUM that has no effects on the performance
	glGetError();
	
	//Check for error
	if (status != GLEW_OK) {
		std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
		return false;
	}
#endif
	
	// For OpenGL 3
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	//enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	return true;
}

glm::vec3 Graphics::hsv2rgb(const glm::vec3& in) {
	float hh, p, q, t, ff;
	long i;
	glm::vec3 out;
	
	hh = in.r;
	while(hh < 0) {
		hh += 360.0;
	}
	while(hh >= 360.0) {
		hh -= 360.0;
	}
	hh /= 60.0;
	i = (long) hh;
	ff = hh - i;
	p = in.b * (1.0 - in.g);
	q = in.b * (1.0 - (in.g * ff));
	t = in.b * (1.0 - (in.g * (1.0 - ff)));
	
	switch (i) {
		case 0:
			out.r = in.b;
			out.g = t;
			out.b = p;
			break;
		case 1:
			out.r = q;
			out.g = in.b;
			out.b = p;
			break;
		case 2:
			out.r = p;
			out.g = in.b;
			out.b = t;
			break;
		
		case 3:
			out.r = p;
			out.g = q;
			out.b = in.b;
			break;
		case 4:
			out.r = t;
			out.g = p;
			out.b = in.b;
			break;
		case 5:
		default:
			out.r = in.b;
			out.g = p;
			out.b = q;
			break;
	}
	return out;
}

void Graphics::Render() {
	//Switch to rendering on the screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Get any errors from OpenGL
//	auto error = glGetError();
//	if (error != GL_NO_ERROR) {
//		std::string val = ErrorString(error);
//		std::cout << "Error initializing OpenGL! " << error << ", " << val << std::endl;
//	}
}

std::string Graphics::ErrorString(GLenum error) {
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