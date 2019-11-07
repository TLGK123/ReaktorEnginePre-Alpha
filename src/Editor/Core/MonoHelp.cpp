//The MIT License
//
//Copyright(c) 2016 - 2019 littleblue
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//copies of the Software, and to permit persons to whom the Software is furnished
//to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
//COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

//
#include "MonoHelp.h"

typedef void (*CsharpFunction)(const char* data);

class Point
{
public:
	int x;
	int y;
	int z;
	~Point()
	{

	}
};

extern "C"
{
	EXPORT_API void DoSomething();
	EXPORT_API void DoSomething2(const char* messgae);
	EXPORT_API const char* DoSomething3(const char* messgae);
	EXPORT_API void DoSomething4(CsharpFunction handle);
	EXPORT_API void DoWithClass(Point p);
}

void DoSomething2(const char* messgae)
{
	std::string ss = std::string(messgae);
	std::cout << " some message  哈哈 define in c# ! " << ss << std::endl;
}

void DoSomething()
{
	std::cout << " some function 哈哈 define in c++ ! " << std::endl;
}

const char* DoSomething3(const char* messgae)
{
	std::string msg(messgae);

	msg += " native data fom c++ ";

	return msg.c_str();
}

void DoWithClass(Point p)
{
	std::cout << " Pass C# class to c++ ! " << "x: " << p.x << " y: " << p.y << " z: " << p.z << std::endl;
}

void DoSomething4(CsharpFunction handle)
{
	std::string cn = std::string("c++ Data 123 ");
	auto s = cn.c_str();
	handle(s);

}

MonoDomain* domain;
int TmingEngine::MonoHelp::Run(std::string path)
{
	std::cout << "Hello World! in c++  \n";
	// 打印当前路径

	//auto s = getPath("DLLProject/bin/Debug/CSharpDLL.dll");
	//std::string s = "D:/Gitee/CppProject/MonoRun/DLLProject/bin/Debug";
	const char* csharp_dll = path.c_str();
	try
	{
		// 初始化JIT
		domain = mono_jit_init("TestDll");
		// 加载程序集
		MonoAssembly* assembly = mono_domain_assembly_open(domain, csharp_dll);
		MonoImage* image = mono_assembly_get_image(assembly);
		// 获取MonoClass
		MonoClass* mono_class = mono_class_from_name(image, "TestDll", "Main");
		// 获取方法
		MonoMethodDesc* method_desc = mono_method_desc_new("TestDll.Main:SayHello()", true);
		MonoMethod* method = mono_method_desc_search_in_class(method_desc, mono_class);
		mono_method_desc_free(method_desc);

		// 调用方法
		mono_runtime_invoke(method, nullptr, nullptr, nullptr);
		// 释放JIT

		mono_jit_cleanup(domain);
	}
	catch (std::exception * e)
	{
		std::cout << e->what();
	}

	return 0;
}
