#pragma once

#ifdef VZ_PLATFORM_WINDOWS

extern Vesper::Application* Vesper::CreateApplication();

int main(int argc, char** argv)
{

	Vesper::Log::Init();

	VZ_PROFILE_BEGIN_SESSION("Startup", "VesperProfile-Startup.json");
	auto app = Vesper::CreateApplication();
	VZ_PROFILE_END_SESSION();

	VZ_PROFILE_BEGIN_SESSION("Runtime", "VesperProfile-Runtime.json");
	app->Run();
	VZ_PROFILE_END_SESSION(); 

	VZ_PROFILE_BEGIN_SESSION("Shutdown", "VesperProfile-Shutdown.json");
	delete app;
	VZ_PROFILE_END_SESSION();
}

#endif