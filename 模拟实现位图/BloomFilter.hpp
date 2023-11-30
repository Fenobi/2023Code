#pragma once
#include <bitset>
#include <string>

namespace fu
{
	struct BKDRHash
	{
		size_t operator()(const std::string& key)
		{
			size_t hash = 0;
			for (auto ch : key)
			{
				hash *= 131;
				hash += ch;
			}
			return hash;
		}
	};

	struct APHash
	{
		size_t operator()(const std::string& key)
		{
			size_t hash = 0;
			size_t i = 0;
			for (auto ch : key)
			{
				if ((i & 1) == 0)
				{
					hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
				}
				else
				{
					hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
				}
				++i;
			}
			return hash;
		}
	};

	struct DJBHash
	{
		size_t operator()(const std::string& key)
		{
			size_t hash = 5381;

			for (auto ch : key)
			{
				hash += (hash << 5) + ch;
			}
			return hash;
		}
	};

	//假设N是最多存储的数据个数
	template<size_t N,
		class K = std::string,
		class HashFunc1 = APHash,
		class HashFunc2 = BKDRHash,
		class HashFunc3 = DJBHash>
	class BloomFilter
	{
	public:
		bool set(const K& key)
		{
			size_t hashi1 = HashFunc1()(key) % (5 * N);
			size_t hashi2 = HashFunc2()(key) % (5 * N);
			size_t hashi3 = HashFunc3()(key) % (5 * N);

			_bs.set(hashi1);
			_bs.set(hashi2);
			_bs.set(hashi3);
			return true;
		}

		bool test(const K& key)
		{
			size_t hashi1 = HashFunc1()(key) % (5 * N);
			if (!_bs.test(hashi1))
			{
				return false;
			}
			size_t hashi2 = HashFunc2()(key) % (5 * N);
			if (!_bs.test(hashi2))
			{
				return false;
			}
			size_t hashi3 = HashFunc3()(key) % (5 * N);
			if (!_bs.test(hashi3))
			{
				return false;
			}
			// 前面判断不在都是准确的
			return true;// 可能存在误判，映射的几个位置都冲突，就会误判
		}
	private:
		std::bitset<N * 5> _bs;
	};

	void test_bloomfilter()
	{
		std::string str[] = { "猪八戒","孙悟空","沙悟净","唐三藏","白龙马" };
		BloomFilter<10> bf;
		for (auto& str : str)
		{
			bf.set(str);
		}
		for (auto& s : str)
		{
			std::cout<<bf.test(s)<<"　";
		}
		srand(time(0));
		for (auto& s : str)
		{
			std::cout << bf.test(s+std::to_string(rand())) << "　";
		}
	}
}