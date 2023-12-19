#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

using namespace std;

namespace fu
{
	template<class T>
	struct list_node
	{
		list_node* _prev;
		list_node* _next;
		T _data;

		list_node(const T& x)
			:_prev(nullptr),
			_next(nullptr),
			_data(x)
		{}

		list_node(T&& x)
			:_prev(nullptr),
			_next(nullptr),
			_data(move(x))
		{}
	};

	//typedef __list_iterator<T, T&, T*> iterator;
	//typedef __list_iterator<T, const T&, const T*>const iterator;
	template<class T,class Ref,class Ptr>
	struct __list_iterator
	{
		typedef list_node<T> node;
		typedef __list_iterator<T, Ref,Ptr> Self;
		node* _pnode;

		__list_iterator(node* p)
			:_pnode(p)
		{}

		Ref operator*()
		{
			return _pnode->_data;
		}

		Ptr operator->()
		{
			return &_pnode->_data;
		}

		//++it
		Self& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}
		//--it
		Self& operator--()
		{
			_pnode = _pnode->_prev;
			return *this;
		}

		//it++
		Self operator++(int)
		{
			Self tmp(*this);
			_pnode = _pnode->_next;

			return tmp;
		}
		//it--
		Self operator--(int)
		{
			Self tmp(*this);
			_pnode = _pnode->_prev;

			return tmp;
		}

		bool operator!=(const Self& it)const
		{
			return _pnode != it._pnode;
		}

		bool operator==(const Self& it)const
		{
			return _pnode == it._pnode;
		}
	};

	/*template<class T>
	struct __list_const_iterator
	{
		typedef list_node<T> node;
		node* _pnode;

		__list_const_iterator(node* p)
			:_pnode(p)
		{}

		const T& operator*()
		{
			return _pnode->_data;
		}

		__list_const_iterator<T>& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}

		__list_const_iterator<T>& operator--()
		{
			_pnode = _pnode->prev;
			return *this;
		}

		bool operator!=(const __list_const_iterator<T>& it)
		{
			return _pnode != it._pnode;
		}
	};*/

	template<class T>
	class list
	{
		typedef list_node<T> node;
	public:
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;
		//typedef __list_const_iterator<T> const_iterator;
		
		void empty_initialize()
		{
			_head = new node(T());
			_head->_next = _head;
			_head->_prev = _head;
		}

		list()
		{
			empty_initialize();
		}

		////一般写法
		//list(const list<T>& lt)
		//{
		//	empty_initialize();

		//	for (const auto& e : lt)
		//	{
		//		push_back(e);
		//	}
		//}
		
		//list<T>& operator=(const list<T>& lt)
		//{
		//	if (this != &lt)
		//	{
		//		clear();
		//		for (const auto& e : lt)
		//		{
		//			push_back(e);
		//		}
		//	}
		//	return *this;
		//}

		//现代写法
		//迭代器区间构造
		template <class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_initialize();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		void swap(list<T>& lt)
		//void swap(list& lt)
		{
			std::swap(_head, lt._head);
		}

		// lt2(lt1)
		list(const list<T>& lt)
		//list(const list& lt)
		{
			empty_initialize();

			list tmp(lt.begin(), lt.end());
			swap(tmp);
		}

		//lt3 = lt1;
		list<T>& operator=(list<T> lt)
		//list& operator=(list lt)
		{
			swap(lt);
			return *this;
		}

		~list()
		{
			clear();

			delete _head;
			_head = nullptr;
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		size_t size() const
		{
			/*size_t count = 0;
			list<T>::iterator it = this->begin();
			while (it != this->end())
			{
				++count;
				++it;
			}
			return count;*/
			return _size;
		}

		bool empty() const
		{
			return _size == 0;

		}

		T& front()
		{
			return _head->_next->_data;
		}

		T& back()
		{
			return _head->_prev->_data;
		}

		void resize(size_t size)
		{
			int len = this->size() - size;
			if (len > 0)
			{
				while (len--)
				{
					this->pop_back();
				}
			}
			else
			{
				while (len++)
				{
					this->push_back(T());
				}
			}
		}

		void push_back(const T& x)
		{
			insert(end(), x);
		}

		void push_back(T&& x)
		{
			insert(end(), move(x));
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		void pop_back()
		{
			/*assert(this->size());
			node* tail = _head->prev;
			node* newtail = tail->prev;
			_head->prev = newtail;
			newtail->_next = _head;
			delete tail;*/
			erase(--end());
		}

		void pop_front()
		{
			/*assert(this->size());
			node* head = _head->_next;
			node* newhead = head->_next;
			_head->_next = newhead;
			newhead->prev = _head;
			delete head;*/
			erase(begin());
		}

		iterator insert(iterator pos,const T& x)
		{
			node* newnode = new node(x);
			node* prev = pos._pnode->_prev;
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = pos._pnode;
			pos._pnode->_prev = newnode;

			++_size;
			return iterator(newnode);
		}

		iterator insert(iterator pos, T&& x)
		{
			node* newnode = new node(move(x));
			node* prev = pos._pnode->_prev;
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = pos._pnode;
			pos._pnode->_prev = newnode;

			++_size;
			return iterator(newnode);
		}
		
		iterator erase(iterator pos)
		{
			assert(pos != end());

			node* prev = pos._pnode->_prev;
			node* next = pos._pnode->_next;

			prev->_next = next;
			next->_prev = prev;
			
			delete pos._pnode;
			--_size;

			return iterator(next);
		}

	private:
		node* _head;
		size_t _size;
	};

	//void test1()
	//{
	//	list<int> lt;

	//	lt.push_back(1);
	//	lt.push_back(2);
	//	lt.push_back(3);
	//	lt.push_back(4);
	//	list<int>::iterator it = lt.begin();
	//	while (it != lt.end())
	//	{
	//		cout << *it << ' ';
	//		++it;
	//	}
	//	cout << endl;
	//	for (auto e : lt)
	//	{
	//		cout << e << ' ';
	//	}
	//	cout << endl;
	//	cout << lt.size() << endl;
	//	cout << lt.back() << endl;
	//	cout << lt.front() << endl;
	//}
	//void test2()
	//{
	//	list<int> lt;
	//	lt.push_back(1);
	//	lt.push_back(2);
	//	lt.push_back(3);
	//	lt.pop_back();
	//	lt.push_front(10);
	//	lt.pop_front();
	//	//lt.pop_back();
	//	//lt.resize(10);
	//	for (auto e : lt)
	//	{
	//		cout << e << ' ';
	//	}
	//}
	//void test3()
	//{
	//	list<int> lt;
	//	lt.push_back(1);
	//	lt.push_back(2);
	//	lt.push_back(3);
	//	lt.push_back(4);
	//	lt.push_back(5);
	//	list<int>::iterator it = lt.end();
	//	//it = find(lt.begin(), lt.end(), 3);
	//	lt.insert(it, 10);
	//	for (auto e : lt)
	//	{
	//		cout << e << ' ';
	//	}
	//}
	//void test4()
	//{
	//	list<int> lt1;
	//	list<int> lt3;
	//	lt1.push_back(1);
	//	lt1.push_back(1);
	//	lt1.push_back(1);
	//	lt1.push_back(1);
	//	list<int> lt2(lt1);
	//	lt3 = lt1;
	//	for (auto e : lt2)
	//	{
	//		cout << e << ' ';
	//	}
	//}
	//void test5()
	//{
	//	list<int> lt1;
	//	lt1.push_back(1);
	//	lt1.push_back(2);
	//	lt1.push_back(3);
	//	lt1.push_back(4);
	//	list<int>::iterator it = lt1.begin();
	//}

	//struct Pos
	//{
	//	Pos(int x = 0, int y = 0)
	//		:_x(x)
	//		,_y(y)
	//	{}

	//	int _x;
	//	int _y; 

	//};

	//void test6()
	//{
	//	list<Pos> lt;
	//	lt.push_back(Pos(1, 1));
	//	lt.push_back(Pos(2, 2));
	//	lt.push_back(Pos(3, 3));
	//	list<Pos>::iterator it = lt.begin();
	//	while (it != lt.end())
	//	{
	//		cout << it->_x << ":" << it->_y << '\n';
	//		++it;
	//	}
	//}
	void test8()
	{
		string s("1234");
		list<string> li;
		li.push_back(move(s));
		li.push_back("12345");
		li.push_back(string("123456"));
	}
}
