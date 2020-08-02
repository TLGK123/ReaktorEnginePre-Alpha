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

	void ReadOneWord(Pair* env, string code);
	void PushWordToStack(Pair* env, string word);
	bool IsOnePairEnd(string word);
	void PopWordFromStack(Pair* env);
	void CaculateOnePair(Pair* env, Pair* p);

	stack<Pair*> codeStack;
	stack<Pair*> pairStack;

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
						return new Pair();
					}
				}
				else
				{
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
				env = ExtendEnv(exp->car, env); //
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
				auto c1 = exp->car;//eval(exp->car, env);
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
			auto v1 = eval(exp->car, env);		//
			auto v2 = eval(exp->cdr, env);		//
			auto that_env = v1->cdr;			//
			auto funcp = v1->car->car;			//
			auto nv = new Pair(funcp, v2);		//
			that_env = ExtendEnv(nv, that_env); //
			auto func = v1->car->cdr;			//
			auto v3 = eval(func, that_env);		//
			return v3;
		}

		return nullptr;
	}

	void LoadScheme(Pair* env, string path)
	{
		fstream file;
		char script[64];

		file.open(path, ios::in);
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
			ReadOneWord(env, code);
		}
	}

	void ReadOneWord(Pair* env, string code)
	{
		if (code[0] == '(')
		{
			PushWordToStack(env, "(");
			code = code.substr(1, code.size() - 1);
			ReadOneWord(env, code);
		}
		else if (code[code.size() - 1] == ')')
		{
			code = code.substr(0, code.size() - 1);
			ReadOneWord(env, code);
			PushWordToStack(env, ")");
		}
		else
		{
			PushWordToStack(env, code);
		}
	}

	void PushWordToStack(Pair* env, string word)
	{
		codeStack.push(new Pair(word));

		if (IsOnePairEnd(word))
		{
			PopWordFromStack(env);
		}
		else
		{
		}
	}

	bool IsOnePairEnd(string word)
	{
		return word == ")";
	}

	void PopWordFromStack(Pair* env)
	{
		Pair* stackData = new Pair();
		Pair* p = new Pair();
		p->Type = CellType::pair;
		Pair* head = p;
		int point = 1;
		vector<Pair*> codes;
		while (stackData->Data != "(" && codeStack.size() > 0)
		{
			stackData = codeStack.top();
			codeStack.pop();
			if (stackData->Data != "(" && stackData->Data != ")")
			{
				codes.push_back(stackData);
			}
			//std::cout << " Stack:===> " << stackData->Data << std::endl;
		}

		if (codes.size() == 1)
		{
			p->SetData(codes[0]->Data);
		}
		else if (codes.size() == 2)
		{
			p->car = codes[1];
			p->cdr = codes[0];
		}
		else if (codes.size() == 3)
		{
			p->cdr = codes[0];
			p->car = codes[1];
			p->SetData(codes[2]->Data);
		}

		CaculateOnePair(env, p);
	}

	void CaculateOnePair(Pair* env, Pair* p)
	{
		pairStack.push(p);

		//std::cout << "code size: " << codeStack.size() << std::endl;
		if (codeStack.size() == 0)
		{
			Pair* p1, * p2, * p3;
			Pair* result = nullptr;
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

				result = env->eval(p1);
			}
			else if (pairStack.size() == 1)
			{
				p1 = pairStack.top();
				pairStack.pop();

				result = env->eval(p1);
			}
			else if (pairStack.size() == 2)
			{
				p1 = pairStack.top();
				pairStack.pop();
				p2 = pairStack.top();
				pairStack.pop();
				p3 = new Pair(p2, p1);
				result = env->eval(p3, env);
			}

			int u = 0;
		}
	}
}