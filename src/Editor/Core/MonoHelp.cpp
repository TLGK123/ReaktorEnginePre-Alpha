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
//  Selection.hpp
//  Editor
//
//  Created by lillteblue on 2019/11/5.
//
#include "MonoHelp.h"

int TmingEngine::MonoHelp::Run(std::string path)
{
	std::cout << "Hello World! in c++  \n";
	// 打印当前路径

	MonoDomain* domain;

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
		//MonoMethodDesc *method_desc = mono_method_desc_new("csharp.BindingTest:Main()", true);
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
