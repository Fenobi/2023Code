#pragma once

#include "HashTable.hpp"

namespace fu
{
	template<class K, class Hash = HashFunc<K>>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename bucketHash::HashTable<K, K, Hash, SetKeyOfT>::iterator iterator;
		typedef typename bucketHash::HashTable<K, K, Hash, SetKeyOfT>::const_iterator const_iterator;

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		const_iterator begin() const 
		{
			return _ht.begin();
		}

		const_iterator end() const
		{
			return _ht.end();
		}

		std::pair<iterator, bool> Insert(const K& key)
		{
			return _ht.Insert(key);
		}

		iterator Find(const K& key)
		{
			return _ht.Find(key);
		}

		bool Erase(const K& key)
		{
			return _ht.Erase();
		}

	private:
		bucketHash::HashTable<K, K, Hash, SetKeyOfT> _ht;
	};

	void Func(const unordered_set<int>& us)
	{
		unordered_set<int>::const_iterator it = us.begin();
		
		while (it != us.end())
		{
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;
	}

	void Test_unordered_set()
	{
		unordered_set<int> us;
		us.Insert(3);
		us.Insert(13);
		us.Insert(23);
		us.Insert(5);
		us.Insert(15);
		us.Insert(6);

		unordered_set<int>::iterator it = us.begin();
		while (it != us.end())
		{
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;
		
		for (auto e : us)
		{
			std::cout << e << " ";
		}
		Func(us);
	}
	
	
}