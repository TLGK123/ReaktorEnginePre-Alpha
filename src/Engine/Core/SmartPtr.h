//The MIT License
//
//Copyright(c) 2016 - 2019 littleblue
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//copies of the Software, and to permit persons to whom the Software is furnished
//to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
//COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#pragma once
#include <iostream>
#ifndef SmartPtr_H
#define SmartPtr_H

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

template <class T>
class SmartPtr
{
private:
	T * p;
public:
	SmartPtr(T* p_)
	{
		p = p_;
		if (p != NULL)
			p->upcount();
	}

	SmartPtr(const SmartPtr<T> & p_)
	{
		p = NULL;
		operator=(p_.p);
	}

	SmartPtr() : p(NULL) {}

	~SmartPtr(void)
	{
		if (p) p->downcount();
	}

	operator T*(void) { return p; }
	T& operator*(void) { return *p; }
	T* operator->(void) { return p; }

	SmartPtr& operator=(SmartPtr<T> &p_)
	{
		return operator=((T *)p_);
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


#endif