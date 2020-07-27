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

using namespace TmingEngine;
using namespace std;

void separateWords();
void readOneWorld();
void pushWordToSatck();
void isOnePairEnd();
void popWordsFromSatck();
void caculateOnePair();

int main()
{
	int size = sizeof(Pair);
	fstream file;
	char script[25];
	
	file.open("D:\\Github\\TmingEngine\\Data\\EngineScript\\scheme.scm", ios::in);//打开文件，供读
	if (!file)
	{
		cerr << "Open File Fail." << endl;
		exit(1);
	}
	string code = "";
	Pair* c = new Pair();
	Pair* head = c;
	while (!file.eof())
	{
		file >> script;
		code = string(script);
		if (code != "(" && code != ")" && code != "")
		{
			c->InitPair(code);			
		}
	}
	head->Print();

	Pair* env = new Pair();
	int sc = *env->eval(head, env);

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
	Pair* x1 = new Pair("x");
	Pair* v = env->eval(x1, env);

	/* scheme
	(define x 3)
	*/

	//局部变量求值
	Pair* let = new Pair("let");
	let->car = new Pair("w", "66");
	let->cdr = new Pair("*");
	let->cdr->car = new Pair("2");
	let->cdr->cdr = new Pair("w");

	//let->Print();
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
		(lambda (x)(* x 7))
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