#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

//class Person
//{
//public:
//	void Print()
//	{
//		cout << "name:" << _name << endl;
//		cout << "age:" << _age << endl;
//	}
//
////protected:
//	string _name = "kenobi";
//	static int _age;
//};
//int Person::_age = 0;
//class Student : public Person
//{
//protected:
//	int _stuid;
//};
//
//class Teacher : public Person
//{
//protected:
//	int _jobid;
//};
//
//int main()
//{
//	
//	Student s;
//	Teacher t;
//	s.Print();
//	t.Print();
//	Person p;
//	++p._age;
//	cout << p._age << endl;
//
//	Person* p = nullptr;
//	
//	return 0;
//}



//class Person
//{
//public:
//	void Print()
//	{
//		cout << "name:" << _name << endl;
//		cout << "age:" << _age << endl;
//	}
//
//	string _name = "kenobi";
//	static int _age;
//};
//int Person::_age = 0;
//class Student :virtual public Person
//{
//protected:
//	int _stuid;
//};
//
//class Teacher :virtual public Person
//{
//protected:
//	int _jobid;
//};
//
//class Preant :public Student, public Teacher
//{
//public:
//	int _stu;
//	int _job;
//};
//
//int main()
//{
//	/*Preant pr;
//	pr._name = "Fenobi";
//	pr._age = 21;
//	pr._job = 23;
//	pr.Print();*/
//	//cout << pr.Student::_name << endl;
//	//cout << pr.Teacher::_name << endl;
//	return 0;
//}

//class A
//{
//public:
//	int _a;
//};
//
//class B :virtual public A
//{
//public:
//	int _b;
//};
//
//class C :virtual public A
//{
//public:
//	int _c;
//};
//
//class D :public B,public C
//{
//public:
//	int _d;
//};
//
//int main()
//{
//	D d;
//	d._b = 2;
//	d._c = 3;
//	d._d = 4;
//	d.B::_a = 5;
//	d.C::_a = 6;
//	d._a = 1;
//
//	B b;
//	b._a = 1;
//	b._b = 2;
//	B* ptr = &b;
//	ptr->_a = 10;
//
//	ptr = &d;
//	ptr->_a = 20;
//	return 0;
//}

//¼Ì³Ð
class X
{
	int _x;
};

class Y :public X
{
	int _y;
};

//×éºÏ
class M
{
	int _m;
};

class N
{
	M m;
	int _n;
};