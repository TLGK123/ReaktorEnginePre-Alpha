#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<sstream>
#ifdef __APPLE__
#include <sys/uio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <io.h>
#endif

#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <string>

#include "FileReader.hpp"

using namespace std;

//int main(int argc, char const *argv[])
//{
//	//TextRead_CPPmode("D:\\Gitee\\TmingEngine\\src\\Tools\\FileReader\\Data\\1.txt");
//	int todayWork = FileCharacter("D:\\Gitee\\TmingEngine\\src\\Tools\\FileReader\\Data\\1.txt");
//	cout << "今天写的代码量:" << todayWork << " 字节"<< endl;
//	return 0;
//}

//采用CPP模式读取txt
void TextRead_CPPmode(string s)
{
	fstream f;
	f.open(s, ios::in);
	//文件打开方式选项：
	//　ios::in　　　　= 0x01,　//供读，文件不存在则创建(ifstream默认的打开方式)
	//　ios::out　　　 = 0x02,　//供写，文件不存在则创建，若文件已存在则清空原内容(ofstream默认的打开方式)
	//　ios::ate　　　 = 0x04,　//文件打开时，指针在文件最后。可改变指针的位置，常和in、out联合使用
	//　ios::app　　　 = 0x08,　//供写，文件不存在则创建，若文件已存在则在原文件内容后写入新的内容，指针位置总在最后
	//　ios::trunc　　 = 0x10,　//在读写前先将文件长度截断为0（默认）
	//　ios::nocreate　= 0x20,　//文件不存在时产生错误，常和in或app联合使用
	//　ios::noreplace = 0x40,　//文件存在时产生错误，常和out联合使用
	//　ios::binary　　= 0x80　 //二进制格式文件
	vector<int> index;
	vector<double> x_pos;
	vector<double> y_pos;
	if (!f)
	{
		cout << "打开文件出错" << endl;
		return;
	}
	//cout << "mode为1，按字符读入并输出；mode为2，按行读入输出；mode为3，知道数据格式，按行读入并输出" << endl;
	int mode = 2;
	//cin >> mode;
	if (1 == mode)
	{
		//按字节读入并输出
		char ch;
		while (EOF != (ch = f.get()))
			cout << ch;
	}
	else if (2 == mode)
	{
		//按行读取，并显示
		char line[128];
		int numBytes;
		f.seekg(0, 0);			  //跳过字节
		//seekg(绝对位置);　　　　　 //绝对移动
		//seekg(相对位置,参照位置);　//相对操作
		//tellg();			     //返回当前指针位置

		long totalByte = 0;
		while (!f.eof())
		{
			//使用eof()函数检测文件是否读结束
			f.getline(line, 128);
			numBytes = f.gcount();		//使用gcount()获得实际读取的字节数
			totalByte += numBytes;
			cout << line << "\t" << numBytes << "字节" << endl;
		}
		cout << "文件总字节数：\t" << totalByte << "字节" << endl;
	}
	else if (3 == mode)
	{
		//如果知道数据格式，可以直接用>>读入
		int index_temp = 0;
		double x_pos_temp = 0, y_pos_temp = 0;
		while (!f.eof())
		{
			f >> index_temp >> x_pos_temp >> y_pos_temp;
			index.push_back(index_temp);
			x_pos.push_back(x_pos_temp);
			y_pos.push_back(y_pos_temp);
			cout << index_temp << "\t" << x_pos_temp << "\t" << y_pos_temp << endl;
		}
	}
	f.close();
}

long FileCharacter(string s)
{
	fstream f;
	f.open(s, ios::in);
	vector<int> index;
	vector<double> x_pos;
	vector<double> y_pos;
	if (!f)
	{
		cout << "打开文件出错" << endl;
		return 0;
	}
	long totalByte = 0;
	//按字节读入并输出
	char ch;
	while (EOF != (ch = f.get()))
	{
		//cout << ch;
		if (ch == '\n')
			totalByte++;
	}

	f.close();
	return totalByte;
}

vector<string> GetFileContent(string f)
{
	vector<string> content;
	ifstream fin(f);
	string  s;
	while (getline(fin, s))
	{
		content.push_back(s);
	}
	fin.close();
	return content;
}