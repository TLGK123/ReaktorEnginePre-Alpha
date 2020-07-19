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

#ifndef TmingEngine_ScriptEnginee_scheme_h
#define TmingEngine_ScriptEnginee_scheme_h

#include<vector>
#include<string>

using namespace std;

namespace TmingEngine
{
	enum class CellType
	{
		Atom, // 原子为标识符形式的符号或数字的字面值   如果是原子，或者空表 返回t ，否则就返回 f
		Quote, // 引用，用来表示数据 ，避免被求值
		Operater, // 算术操作符
		Lambda, // 匿名函数
		Number, // 整数
		Bool,  // 布尔
		Syntax, // 语法关键词
		Nil, // 空序对
		pair, // 序对
		Symbol, // 符号
		Closure, // 闭包
	};

	class Pair
	{
	public:

		string Data;
		Pair* car;
		Pair* cdr;
		CellType Type;

		Pair()
		{
			Type = CellType::Nil;
			car = this;
			cdr = nullptr;
		}

		Pair(Pair* _car, Pair* _cdr)
		{
			car = _car;
			Data = _car->Data;
			Type = _car->Type;

			cdr = _cdr;
		}

		operator bool()
		{
			return Data == "#t";
		}

		operator int()
		{
			int val = std::stoi(Data, nullptr, 0);
			return val;
		}

		Pair(bool x)
		{
			Data = x ? "#t" : "#f";
			Type = CellType::Atom;
			car = this;
			cdr = nullptr;
		}

		Pair(int x)
		{
			Data = std::to_string(x);
			car = this;
			cdr = nullptr;
			Type = CellType::Number;
		}

		operator string()
		{
			return Data;
		}

		void InitPair(string x);

		Pair(const char* x)
		{
			string data = string(x);
			InitPair(data);
		}

		Pair(string x)
		{
			InitPair(x);
		}

		bool operator ==(const Pair& other) const
		{
			if (this->Data != other.Data)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		bool operator  !=(const Pair& other)const
		{
			if (this->Data != other.Data)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		Pair* eval(Pair* exp, Pair* env);

		Pair* CaculateOperate(Pair* exp, Pair* env);

		Pair* Cons(Pair* p1, Pair* p2)
		{
			return new Pair(p1, p2);
		}

		Pair* ExtendEnv(Pair* p1, Pair* _env)
		{
			return Cons(p1, _env);
		}

		Pair* LookUp(Pair* p1, Pair* _env);

		Pair* CaculateSymbol(Pair* exp, Pair* _env);

		Pair* CaculateSyntax(Pair* exp, Pair* env);

		Pair* CaculateLambda(Pair* exp, Pair* env);

		Pair* Pair::CaculateFucntionCall(Pair* exp, Pair* env);

		Pair* GetValueInEnv(Pair* var, Pair* env)
		{
			Pair* v;
			v = env->car;
			if (v->car == var)
			{
				return v->cdr;
			}
			else
			{
				return GetValueInEnv(var, v->cdr);
			}
		}

		void SetValueInEnv(Pair* var, Pair* env)
		{
			Pair* v = GetValueInEnv(var, env);
			if (v != nullptr)
			{
				v = var;
			}
			else
			{
				Pair* next;
				while ((next = env->cdr) != nullptr)
				{
					env = next;
				}

				env->cdr = var;
			}
		}
	};
}

#endif