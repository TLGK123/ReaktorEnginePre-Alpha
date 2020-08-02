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

#include <vector>

using namespace TmingEngine;
using namespace std;

int mainT()
{
	Pair* env = new Pair();
	LoadScheme(env, "E:\\WorkSpace\\Giteet\\TmingEngine\\Data\\EngineScript\\scheme.scm");

	Pair x1 = "CameraX";

	Pair* exp = new Pair("+");
	exp->car = new Pair("8");
	exp->cdr = new Pair("4");

	/* scheme
	(+ 8 3)
	*/
	//exp->Print();

	int d = *env->eval(exp, env);

	env->Print();
	Pair* var = new Pair("x", "4");
	env->ExtendEnv(var);
	env->Print();
	auto d1 = env->eval(new Pair("x"));
	auto d2 = env->eval(&x1, env);
	/* scheme
	(define x 3)
	*/

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

	Pair* funCall = new Pair(func, "8");

	Pair* result = env->eval(funCall, env);
	funCall->Print();
	/* scheme
		((lambda (x)(* x 7))3)
	*/

	int  s = *result;
	return 0;
	;
}