#include "mupch.h"
#include "RenderCommand.h"

#include "RenderAPI/OpenGL/OpenGLRendererAPI.h"

namespace Muto {
	RenderAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}