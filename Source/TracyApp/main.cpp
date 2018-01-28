#include "..\Engine\Engine.hpp"
#include "..\Engine\Display\Vulkan\VulkanPrimitiveMeshGenerator.h"

using namespace Tracy;

int main(int argc, char* argv[])
{
#if defined(WIN32) || defined(_WIN32)
	Win32Application App((HINSTANCE)GetModuleHandle(NULL));
#elif defined(__linux__) || defined(__unix__)
	// Not implemented yet!
#endif

	RenderGraphDesc Desc{};

	if (App.Initialize(1280u, 720u, Tracy::EGraphicsAPI::eVulkan, Desc))
	{
		Mesh m = VulkanPrimitiveMeshGenerator::TriangleVertPos();

		return App.Run();
	}

	return EXIT_FAILURE;
}