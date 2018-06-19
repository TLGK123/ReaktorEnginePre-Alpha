#include<iostream>

#if !__APPLE__
#include<direct.h>
#else
#define MAX_PATH _PC_PATH_MAX
#include <unistd.h>
#endif
//unistd.h（windows下为direct.h）

#ifdef _DEBUG  

#else  
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址
#endif

static class FileSystem
{
public:
	static std::string getPath(std::string assetpath);

private:

};

std::string FileSystem::getPath(std::string assetpath)
{
    char buffer[MAX_PATH];
   // getcwd(buffer, MAX_PATH);
    std::string path = buffer;
    path = "/Users/blue/Desktop/Gitee/TmingEngine/" + assetpath;
    ;
    std::cout <<"AssetPath: "+ path << std::endl;
    return path;
       
}

