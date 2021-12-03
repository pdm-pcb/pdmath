#ifndef GLDEBUGGER_HPP
#define GLDEBUGGER_HPP

#include "glad/glad.h"

class GLDebugger {
public:
	static void GLAPIENTRY
		error_callback(GLenum source,
					   GLenum type, GLuint id, GLenum severity,
					   GLsizei length, const GLchar *message,
					   const void *user_data);

	GLDebugger();
};

#endif // GLDEBUGGER_HPP