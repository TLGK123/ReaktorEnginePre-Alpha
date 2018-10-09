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

//������ǰĿ¼�µ��ļ��к��ļ�,Ĭ���ǰ���ĸ˳�����
bool TraverseFiles(string path, int &file_num) {
	_finddata_t file_info;
	string current_path = path + "/*.*";							//���Զ������ĺ�׺Ϊ*.exe��*.txt���������ض���׺���ļ���*.*��ͨ�����ƥ����������,·�����ӷ��������б��/���ɿ�ƽ̨    //���ļ����Ҿ��
	int handle = _findfirst(current_path.c_str(), &file_info);		//����ֵΪ-1�����ʧ��
	if (-1 == handle)
		return false;
	do {															//�ж��Ƿ���Ŀ¼
		string attribute;
		if (file_info.attrib == _A_SUBDIR)							//��Ŀ¼
			attribute = "dir";
		else
			attribute = "file";        //����ļ���Ϣ������,�ļ���(����׺)���ļ�����޸�ʱ�䡢�ļ��ֽ���(�ļ�����ʾ0)���ļ��Ƿ�Ŀ¼
		cout << file_info.name << ' ' << file_info.time_write << ' ' << file_info.size << ' ' << attribute << endl; //��õ�����޸�ʱ����time_t��ʽ�ĳ����ͣ���Ҫ����������ת������ʱ����ʾ
		file_num++;
	} while (!_findnext(handle, &file_info));  //����0�������    //�ر��ļ����
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