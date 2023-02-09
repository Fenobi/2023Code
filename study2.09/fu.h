#pragma once

#include <iostream>


using namespace std;

namespace fu
{
	template<class T>
	struct list_node
	{
		list_node* _prve;
		list_node* _next;
		T _data;

		list_node(const T& x)
			:_prve(nullptr),
			_next(nullptr),
			_data(x);
		{}
	};
	template <class T>
	struct __list_iterator
	{
		typedef list_node<T> node;
		node* _pnode;

		__list_iterator (node* p)
			:_pnode(p)
		{}
		
		T& operator*()
		{
			return _pnode->_data;
		}

		__list_iterator<T>& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}

		__list_iterator<T>& operator--()
		{
			_pnode = _pnode->prve;
			return *this;
		}

		bool operator!=(const __list_iterator<T>& lt)
		{
			return _pnode != lt._pnode;
		}
	};


	template<class T>
	class list
	{
		typedef list_node<T> node;
	public:
		typedef __list_iterator<T> iterator;

		list()
		{
			empty_initialize();
		}

		list(const list<T>& lt)
		{
			empty_initialize();
			for (const auto& e : lt)
			{
				push_back(e);
			}
		}

		void empty_initialize()
		{
			_head = new node(T());
			_head->_next = _head;
			_head->_prve = _head;
		}

		clear()
		{
			;
		}
			
		iterator begin()const
		{
			return iterator(_head->_next);
		}

		iterator end()const
		{
			return iterator(_head);
		}

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		size_t size()
		{
			size_t count = 0;
			list<T>::iterator it = this->begin();
			while (it != this->end())
			{
				++count;
				++it;
			}
			
			return count;
		}

		bool empty()
		{
			return !this->size();
		}

		T& front()
		{
			return _head->_next->_data;
		}

		T& back()
		{
			return _head->_prve->_data;
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
	private:
		node* _head;
	};
	void test1()
	{
		list<int> lt;
		
	}
}