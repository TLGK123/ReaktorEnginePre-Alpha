/*
			This file is part of:
				TmingEngine
			https://github.com/xiaomingfun/TmingEngine

   Copyright 2018 - 2020 TmingEngine

   File creator: littleblue

   TmingEngine is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

#include "scheme.hpp"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>

using namespace TmingEngine;
using namespace std;

Pair* env = new Pair();
stack<string> codeStack;
stack<Pair*> pairStack;
//queue<string> codeQueue;

void SeparateWords();
void ReadOneWord(string code);
void PushWordToStack(string word);
bool IsOnePairEnd(string word);
void PopWordFromStack();
void CaculateOnePair(Pair* p);

int main()
{
	int size = sizeof(Pair);
	
	SeparateWords();
	Pair x1 = "CameraX";
	Pair* v = env->eval(&x1, env);
	//s-表达式嵌套
	Pair* exp = new Pair("+");
	exp->car = new Pair("8");
	exp->cdr = new Pair("4");

	/* scheme
	(+ 8 3)
	*/
	//exp->Print();

	int d = *env->eval(exp, env);

	//变量存储在环境中

	Pair* var = new Pair("x", "4");
	env = env->ExtendEnv(var, env);


	/* scheme
	(define x 3)
	*/

	//局部变量求值
	Pair* let = new Pair("let");
	let->car = new Pair("w", "66");
	let->cdr = new Pair("*");
	let->cdr->car = new Pair("2");
	let->cdr->cdr = new Pair("w");

	let->Print();
	;

	Pair* rest = env->eval(let, env);

	/* scheme
		(let ((w 66))
				(* (w 2)))
	*/

	//把函数定义和当时的环境打包在一起，就是闭包
	Pair* function = new Pair("lambda");
	function->car = new Pair("x");
	function->cdr = new Pair("*");
	function->cdr->car = new Pair("x");
	function->cdr->cdr = new Pair("7");

	Pair* func = env->eval(function, env);

	//func->Print();
	/* scheme
		(lambda (x) (* x 7))
	*/

	//函数调用

	Pair* funCall = new Pair(func, "8");

	Pair* result = env->eval(funCall, env);
	funCall->Print();
	/* scheme
		((lambda (x)(* x 7))3)
	*/

	int  s = *result;
	;
}

void SeparateWords()
{
	fstream file;
	char script[64];

	file.open("D:\\Github\\TmingEngine\\Data\\EngineScript\\scheme.scm", ios::in);//打开文件，供读
	if (!file)
	{
		cerr << "Open File Fail." << endl;
		exit(1);
	}
	string code = "";

	while (!file.eof())
	{
		file >> script;
		code = string(script);
		ReadOneWord(code);
	}

	int i = 1;
}

void ReadOneWord(string code)
{
	if (code[0] == '(')
	{
		PushWordToStack("(");
		code = code.substr(1, code.size() - 1);
		ReadOneWord(code);
	}
	else if (code[code.size() - 1] == ')')
	{
		code = code.substr(0, code.size() - 1);
		ReadOneWord(code);
		PushWordToStack(")");
	}
	else
	{
		PushWordToStack(code);
	}
}

void PushWordToStack(string word)
{
	codeStack.push(word);

	if (IsOnePairEnd(word))
	{
		PopWordFromStack();
	}
	else
	{

	}
}

bool IsOnePairEnd(string word)
{
	return word == ")";
}

void PopWordFromStack()
{
	string stackData = "";
	Pair* p = new Pair();
	p->Type = CellType::pair;
	Pair* head = p;
	int point = 1;
	vector<string> codes;
	while (stackData != "(" && codeStack.size() > 0)
	{		
		stackData = codeStack.top();
		codeStack.pop();
		if (stackData != "(" && stackData != ")")
		{
			codes.push_back(stackData);
		}
		std::cout << " Stack:===> " << stackData << std::endl;
	}

	if (codes.size() == 1)
	{
		p->SetData(codes[0]);
	}
	else if (codes.size() == 2)
	{
		p->car = new Pair(codes[1]);
		p->cdr = new Pair(codes[0]);
	}
	else if (codes.size() == 3)
	{
		p->cdr = new Pair(codes[0]);
		p->car = new Pair(codes[1]);
		p->SetData(codes[2]);
	}

	CaculateOnePair(p);
}

void CaculateOnePair(Pair* p)
{
	pairStack.push(p);

	std::cout << "code size: " << codeStack.size() << std::endl;
	if (codeStack.size() == 0)
	{
		Pair* p1, * p2, * p3;
		Pair* result;
		if (pairStack.size() == 3)
		{
			p1 = pairStack.top();
			pairStack.pop();
			p3 = pairStack.top();
			pairStack.pop();
			p2 = pairStack.top();
			pairStack.pop();

			p1->car = p2;
			p1->cdr = p3;

			p1->Print();

			result = env->eval(p1, env);			
		}
		else if (pairStack.size() == 1)
		{
			result = env->eval(p, env);
		}
		
		int u = 0;
	}

}