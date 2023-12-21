#pragma once

#include <iostream>
#include <thread>

using namespace std;

namespace fu
{
	template<class T>
	class auto_ptr
	{
	public:
		// ������Դ
		auto_ptr(T* ptr)
			:_ptr(ptr)
		{}

		// �ͷ���Դ
		~auto_ptr()
		{
			delete[] _ptr;
			cout << _ptr << endl;
		}

		auto_ptr(auto_ptr<T>& sp)
			:_ptr(sp._ptr)
		{
			sp._ptr = nullptr;
		}

		// ��ָ��һ��
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

	template<class T>
	class unique_ptr
	{
	public:
		// ������Դ
		unique_ptr(T* ptr)
			:_ptr(ptr)
		{}

		// �ͷ���Դ
		~unique_ptr()
		{
			delete[] _ptr;
			cout << _ptr << endl;
		}

		unique_ptr(const unique_ptr<T>& up) = delete;

		// ��ָ��һ��
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

	template<class T>
	class shared_ptr
	{
	public:
		// ������Դ
		shared_ptr(T* ptr)
			:_ptr(ptr)
			,_pcount(new int(1))
		{}

		// �ͷ���Դ
		~shared_ptr()
		{
			Release();
		}

		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
			,_pcount(sp._pcount)
		{
			++(*_pcount);
			
		}

		void Release()
		{
			if (--(*_pcount) == 0)
			{
				delete[] _ptr;
				delete _pcount;
			}
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (_ptr == sp._ptr)
			{
				Release();
				_ptr = sp._ptr;
				_pcount = sp._pcount;
				++(*_pcount);
			}
			return *this;
		}

		// ��ָ��һ��
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
		int* _pcount;
	};

	void Test1()
	{
		int n = 10000000;
		shared_ptr<int> sp1(new int(1));
		thread t1([&]()
		{
			for (int i = 0; i < n; ++i)
			{
				shared_ptr<int> sp2(new int(1));
			}
		});
		thread t2([&]()
		{
			for (int i = 0; i < n; ++i)
			{
				shared_ptr<int> sp3(new int(1));
			}

		});
		t1.join();
		t2.join();
	}
}