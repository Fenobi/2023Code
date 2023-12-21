#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include "SmartPtr.h"
#include <memory>

using namespace std;

template<class T>
class SmartPtr
{
public:
	// 保存资源
	SmartPtr(T* ptr)
		:_ptr(ptr)
	{}

	// 释放资源
	~SmartPtr()
	{
		delete[] _ptr;
		cout << _ptr << endl;
	}

	// 像指针一样
	T& operator*()
	{
		return *_ptr;
	}

	T& operator[](size_t i)
	{
		return *(_ptr + i);
	}
private:
	T* _ptr;
};

int div()
{
	int x, y;
	cin >> x >> y;
	if (y == 0)
	{
		throw "不能除零";
	}
	else
	{
		return x / y;
	}
}

void func()
{
	/*int* p1 = new int[10];
	SmartPtr<int> sp1 = p1;
	*sp1 = 1;*/


	cout << div() << endl;
}

//C++智能指针发展历史
//C++98 auto_ptr 资源管理权转移-->对象悬空 不使用
//boost scoped_ptr 防拷贝
//boost shared_ptr/weak_ptr
//C++11 unique_ptr 防拷贝
//C++11 shared_ptr/weak_ptr
//
//int main()
//{
//	//int* p1 = new int[10];
//	//SmartPtr<int> sp1 = p1;
//	
//	//auto_ptr<int> ap1 = p1;
//	//auto_ptr<int> ap2(ap1);
//	
//	//unique_ptr<int> up1(new int);
//	//unique_ptr<int> up2(up1);
//
//	fu::shared_ptr<int> sp1(new int(0));
//	fu::shared_ptr<int> sp2(sp1);
//
//	(*sp1)++;
//	(*sp2)++;
//	
//	cout << *sp1 << " " << *sp2 << endl;
//
//	fu::shared_ptr<int> sp3(new int(10));
//	fu::shared_ptr<int> sp4(sp3);
//
//	sp1 = sp3;
//	sp2 = sp1;
//	//SmartPtr<int> sp2(sp1);
//	/*try
//	{
//		func();
//	}
//	catch (const char* e)
//	{
//		cout << e << endl;
//	}*/
//
//	return 0;
// }

int main()
{
	fu::Test1();

	return 0;

}