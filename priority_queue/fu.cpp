#include "priority_queue.h"
//#include "list.h"
#include "vector.h"

//int main()
//{
//	fu::priority_queue<int> pq;
//	//fu::priority_queue<int, vector<int>, greater<int>> pq;
//	pq.push(6);
//	pq.push(4);
//	pq.push(3);
//	pq.push(7);
//	while(!pq.empty())
//	{
//		cout << pq.top() << ' ';
//		pq.pop();
//	}
//	return 0;
//}

//namespace fu//·Âº¯Êý
//{
//	template <class T>
//	struct less
//	{
//		bool operator()(const T& x, const T& y)
//		{
//			return x < y;
//		}
//	};
//
//	template <class T>
//	struct greater
//	{
//		bool operator()(const T& x, const T& y)
//		{
//			return x > y;
//		}
//	};
//}

template<class T,class Compare>
void BuobleSort(T* a, int n,Compare com)
{
	for (int i = 0; i < n; i++)
	{
		int exchange = 0;
		for (int j = 1; j < n - i; j++)
		{
			if (com(a[j], a[j - 1]))
			{
				swap(a[j - 1], a[j]);
				exchange = 1;
			}
		}
		if (exchange == 0)
		{
			break;
		}
	}
}

//int main()
//{
//	fu::less<int> lessFunc;
//	fu::greater<int> greaterFunc;
//	//lessFunc(1, 2);
//	int a[] = { 2,3,1,4,5,3,4,5 };
//	BuobleSort(a, sizeof(a) / sizeof(int), greaterFunc);
//	for (auto e : a)
//	{
//		cout << e << ' ';
//	}
//	cout << endl;
//	fu::priority_queue<int> pe;
//	
//	return 0;
//}

int main()
{
	//fu::test7();
	fu::test6();
	return 0;
}