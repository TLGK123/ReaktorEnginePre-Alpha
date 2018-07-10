#include<iostream>

#if !__APPLE__
#include <stdio.h>
#include <direct.h>
#else
#include "iostream"
#include <unistd.h>
#endif

#define MAX_PATH 250


static class FileSystem
{
public:
	static std::string getPath(std::string assetpath);

private:

};
