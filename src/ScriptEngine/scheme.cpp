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
namespace TmingEngine
{
	extern  vector<string> Syntaxs = { "car", "cdr", "cons", "atom", "quote", "cond", "let", "lambda", "'", "if","define" };
	extern  vector<string> Operates = { "+", "-", "*", "/", "%", "=" };
	extern  vector<string> BoolSymbol = { "#f", "#t" };
	
	Pair* Pair::CaculateOperate(Pair* exp, Pair* env)
	{
		Pair* nextCell;
		int detaValue = 0;
		int v1, v2;
		string d = exp->Data;
		if (d == "+")
		{
			nextCell = exp;
			auto ev1 = eval(nextCell->car, env);
			auto ev2 = eval(nextCell->cdr, env);
			if (ev1->Type == CellType::Number && ev2->Type == CellType::Number)
			{
				v1 = *ev1;
				v2 = *ev2;
				return new Pair(v1 + v2);
			}
			else
			{
				return exp;
			}
		}
		else if (d == "-")
		{
			nextCell = exp;
			auto ev1 = eval(nextCell->car, env);
			auto ev2 = eval(nextCell->cdr, env);
			if (ev1->Type == CellType::Number && ev2->Type == CellType::Number)
			{
				v1 = *ev1;
				v2 = *ev2;
				return new Pair(v1 - v2);
			}
			else
			{
				return exp;
			}
		}
		else if (d == "*")
		{
			nextCell = exp;
			auto ev1 = eval(nextCell->car, env);
			auto ev2 = eval(nextCell->cdr, env);
			if (ev1->Type == CellType::Number && ev2->Type == CellType::Number)
			{
				v1 = *ev1;
				v2 = *ev2;
				return new Pair(v1 * v2);
			}
			else
			{
				return exp;
			}
		}
		else if (d == "/")
		{
			nextCell = exp;
			auto ev1 = eval(nextCell->car, env);
			auto ev2 = eval(nextCell->cdr, env);
			if (ev1->Type == CellType::Number && ev2->Type == CellType::Number)
			{
				v1 = *ev1;
				v2 = *ev2;
				return new Pair(v1 / v2);
			}
			else
			{
				return exp;
			}
		}
		else if (d == "==")
		{
			nextCell = exp;
			auto ev1 = eval(nextCell->car, env);
			auto ev2 = eval(nextCell->cdr, env);
			if (ev1->Type == CellType::Number && ev2->Type == CellType::Number)
			{
				v1 = *ev1;
				v2 = *ev2;
				return new Pair(v1 == v2);
			}
			else
			{
				return exp;
			}
		}

		return new Pair();
	}

	void Pair::InitPair(string x)
	{
		Data = x;
		car = nullptr;
		cdr = nullptr;
		AutoSetType();
	}

	void Pair::AutoSetType()
	{
		string x = Data;
		if (x == "0")
		{
			Type = CellType::Number;
			return;
		}
		else
		{
			int a = atoi(x.c_str());
			if (a != 0)
			{
				Type = CellType::Number;
				return;
			}
		}

		vector<std::string>::iterator iter;
		for (iter = Syntaxs.begin(); iter != Syntaxs.end(); iter++)
		{
			if (*iter == x)
			{
				if (x == "lambda")
				{
					Type = CellType::Lambda;
					return;
				}
				else if (x == "quote" || x == "'")
				{
					Type = CellType::Quote;
					return;
				}
				else
				{
					Type = CellType::Syntax;
					return;
				}
			}
		}

		for (iter = Operates.begin(); iter != Operates.end(); iter++)
		{
			if (*iter == x)
			{
				Type = CellType::Operater;
				return;
			}
		}

		for (iter = BoolSymbol.begin(); iter != BoolSymbol.end(); iter++)
		{
			if (*iter == x)
			{
				Type = CellType::Atom;
				return;
			}
		}

		Type = CellType::Symbol;
	}

	Pair* Pair::eval(Pair* exp)
	{
		return	eval(exp, this);
	}

	Pair* Pair::eval(Pair* exp, Pair* env)
	{
		switch (exp->Type)
		{
		case CellType::Number:
			return exp;

		case CellType::Quote:
			return CaculateQuote(exp);

		case CellType::Operater:
			return CaculateOperate(exp, env);

		case CellType::Atom:
			return exp;

		case CellType::Symbol:
			return CaculateSymbol(exp, env);

		case CellType::Syntax:
			return CaculateSyntax(exp, env);

		case CellType::Lambda:
			return CaculateLambda(exp, env);

		case CellType::FunctionCall:
			return CaculateFucntionCall(exp, env);

		default:
			return exp;
		}

		return new Pair();
	}

	Pair* Pair::LookUp(Pair* p1, Pair* _env)

	{
		Pair* temp = _env->car;

		if (temp == nullptr || temp->Type == CellType::Nil)
		{
			//Debug::Log("δ�������: " + p1);
			return new Pair();
		}

		if (temp->car != nullptr)
		{
			if (*(temp->car) != *(p1))
			{
				Pair* _next = _env->cdr;
				if (_next != nullptr)
				{
					if (_next->Type != CellType::Nil)
					{
						return LookUp(p1, _next);
					}
					else
					{
						//Debug.Log("δ�������: " + p1);
						return new Pair();
					}
				}
				else
				{
					//Debug.Log("δ�������: " + p1);
					return new Pair();
				}
			}
			else
			{
				return temp->cdr;
			}
		}
		else if (temp->cdr != nullptr)
		{
			return LookUp(p1, temp->cdr);
		}
	}

	Pair* Pair::CaculateSymbol(Pair* exp, Pair* _env)
	{
		if (_env == nullptr || _env->Type == CellType::Nil)
		{
			//Debug.Log("δ�������: " + exp);
			return exp;
		}

		return LookUp(exp, _env);
	}

	Pair* Pair::CaculateQuote(Pair* exp)
	{
		auto p = new Pair();
		p->Data = exp->Data;
		p->Type = CellType::Symbol;
		return p;
	}

	Pair* Pair::CaculateSyntax(Pair* exp, Pair* env)
	{
		if (exp->Type == CellType::Syntax)
		{
			if (exp->Data == "let")
			{
				env = ExtendEnv(exp->car, env); //  ��Ҫ�󶨵ı���
				return eval(exp->cdr, env);
			}
			else if (exp->Data == "if")
			{
				auto cond = eval(exp->cdr->car, env);
				if (cond)
				{
					return eval(exp->cdr->cdr, env);
				}
				else
				{
					return nullptr;
				}
			}
			else if (exp->Data == "define")
			{
				auto c1 = eval(exp->car, env);
				auto c2 = eval(exp->cdr, env);
				auto var = new Pair(c1, c2);
				env->ExtendEnv(var);
				return env;
			}
			else
			{
				return nullptr;
			}
		}

		return nullptr;
	}

	Pair* Pair::CaculateLambda(Pair* exp, Pair* env)
	{
		if (exp->Type == CellType::Lambda)
		{
			Pair* clouse = new Pair(exp, env);
			clouse->Type = CellType::Closure;
			return clouse;
		}

		return nullptr;
	}

	Pair* Pair::CaculateFucntionCall(Pair* exp, Pair* env)
	{
		if (exp->Type == CellType::FunctionCall)
		{
			auto v1 = eval(exp->car, env); // ����������հ�
			auto v2 = eval(exp->cdr, env); // �����������ֵ
			auto that_env = v1->cdr; // ��ȡ��������ʱ�Ļ���
			auto funcp = v1->car->car; // ��ȡ��������ʱ������������
			auto nv = new Pair(funcp, v2);
			that_env = ExtendEnv(nv, that_env); // �Ѳ�����չ����ʱ����Ļ�����ȥ
			auto func = v1->car->cdr; //������
			auto v3 = eval(func, that_env);
			return v3;
		}

		return nullptr;
	}
}