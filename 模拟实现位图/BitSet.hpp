#pragma once

#include <iostream>
#include <vector>

namespace fu
{
	template<size_t N>
	class bitset
	{
	public:
		bitset()
		{
			_bits.resize((N >> 3) + 1, 0);
		}

		void set(size_t x)
		{
			size_t i = x >> 3;
			size_t j = x % 8;
			_bits[i] |= (0x01 << j);
		}

		void reset(size_t x)
		{
			size_t i = x >> 3;
			size_t j = x % 8;
			_bits[i] &= (~(0x01 << j));
		}

		bool test(size_t x)
		{
			size_t i = x >> 3;
			size_t j = x % 8;
			
			return _bits[i] & (0x01 << j);
		}

	private:
		std::vector<char> _bits;

	};
	
	template<size_t N>
	class twobitset
	{
	public:
		void set(size_t x)
		{
			if (!_bits1.test(x) && !_bits2.test(x)) // 00
			{
				_bits2.set(x);// 01
			}
			else if (!_bits1.test(x) && _bits2.test(x))//0 1
			{
				_bits1.set(x);
				_bits2.reset(x);// 10
			}
		}

		void PrintOnce()
		{
			for (size_t i = 0; i < N; ++i)
			{
				if (!_bits1.test(i) && _bits2.test(i))
				{
					std::cout << i << " ";
				}
			}
			std::cout << std::endl;
		}
	
	private:
		bitset<N> _bits1;
		bitset<N> _bits2;
	};
	void test_bitset()
	{
		bitset<0xffffffff> bs;
		bs.set(10);
		bs.set(1000);
		bs.set(100);
		bs.set(100000);

		std::cout << bs.test(10) << " ";
		std::cout << bs.test(100) << " ";
		std::cout << bs.test(1000) << " ";
		std::cout << bs.test(10000) << " ";
	}
	void test_bitsetonce()
	{
		twobitset<0xffff> bs;
		bs.set(10);
		bs.set(1000);
		bs.set(100);
		bs.set(100);
		bs.set(10000);
		bs.PrintOnce();
		
	}
}