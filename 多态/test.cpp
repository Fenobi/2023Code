#include <iostream>

using namespace std;

typedef void(*VFPtr)();//����ָ��������
//class Person
//{
//public:
//	virtual void BuyTicket()
//	{
//		cout << "ȫ��" << endl;
//	}
//};
//
//class Student :public Person
//{
//public:
//	virtual void BuyTicket()
//	{
//		cout << "���" << endl;
//	}
//};
//
//void Func(Person& p)
//{
//	p.BuyTicket();
//}
//
//int main()
//{
//	Person pn;
//	Student st;
//	Func(pn);
//	Func(st);
//
//	return 0;
//}

//class Person
//{
//public:
//	virtual void BuyTicket()
//	{
//		cout << "ȫ��" << endl;
//	}
//};
//
//class Student :public Person
//{
//public:
//	void BuyTicket()
//	{
//		cout << "���" << endl;
//	}
//};
//
//void Func(Person& p)
//{
//	p.BuyTicket();
//}
//
//int main()
//{
//	Person pn;
//	Student st;
//	Func(pn);
//	Func(st);
//
//	return 0;
//}

//class Person
//{
//public:
//	virtual Person* BuyTicket()
//	{
//		cout << "ȫ��" << endl;
//		return this;
//	}
//};
//
//class Student :public Person
//{
//public:
//	virtual Student* BuyTicket()
//	{
//		cout << "���" << endl;
//		return this;
//	}
//};
//
//void Func(Person& p)
//{
//	p.BuyTicket();
//}
//
//int main()
//{
//	Person pn;
//	Student st;
//	Func(pn);
//	Func(st);
//
//	return 0;
//}

//class Person
//{
//public:
//	virtual void BuyTicket()
//	{
//		cout << "ȫ��" << endl;
//	}
//};
//
//class Student :public Person
//{
//public:
//	virtual void BuyTicket()
//	{
//		cout << "���" << endl;
//	}
//};
//
//void Func(Person& p)
//{
//	p.BuyTicket();
//}
//
//int main()
//{
//	Person pn;
//	Student st;
//	Func(pn);
//	Func(st);
//
//	return 0;
//}

//class Person
//{
//public:		
//	virtual ~Person()
//	{
//		cout << "Person delete:" << _p << endl;
//		delete[] _p;
//	}
//protected: 
//	int* _p = new int[10];
//};
//
//class Student :public Person
//{
//public:
//	~Student()
//	{
//		cout << "Student delete:" << _s << endl;
//		delete[] _s;
//	}
//protected:
//	int* _s = new int[20];
//};
//
//int main()
//{
//	Person* ptr1 = new Person;
//	Person* ptr2 = new Student;
//
//	delete ptr1;
//	delete ptr2;
//	return 0;
//}

// ���ʵ��һ�����ܱ��̳е���
// 1��������˽�� C++98
// 2���ඨ��ʱ ��fanal C++11
//

//class A final
//{
//public:
//	A()
//	{}
//};
//
//class B:public A
//{
//public:
//
//};
//
//int main()
//{
//	B bb;
//	return 0;
//}

//class Car
//{
//public:
//	virtual void Drive(int){}
//};
//
//class Benz :public Car
//{
//public:
//	virtual void Drive() override
//	{
//		cout << "Benz" << endl;
//	}
//};
//
//int main()
//{
//
//	return 0;
//}


// ������ -- ����ʵ����������
//class Car
//{
//public:
//	//���麯��
//	virtual void Drive() = 0;
//};
//
//class BMW :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "��д" << endl;
//	}
//};
//
//int main()
//{
//	BMW b;
//	//Car c;
//	return 0;
//}

//class A
//{
//public:
//	virtual void func(int val = 1)
//	{
//		cout << "A->" << val << endl;
//	}
//	virtual void test()
//	{
//		func();
//	}
//};
//
//class B :public A
//{
//	void func(int val = 0)
//	{
//		cout << "B->" << val << endl;
//	}
//
//};
//
//int main()
//{
//	B* pb = new B;
//	pb->test();
//}

//class Base
//{
//public:
//	virtual void Func1()
//	{
//		cout << "Base::Func1()" << endl;
//	}
//
//	virtual void Func2()
//	{
//		cout << "Base::Func2()" << endl;
//	}
//
//	void Func3()
//	{
//		cout << "Base::Func3()" << endl;
//	}
//
//private:
//	int _b = 1;
//	char _ch;
//};
//
//class Derive : public Base
//{
//public:
//	virtual void Func1()
//	{
//		cout << "Derive::Func1()" << endl;
//	}
//
//	void Func3()
//	{
//		cout << "Derive::Func3()" << endl;
//	}
//private:
//	int _d = 2;
//};

//int main()
//{
//	Base b;
//	Derive d;
//	//��̬���� -- ����ʱ/��̬ ��
//	Base* ptr = &b;
//	ptr->Func3();
//	ptr = &d;
//	ptr->Func3();
//	
//	//��̬���� -- ����ʱ/��̬ ��
//	ptr = &b;
//	ptr->Func1();
//	ptr = &d;
//	ptr->Func1();
//	return 0;
//}


//int main()
//{
//	int a = 2;
//	cout << "ջ��" << &a << endl;
//
//	int* p1 = new int;
//	cout << "�ѣ�" << p1 <<endl;
//
//	const char* str = "hello!";
//	cout << "��������" << (void*)str << endl;
//
//	static int b = 0;
//	cout << "��̬����" << &b << endl;
//
//	Base bs;
//	cout << "���:" << (void*)*((int*)&bs) << endl;
//
//	return 0;
//}

//void PrintVFPable(VFPtr vft[], int n)
//{
//	for (int i = 0; i < n; ++i)
//	{
//		printf("[%d]:%p\n", i, vft[i]);
//	}
//}

//void PrintVFPable(VFPtr vft[])
//{
//	for (int i = 0; vft[i] != nullptr; ++i)
//	{
//		printf("[%d]:%p->", i, vft[i]);
//		vft[i]();
//	}
//}
//
//int main()
//{
//	Base b;
//
//	PrintVFPable((VFPtr*)(*(void**)&b));//void**�����þ��ǻ���λ��void��С��int**/double**ͬ��
//
//	//PrintVFPable((VFPtr*)(*(long long*)&b));
//	
//	return 0;
//}

class Base1 
{
public:
	virtual void func1() 
	{ 
		cout << "Base1::func1" << endl; 
	}
	virtual void func2() 
	{ 
		cout << "Base1::func2" << endl;
	}
private:
	int b1;
};

class Base2 
{
public:
	virtual void func1()
	{
		cout << "Base2::func1" << endl;
	}
	virtual void func2()
	{
		cout << "Base2::func2" << endl;
	}
private:
	int b2;
};

class Derive : public Base1, public Base2 
{
public:
	virtual void func1() 
	{ 
		cout << "Derive::func1" << endl;
	}
	virtual void func3() 
	{
		cout << "Derive::func3" << endl;
	}
private:
	int d1;
};

void PrintVFPable(VFPtr vft[])
{
	for (int i = 0; vft[i] != nullptr; ++i)
	{
		printf("[%d]:%p->", i, vft[i]);
		VFPtr f = vft[i];
		f();

	}
}

int main()
{
	Base1 b1;
	Base2 b2;

	PrintVFPable((VFPtr*)(*(void**)&b1));
	cout << endl;
	PrintVFPable((VFPtr*)(*(void**)&b2));
	cout << endl; 

	Derive d;
	PrintVFPable((VFPtr*)*(void**)&d);
	cout << endl;

//	PrintVFPable((VFPtr*)(*(void**)((char*)&d + sizeof(Base1))));
//	cout << endl;

	Base2* ptr2 = &d;
	PrintVFPable((VFPtr*)(*(void**)ptr2));
	cout << endl;

	return 0;
}