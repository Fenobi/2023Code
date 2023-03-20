#pragma once

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

namespace fu
{
	template<class T, class Container = vector<T>, class Compare = less<T> >
	class priority_queue
	{ 
	public:
		priority_queue()
		{}

		template <class InputIterator>
		priority_queue(InputIterator first, InputIterator last)
		:_con(first,last)
		{
			for (int i = (_con.size() - 1 - 1) / 2; i > 0; --i)
			{
				adjust_down(i);
			}
		}

		void adjust_down(size_t parent)
		{
			size_t child = parent * 2 + 1;
			Compare com;

			while (child <_con.size())
			{
				if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))
				{
					++child;
				}

				if (com(_con[parent] , _con[child]))
				{
					swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
		
		void adjust_up(size_t child)
		{
			Compare com;
			size_t parent = (child - 1) / 2;
			while (child > 0)
			{
				if (com(_con[parent], _con[child]))
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}

		void push(const T& x)
		{
			_con.push_back(x);
			adjust_up(_con.size() - 1);
		}
		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();

			adjust_down(0);
		}
		size_t size() const
		{
			return _con.size();
		}
		const T& top() const
		{
			return _con[0];
		}
		bool empty() const 
		{
			return _con.empty();
		}
	private:
		Container _con;
	};
}

