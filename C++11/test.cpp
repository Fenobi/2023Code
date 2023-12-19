#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <list>
#include "vector.h"
#include "string.h"
#include "list.h"

using namespace std;
//
//struct Point
//{
//	int _x;
//	int _y;
//};
//
//int main()
//{
//	Point p1 = { 1,2 };
//	Point p2{ 2,3 };
//	int arr1[] = { 1,2,3,4 };
//	int arr2[]{ 1,2,3,4 };
//
//	int a = 1;
//	int a1 = { 1 };
//	int a2{ 2 };
//
//	int* p3 = new int[10];
//	int* p4 = new int[10] {1, 2, 3, 4};//c++11
//
//	Point* p5 = new Point[2]{ { 1,2 }, { 2,3 } };
//
//	return 0;
//}
//
//template<class T1,class T2>
//void F(T1 t1, T2 t2)
//{
//	decltype(t1 * t2) ret = t1 * t2;
//	cout << typeid(ret).name() << endl;
//	cout << ret << endl;
//}
//
//int main()
//{
//	vector<int> v1 = { 1,2,3,4,5 };
//	vector<int> v2 = { 1,2,3,4,5,6,7 };
//
//	list<int> l1 = { 1,2 };
//
//	auto il = { 1,4,5 };
//	cout << typeid(il).name() << endl;//class std::initializer_list<int>
//	map<string, string> m = { {"字符串","string"},{"排序","sort"} };
//	fu::test6();
//	F(1, 2);
//	F(1, 2.2);
//	decltype(v1) v3;
//	return 0;
//}
//

//int main()
//{
//	array<int, 10> a1;
//	int a2[10];
//	a2[0] = 1;
//	return 0;
//}

//int main()
//{
//	////fu::test7();
//	//list<fu::string> lt;
//	//fu::string s1("234");
//	//lt.push_back(s1); 
//
//	//lt.push_back(fu::string("1234"));
//
//	//lt.push_back("345");
//
//	//double d1 = 1.1, d2 = 2.2;
//	//int&& r1 = 1;
//	//const double&& r2 = d1 + d2;
//	//r1++;
//	////r2++;
//	//cout << &r1 << endl;
//	//cout << &r2 << endl;
//
//	fu::test8();
//
//
//	return 0;
//}

//void test1(int& x)
//{
//	cout << "void test1(int& x)" << endl;
//}
//
//void test1(int&& x)
//{
//	cout << "void test1(int&& x)" << endl;
//}
//
//void test1(const int& x)
//{
//	cout << "void test1(const int& x)" << endl;
//}
//
//void test1(const int&& x)
//{
//	cout << "void test1(const int&& x)" << endl;
//}
//
////万能引用
//template<typename T>
//void PrefectForward(T&& t)
//{
//	// t可能是左值，可能是右值
//	//test1(t);
//
//	// 完美转发，保持属性
//	test1(std::forward<T>(t));
//} 
//
//int main()
//{
//	int a = 1;
//	/*test1(a);
//	test1(2);*/
//	PrefectForward(a);
//	PrefectForward(2);
//	const int b = 3;
//	PrefectForward(b);
//	PrefectForward(move(b));
//	return 0;
//}

//class Person
//{
//public:
//	Person(const char* name = "", int age = 0)
//		:_name(name)
//		, _age(age)
//	{}
//
//	
//
//	//Person(const Person& p)
//	//:_name(p._name)
//	//,_age(p._age)
//	//{}
//	//Person& operator=(const Person& p)
//	//{
//	//	if (this != &p)
//	//	{
//	//		_name = p._name;
//	//		_age = p._age;
//	//	}
//	//	return *this;
//	//}
//	//~Person()
//	//{}
//private:
//	fu::string _name;
//	int _age;
//};
//int main()
//{
//	Person s1;
//	Person s2 = s1;
//	Person s3 = std::move(s1);
//	Person s4;
//	s4 = std::move(s2);
//	return 0;
//}

//struct Goods
//{
//	string _name; // 名字
//	double _price; // 价格
//	int _evaluate; // 评价
//	Goods(const char* str, double price, int evaluate)
//		:_name(str)
//		, _price(price)
//		, _evaluate(evaluate)
//	{}
//};
//
//int main()
//{
//	vector<Goods> v = { { "苹果", 2.1, 5 }, { "香蕉", 3, 4 }, { "橙子", 2.2,3 }, { "菠萝", 1.5, 4 } };
//	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2)
//		{
//			return g1._price < g2._price;
//		});
//	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2)
//		{
//			return g1._price > g2._price;
//		});
//	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2)
//		{
//			return g1._evaluate < g2._evaluate;
//		});
//	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2
//		) {
//			return g1._evaluate > g2._evaluate;
//		});
//	return 0;
//}

//int main()
//{
//	int t1 = 1, t2 = 2;
//	auto compare = [](int x, int y)->bool{return x > y;};
//	//引用的方式捕捉
//	auto c = [&t1, &t2](int a, int b)//mutable
//		{
//			t2 += t1;
//			a += t2;
//			return a < b;
//		};
//	auto c1 = [&](int a, int b)//mutable
//		{
//			t2 += t1;
//			a += t2;
//			return a < b;
//		};
//	auto c2 = [=, &t2](int a, int b)//mutable
//		{
//			t2 += t1;
//			a += t2;
//			return a < b;
//		};
//
//	c(4, 4);
//	cout << t1 << " " << t2 << endl;
//	cout << typeid(compare(1, 2)).name() << endl;
//	cout << compare(1, 2) << endl;
//	return 0;
//}

#include <thread>

//void print1(int& x)
//{
//	for (; x < 100; ++x)
//		cout << "thread1: " << x << endl;
//}
//
//void print2(int& x)
//{
//	for (; x < 100; ++x)
//		cout << "thread2: " << x << endl;
//
//}
//
//int main()
//{
//	int i = 0;
//	thread t1(print1, ref(i));
//	thread t2(print2, ref(i));
//	cout << "xxxxxxxxxxxxxxxxxx" << endl;
//	t1.join();
//	t2.join();
//	cout << "xxxxxxxxxxxxxxxxxx" << endl;
//
//	return 0;
//}

//int main()
//{
//	int i = 0;
//	thread t1([&i]()
//		{
//			for (; i < 100; ++i)
//				cout << "thread1: " << i << endl;
//		});
//	thread t2([&i]()
//		{
//			for (; i < 100; ++i)
//				cout << "thread1: " << i << endl;
//		});
//	cout << "xxxxxxxxxxxxxxxxxx" << endl;
//	t1.join();
//	t2.join();
//	cout << "xxxxxxxxxxxxxxxxxx" << endl;
//
//	return 0;
//}

//int main()
//{
//	vector<thread> vThread;
//	int n;
//	cin >> n;
//	vThread.resize(n);
//	int i = 0;
//	int x = 0;
//	for (auto& t : vThread)
//	{
//		t = thread([&i, x]()
//			{
//				while (i < 100000)
//				{
//					cout << "thread" << x << "->" << i++ << endl;
//				}
//			});
//		++x;
//	}
//
//	for (auto& t : vThread)
//	{
//		t.join();
//	}
//	return 0;
//}

////Args是一个模板参数包，args是一个函数形参参数包
////声明一个参数包Args...args,这个参数包中可以包含0到任意个模板参数
//template<class T, class... Args>
//void ShowList(T val, Args&&... args)
//{
//	cout << val << " ";
//	ShowList(args...);
//	//参数包中有几个参数
//	cout << sizeof...(args) << endl;
//}
//
//int main()
//{
//	ShowList(1, 1.1, string("123"), vector<int>{1, 2, 3});
//	return 0;
//}

//void ShowList()
//{
//	cout << endl;
//}
//
////args参数包可以接收0~N个参数
//template<class T, class ...Args>
//void ShowList(T val, Args... args)
//{
//	cout << typeid(val).name() << ": " << val << endl;
//	ShowList(args...);
//}
//
//int main()
//{
//	ShowList(1, 1.1, string("123"));
//	return 0;
//}

//template<class T>
//void PrintArg(T t)
//{
//	cout << t << " ";
//	return 0;
//}
//
////args参数包可以接收0~N个参数
//template<class ...Args>
//void ShowList(Args... args)
//{
//	int arr[] = { (PrintArg(args),0)... };
//	cout << endl;
//}

//template<class T>
//int PrintArg(T t)
//{
//	cout << t << " ";
//	return 0;
//}
//
////args参数包可以接收0~N个参数
//template<class ...Args>
//void ShowList(Args... args)
//{
//	//int arr[] = { (PrintArg(args),0)... };
//	int arr[] = { PrintArg(args)... };
//	cout << endl;
//}
//
//int main()
//{
//	ShowList(1, 1.1, string("123"));
//	return 0;
//}

//int main()
//{
//	//std::list<int> list1;
//	//list1.push_back(1);
//	//list1.emplace_back(2);
//	////list1.emplace_back(3,4,5);
//
//	//for (auto e : list1)
//	//{
//	//	cout << e << " ";
//	//}
//
//	//std::list<std::pair<int, char> >mylist;
//	//mylist.push_back(make_pair(1, 'a'));//构造+拷贝构造
//	//mylist.emplace_back(1, 'a');//直接构造
//
//	std::list<std::pair<int, fu::string> >mylist;
//	pair<int, fu::string> kv(20, "123");
//	mylist.push_back(kv);//左值
//	mylist.push_back(make_pair(30, "234"));//右值
//	mylist.push_back({ 40,"345" });//右值
//
//	cout << endl;
//
//	mylist.emplace_back(kv);//左值
//	mylist.emplace_back(make_pair(30, "234"));//右值
//	mylist.emplace_back( 40,"345" );//右值
//
//	return 0;
//}

#include <functional>

//void func(int x, int y)
//{
//	cout << x + y << endl;
//}
//
//struct Functor
//{
//public:
//	void operator()(int x, int y)
//	{
//		cout << x + y << endl;
//	}
//	
//};
//
//class Plus
//{
//public:
//	void func(int x, int y)
//	{
//		cout << x + y << endl;
//	}
//	static void staticfunc(int x, int y)
//	{
//		cout << x + y << endl;
//	}
//};
//
//int main() 
//{
//	function<void(int, int)> f1;
//	f1 = func;
//	function<void(int, int)> f2(f1);
//	f1(1, 2);
//	f2(2, 3);
//	f1 = Functor();
//	function<void(int, int)> f3(f1);
//	//function<void(int, int)> f4(Functor());//识别报错
//	f3(4, 5);
//
//	function<void(int, int)> f4 = [](const int x, const int y)->void//lambda
//		{
//			cout << x + y << endl;
//		};
//	f4(5, 6);
//	function<void(Plus, int, int)> f5 = &Plus::func;//类成员函数
//	function<void(int, int)> f6 = Plus::staticfunc;//类静态成员函数
//	f5(Plus(), 1, 2);
//	f6(2, 3);
//	return 0;
//}

//void Pluc(int x, int y)
//{
//	cout << x << " " << y << endl;
//}
//
//class Print
//{
//public:
//	void print(int x, int y)
//	{
//		cout << x << " " << y << endl;
//	}
//};
//
//int main()
//{
//	function<void(int, int)> func1 = bind(Pluc, placeholders::_1, placeholders::_2);
//	func1(1, 2);
//	function<void(int, int)> func2 = bind(Pluc, placeholders::_2, placeholders::_1);
//	func2(1, 2);
//
//	function<void(Print,int, int)> func3 = &Print::print;
//	func3(Print(), 2, 3);
//
//	function<void(int, int)> func4 = bind(&Print::print, Print(), placeholders::_1, placeholders::_2);
//	func4(2, 3);
//
//	return 0;
//}