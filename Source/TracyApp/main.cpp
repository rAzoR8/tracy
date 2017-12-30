#include "..\Engine\Engine.hpp"

#pragma comment(lib, "Engine.lib")

int main(int argc, char* argv[])
{
#if defined(WIN32) || defined(_WIN32)
	Tracy::Win32Application App((HINSTANCE)GetModuleHandle(NULL));
#elif defined(__linux__) || defined(__unix__)
	// Not implemented yet!
#endif

	if (App.Init(1280u, 720u, Tracy::EGraphicsAPI::eVulkan))
	{
		return App.Run();
	}

	return EXIT_FAILURE;
}