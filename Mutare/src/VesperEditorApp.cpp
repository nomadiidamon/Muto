#include <Vesper.h>
#include <Vesper/App/EntryPoint.h>

#include "EditorLayer.h"

namespace Vesper {

	class VesperEditor : public Vesper::Application
	{
	public:
		VesperEditor() 
			: Application("Mutare")
		{

			PushLayer(new EditorLayer());
		}

		~VesperEditor() {

		}
	};

	Application* CreateApplication()
	{
		return new VesperEditor();
	}

}