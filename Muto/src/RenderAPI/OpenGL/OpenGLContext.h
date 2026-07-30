#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Muto {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual ~OpenGLContext();
		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}