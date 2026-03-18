#include "vzpch.h"
#include "RenderCommand.h"

#include "RenderAPI/OpenGL/OpenGLRendererAPI.h"

namespace Vesper {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}