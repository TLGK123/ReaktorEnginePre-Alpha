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

using namespace TmingEngine;
using namespace std;

int main()
{
	fstream file;
	char script[25];
	file.open("E:\\WorkSpace\\Giteet\\TmingEngine\\Data\\EngineScript\\scheme.scm", ios::in);//打开文件，供读
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
			c->cdr = new Pair(code);
			c = c->cdr;
		}
	}

	Pair* env = new Pair();

	//s-表达式嵌套
	Pair* exp = new Pair("+");
	exp->cdr = new Pair(new Pair(8), new Pair(3));
	/* scheme
	(+ 8 3)
	*/

	int d = *env->eval(head->cdr, env);

	//变量存储在环境中

	Pair* x = new Pair(new Pair("x"), new Pair(1));
	env = env->ExtendEnv(x, env);
	Pair* x1 = new Pair("x");
	Pair* v = env->eval(x1, env);

	/* scheme
	(define x 3)
	*/

	//局部变量求值
	Pair* let = new Pair("let");
	let->cdr = new Pair(new Pair(new Pair("w"), new Pair(66))
		, new Pair(new Pair("*"),
			new Pair(new Pair("w"), new Pair(2))));

	Pair* ll = env->eval(let, env);

	/* scheme
		(let ((w 66))
				(* (w 2)))
	*/

	//把函数定义和当时的环境打包在一起，就是闭包
	Pair* function = new Pair("lambda");
	Pair* f = new Pair("*");
	f->cdr = new Pair(new Pair("x"), new Pair(7));
	function->cdr = new Pair(new Pair("x"), f);

	Pair* func = env->eval(function, env);

	/* scheme
		(lambda (x)(* x 7))
	*/

	//函数调用

	Pair* funCall = new Pair(func, new Pair(3));

	Pair* result = env->eval(funCall, env);

	/* scheme
		((lambda (x)(* x 7))3)
	*/

	int  s = *result;
	;
}