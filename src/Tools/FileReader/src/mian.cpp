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
//	cout << "����д�Ĵ�����:" << todayWork << " �ֽ�"<< endl;
//	return 0;
//}

//����CPPģʽ��ȡtxt
void TextRead_CPPmode(string s)
{
	fstream f;
	f.open(s, ios::in);
	//�ļ��򿪷�ʽѡ�
	//��ios::in��������= 0x01,��//�������ļ��������򴴽�(ifstreamĬ�ϵĴ򿪷�ʽ)
	//��ios::out������ = 0x02,��//��д���ļ��������򴴽������ļ��Ѵ��������ԭ����(ofstreamĬ�ϵĴ򿪷�ʽ)
	//��ios::ate������ = 0x04,��//�ļ���ʱ��ָ�����ļ���󡣿ɸı�ָ���λ�ã�����in��out����ʹ��
	//��ios::app������ = 0x08,��//��д���ļ��������򴴽������ļ��Ѵ�������ԭ�ļ����ݺ�д���µ����ݣ�ָ��λ���������
	//��ios::trunc���� = 0x10,��//�ڶ�дǰ�Ƚ��ļ����Ƚض�Ϊ0��Ĭ�ϣ�
	//��ios::nocreate��= 0x20,��//�ļ�������ʱ�������󣬳���in��app����ʹ��
	//��ios::noreplace = 0x40,��//�ļ�����ʱ�������󣬳���out����ʹ��
	//��ios::binary����= 0x80�� //�����Ƹ�ʽ�ļ�
	vector<int> index;
	vector<double> x_pos;
	vector<double> y_pos;
	if (!f)
	{
		cout << "���ļ�����" << endl;
		return;
	}
	//cout << "modeΪ1�����ַ����벢�����modeΪ2�����ж��������modeΪ3��֪�����ݸ�ʽ�����ж��벢���" << endl;
	int mode = 2;
	//cin >> mode;
	if (1 == mode)
	{
		//���ֽڶ��벢���
		char ch;
		while (EOF != (ch = f.get()))
			cout << ch;
	}
	else if (2 == mode)
	{
		//���ж�ȡ������ʾ
		char line[128];
		int numBytes;
		f.seekg(0, 0);			  //�����ֽ�
		//seekg(����λ��);���������� //�����ƶ�
		//seekg(���λ��,����λ��);��//��Բ���
		//tellg();			     //���ص�ǰָ��λ��

		long totalByte = 0;
		while (!f.eof())
		{
			//ʹ��eof()��������ļ��Ƿ������
			f.getline(line, 128);
			numBytes = f.gcount();		//ʹ��gcount()���ʵ�ʶ�ȡ���ֽ���
			totalByte += numBytes;
			cout << line << "\t" << numBytes << "�ֽ�" << endl;
		}
		cout << "�ļ����ֽ�����\t" << totalByte << "�ֽ�" << endl;
	}
	else if (3 == mode)
	{
		//���֪�����ݸ�ʽ������ֱ����>>����
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
		cout << "���ļ�����" << endl;
		return 0;
	}
	long totalByte = 0;
	//���ֽڶ��벢���
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