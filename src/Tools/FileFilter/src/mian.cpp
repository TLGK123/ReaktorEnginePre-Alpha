#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<sstream>
#include <io.h>

using namespace std;

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

//遍历当前目录下的文件夹和文件,默认是按字母顺序遍历
bool TraverseFiles(string path, int &file_num) {
	_finddata_t file_info;
	string current_path = path + "/*.*";							//可以定义后面的后缀为*.exe，*.txt等来查找特定后缀的文件，*.*是通配符，匹配所有类型,路径连接符最好是左斜杠/，可跨平台    //打开文件查找句柄
	int handle = _findfirst(current_path.c_str(), &file_info);		//返回值为-1则查找失败
	if (-1 == handle)
		return false;
	do {															//判断是否子目录
		string attribute;
		if (file_info.attrib == _A_SUBDIR)							//是目录
			attribute = "dir";
		else
			attribute = "file";        //输出文件信息并计数,文件名(带后缀)、文件最后修改时间、文件字节数(文件夹显示0)、文件是否目录
		cout << file_info.name << ' ' << file_info.time_write << ' ' << file_info.size << ' ' << attribute << endl; //获得的最后修改时间是time_t格式的长整型，需要用其他方法转成正常时间显示
		file_num++;
	} while (!_findnext(handle, &file_info));  //返回0则遍历完    //关闭文件句柄
	_findclose(handle);
	return true;
}

int main(int argc, char const *argv[])
{
	map<string, string> commands;
	vector<string> filters;
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-')
		{
			commands.insert(pair<string, string>(argv[i], argv[i + 1]));
		}
	}
	filters = split(commands["-f"], ' ');
	int c;
	TraverseFiles(commands["-p"], c);
	//cout << "Path " << commands["-p"] << endl;
	//cout << "filter " << commands["-f"] << endl;
	;
	return 0;
}