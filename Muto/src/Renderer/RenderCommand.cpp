#include "mupch.h"
#include "RenderCommand.h"

#include "RenderAPI/OpenGL/OpenGLRendererAPI.h"

namespace Muto {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}