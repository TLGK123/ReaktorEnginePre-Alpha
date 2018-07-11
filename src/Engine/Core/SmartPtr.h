#pragma once
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