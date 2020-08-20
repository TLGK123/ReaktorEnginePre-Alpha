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

#ifndef SmartPtr_H
#define SmartPtr_H
#include <iostream>

namespace TmingEngine
{
	template <typename T>
	class GlobalStatic {
	public:
		static T t;
	};
	template <typename T> T  GlobalStatic<T>::t;
	template <typename T>
	T& Global()
	{
		return GlobalStatic<T>::t;
	}

	class RefCount
	{
	private:
		int crefs;
	public:
		RefCount(void)
		{
			crefs = 0;
		}
		virtual ~RefCount() {}
		void upcount(void)
		{
			++crefs;
			;
		}
		void downcount(void)
		{
			if (--crefs != 0)
				return;

			delete this;
		}
	};

	//�������Ҫ��ʹ������ָ��,��ô�����Ӧһ����Ҫ��
	//��ģ���еĳ�Ա���� upcount downcount  ,����������������Ǽ̳� RefCount
	//����ָ��Ҳ����Ϊ�˴���Ұָ��,�����������������մ���

	template <class T>
	class SmartPtr
	{
	private:
		T* p;
	public:
		SmartPtr(T* p_)
		{
			p = p_;
			if (p != NULL)
				p->upcount();     //��ģ���еĳ�Ա����
		}

		SmartPtr(const SmartPtr<T>& p_)
		{
			p = NULL;
			operator=(p_.p);
		}

		SmartPtr() : p(NULL) {}

		~SmartPtr(void)
		{
			if (p) p->downcount();     //��ģ���еĳ�Ա����
		}

		operator T* (void) { return p; }
		T& operator*(void) { return *p; }
		T* operator->(void) { return p; }

		SmartPtr& operator=(SmartPtr<T>& p_)
		{
			return operator=((T*)p_);
		}

		SmartPtr& operator=(T* p_)
		{
			if (p_)
				p_->upcount();

			if (p)
				p->downcount();

			p = p_;

			return *this;
		}
	};
};

#endif //SmartPtr_H