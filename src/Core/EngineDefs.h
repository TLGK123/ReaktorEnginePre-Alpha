#pragma once

#define COMPILING_LIB 1

#ifdef COMPILING_LIB
#define ENGINE_CLASS __declspec(dllexport)
#else
#define ENGINE_CLASS __declspec(dllimport)
#endif

namespace TmingEngine
{
	template <typename T>
	void SafeRelease(T& ptr)
	{
		if (ptr)
		{
			ptr->Release();
			ptr = nullptr;
		}
	}

	template <typename T>
	void SafeDelete(T& ptr)
	{
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}

}