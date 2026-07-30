#include "mupch.h"
#include <Muto.h>
#include <App/EntryPoint.h>

#include "EditorLayer.h"

namespace Muto {

	class Mutare : public Muto::Application
	{
	public:
		Mutare() 
			: Application("Mutare")
		{

			PushLayer(new EditorLayer());
		}

		~Mutare() {

		}
	};

	//Application* CreateApplication()
	//{
	//	return new Mutare();
	//}

}