#include "..\Engine\Engine.hpp"

#include "..\Engine\Datastructures\Allocators.h"
#include "StopWatch.h"
using namespace Tracy;

int main(int argc, char* argv[])
{
#if defined(WIN32) || defined(_WIN32)
	Win32Application App((HINSTANCE)GetModuleHandle(NULL));
#elif defined(__linux__) || defined(__unix__)
	// Not implemented yet!
#endif

	using TestType = float;
	size_t uCount = 100000;
	std::vector<TestType*> Data;
	Data.reserve(uCount);

	auto work = [&]()
	{
		for (size_t i = 0; i < uCount; i++)
		{
			*Data[i] = (TestType)i;
		}

		for (size_t i = 0; i < uCount; i++)
		{
			*Data[i] *= *Data[uCount - i - 1];
		}
	};

	{
		hlx::StopWatch<> timer("reference");

		for (size_t i = 0; i < uCount; ++i)
		{
			Data.push_back(DefaultHeapAllocator<TestType>::Alloc());
		}

		work();

		for (TestType* pData : Data)
		{
			DefaultHeapAllocator<TestType>::Free(pData);
		}
	}

	Data.resize(0);

	{
		auto& Pool = SmallObjAllocator<TestType, false>::Instance(); // prealloc
		hlx::StopWatch<> timer("small obj non threadsafe");

		for (size_t i = 0; i < uCount; ++i)
		{
			Data.push_back(Pool.Alloc());
		}

		work();

		for (TestType* pData : Data)
		{
			Pool.Free(pData);
		}
	}

	Data.resize(0);

	{
		auto& Pool = SmallObjAllocator<TestType, true>::Instance(); // prealloc
		hlx::StopWatch<> timer("small obj threadsafe");

		for (size_t i = 0; i < uCount; ++i)
		{
			Data.push_back(Pool.Alloc());
		}

		work();

		for (TestType* pData : Data)
		{
			Pool.Free(pData);
		}
	}

	Data.resize(0);

	{
		hlx::StopWatch<> timer("big obj none threadsafe");

		for (size_t i = 0; i < uCount; ++i)
		{
			Data.push_back(BigObjAllocator<TestType, false, 1024u>::Alloc());
		}

		work();

		for (TestType* pData : Data)
		{
			BigObjAllocator<TestType, false, 1024u>::Free(pData);
		}
	}

	Data.resize(0);

	{
		hlx::StopWatch<> timer("big obj threadsafe");

		for (size_t i = 0; i < uCount; ++i)
		{
			Data.push_back(BigObjAllocator<TestType, true, 1024u>::Alloc());
		}

		work();

		for (TestType* pData : Data)
		{
			BigObjAllocator<TestType, true, 1024u>::Free(pData);
		}
	}

	Data.resize(0);

	if (App.Init(1280u, 720u, Tracy::EGraphicsAPI::eVulkan))
	{
		return App.Run();
	}

	return EXIT_FAILURE;
}