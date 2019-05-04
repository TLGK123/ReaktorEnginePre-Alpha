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


void TextRead_CPPmode(string s)
{
	fstream f;
	f.open(s, ios::in);
	vector<int> index;
	vector<double> x_pos;
	vector<double> y_pos;
	if (!f)
	{
        cout << " ### 12312312 ####  " << endl;
		return;
	}

	int mode = 2;
	//cin >> mode;
	if (1 == mode)
	{

		char ch;
		while (EOF != (ch = f.get()))
			cout << ch;
	}
	else if (2 == mode)
	{

		char line[128];
		int numBytes;
		f.seekg(0, 0);
		long totalByte = 0;
		while (!f.eof())
		{
			f.getline(line, 128);
			numBytes = f.gcount();
			totalByte += numBytes;
			cout << line << "\t" << numBytes << " tttttt " << endl;
		}
		cout << " hahaha " << totalByte << " hello Ú" << endl;
	}
	else if (3 == mode)
	{
		//Èç¹ûÖªµÀÊý¾Ý¸ñÊ½£¬¿ÉÒÔÖ±½ÓÓÃ>>¶ÁÈë
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
		cout << "´ò¿ªÎÄ¼þ³ö´í" << endl;
		return 0;
	}
	long totalByte = 0;
	//°´×Ö½Ú¶ÁÈë²¢Êä³ö
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
