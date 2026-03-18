#include "vzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Vesper/Renderer/GraphicsContext.h"

namespace Vesper {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: m_WindowHandle(windowHandle)
	{
		VZ_CORE_ASSERT(windowHandle, "Window handle is null!");

	}

	OpenGLContext::~OpenGLContext()
	{
	}

	void OpenGLContext::Init()
	{
		VZ_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		VZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		VZ_CORE_INFO("OpenGL Info:");
		VZ_CORE_INFO("  Vendor: {0}", (const char *)glGetString(GL_VENDOR));
		VZ_CORE_INFO("  Renderer: {0}", (const char *)glGetString(GL_RENDERER));
		VZ_CORE_INFO("  Version: {0}", (const char *)glGetString(GL_VERSION));

#ifdef VZ_ENABLE_ASSERTS
		int major = 0, minor = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		VZ_CORE_ASSERT(major > 4 || (major == 4 && minor >= 5), "Vesper requires at least OpenGL version 4.5!");
#endif

	}

	void OpenGLContext::SwapBuffers()
	{
		VZ_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);

	}



}