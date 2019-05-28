
#include <iostream>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
#include <exception>

#if !__APPLE__
#include <stdio.h>
#include <direct.h>
#else
#include "iostream"
#include <unistd.h>
#endif

//#include <direct.h>

std::string getPath(std::string assetpath);


int main()
{
    std::cout << "Hello World! in c++  \n";
    // 打印当前路径

    MonoDomain *domain;

    auto s = getPath("Library/shared/TestDll.dll");
    const char *csharp_dll = s.c_str();
    try
    {
        // 初始化JIT
        domain = mono_jit_init("TestDll");
        // 加载程序集
        MonoAssembly *assembly = mono_domain_assembly_open(domain, csharp_dll);
        MonoImage *image = mono_assembly_get_image(assembly);
        // 获取MonoClass
        MonoClass *mono_class = mono_class_from_name(image, "TestDll", "Main");
        // 获取方法
        //MonoMethodDesc *method_desc = mono_method_desc_new("csharp.BindingTest:Main()", true);
        MonoMethodDesc *method_desc = mono_method_desc_new("TestDll.Main:SayHello()", true);
        MonoMethod *method = mono_method_desc_search_in_class(method_desc, mono_class);
        mono_method_desc_free(method_desc);
        
        // 调用方法
        mono_runtime_invoke(method, nullptr, nullptr, nullptr);
        // 释放JIT

        mono_jit_cleanup(domain);
    }
    catch (std::exception* e)
    {
        std::cout << e->what();
    }
}

typedef void (*CsharpFunction)(const char * data);

extern "C"
{
    void DoSomething ();
    void DoSomething2 (const char * messgae );
    const char * DoSomething3(const char * messgae);
    void DoSomething4 (CsharpFunction handle);
}



void DoSomething2 (const char * messgae )
{
    std::cout << " some message  哈哈 define in c# ! "<< messgae <<std::endl;
}


void DoSomething ()
{
    std::cout << " some function 哈哈 define in c++ ! "<<std::endl;
}


const char *  DoSomething3(const char * messgae )
{
    std::string msg(messgae);
    msg += " native data fom c++ ";
  
    return msg.c_str();
}

void DoSomething4 (CsharpFunction handle)
{
    handle("c++ data 123");
   
}

#define MAX_PATH 250

std::string getPath(std::string assetpath)
{
    char buffer[MAX_PATH];
    getcwd(buffer, MAX_PATH);
    std::string path = buffer;
    std::string name = "TmingEngine";
    int cutIndex = path.find(name);
    
    std::string  temp = path.substr(0, cutIndex + name.length());
    if (assetpath.length()>0)
    {
        path = temp + "/" + assetpath;
    }
    else
    {
        path = temp;
    }
    
    // std::cout<<"当前路径" <<path<<std::endl;
    // std::cout <<"AssetPath: "+ path << std::endl;
    return path;
}
