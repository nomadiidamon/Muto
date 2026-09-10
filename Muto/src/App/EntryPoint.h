#pragma once

#if defined(MU_PLATFORM_WINDOWS) || defined(MU_PLATFORM_LINUX)

extern Muto::Application* Muto::CreateApplication();

int main(int argc, char** argv)
{

	Muto::Log::Init();

	MU_PROFILE_BEGIN_SESSION("Startup", "MutoProfile-Startup.json");
	auto app = Muto::CreateApplication();
	MU_PROFILE_END_SESSION();

	MU_PROFILE_BEGIN_SESSION("Runtime", "MutoProfile-Runtime.json");
	app->Run();
	MU_PROFILE_END_SESSION(); 

	MU_PROFILE_BEGIN_SESSION("Shutdown", "MutoProfile-Shutdown.json");
	delete app;
	MU_PROFILE_END_SESSION();
}

#endif