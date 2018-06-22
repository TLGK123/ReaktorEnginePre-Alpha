#include<iostream>

#if !__APPLE__
#include <stdio.h>
#include <direct.h>
#else
#include "iostream"
#include <unistd.h>
#endif

#define MAX_PATH 250

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
    getcwd(buffer, MAX_PATH);
    std::string path = buffer;
    std::string name ="TmingEngine";
    int cutIndex = path.find(name);
    
    std::string  temp = path.substr(0,cutIndex+name.length())+"/";
    path = temp;
    ;
    path =path+assetpath;
    std::cout<<"当前路径"<<path<<std::endl;
    
    std::cout <<"AssetPath: "+ path << std::endl;
    return path;
       
}

