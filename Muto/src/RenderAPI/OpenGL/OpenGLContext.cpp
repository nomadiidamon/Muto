#include "mupch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Renderer/GraphicsContext.h"

namespace Muto {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: m_WindowHandle(windowHandle)
	{
		MU_CORE_ASSERT(windowHandle, "Window handle is null!");

	}

	OpenGLContext::~OpenGLContext()
	{
	}

	void OpenGLContext::Init()
	{
		MU_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MU_CORE_ASSERT(status, "Failed to initialize Glad!");
		MU_CORE_INFO("OpenGL Info:");
		MU_CORE_INFO("  Vendor: {0}", (const char *)glGetString(GL_VENDOR));
		MU_CORE_INFO("  Renderer: {0}", (const char *)glGetString(GL_RENDERER));
		MU_CORE_INFO("  Version: {0}", (const char *)glGetString(GL_VERSION));

#ifdef MU_ENABLE_ASSERTS
		int major = 0, minor = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		MU_CORE_ASSERT(major > 4 || (major == 4 && minor >= 5), "Muto requires at least OpenGL version 4.5!");
#endif

	}

	void OpenGLContext::SwapBuffers()
	{
		MU_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);

	}



}