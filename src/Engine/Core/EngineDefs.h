#ifndef EngineDef
#define EngineDef
#ifdef COMPILING_LIB
#if WIN32
    #define ENGINE_CLASS __declspec(dllexport)
#else
    #define ENGINE_CLASS
#endif
#else
    #define ENGINE_CLASS
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

#endif
