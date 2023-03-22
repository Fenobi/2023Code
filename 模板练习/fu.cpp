#include <iostream>
using namespace std;

//#define N 10
//非类型模板参数 -- 常量
template<class T,size_t N = 50>
class Array
{
public:

private:
	T _a[N];
};

template<class T1,class T2>
class Data
{
public:
	Data()
	{
		cout << "a" << '\n';
	}
private:
	
};

template<>
class Data<double, double>
{
public:
	Data()
	{
		cout << "b" << '\n';
	}
private:

};

template<class T1>
class Data<T1, char>
{
public:
	Data()
	{
		cout << "c" << '\n';
	}
private:

};


int main()
{
	Data<int, int> a;
	Data<double, double> b;
	Data<char, char> c1;
	Data<char, char> c2;
	return 0;
}