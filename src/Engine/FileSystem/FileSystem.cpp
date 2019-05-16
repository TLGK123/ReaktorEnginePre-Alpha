#include"filesystem.h"
#include<iostream>
using namespace std;
std::string FileSystem::getPath(std::string assetpath)
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
