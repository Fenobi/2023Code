#pragma once

#include "RBTree.hpp"

namespace fu
{
	template<class K, class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const std::pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename RBTree<K, std::pair<const K, V>, MapKeyOfT>::iterator iterator;
		typedef typename RBTree<K, std::pair<const K, V>, MapKeyOfT>::const_iterator const_iterator;

		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		const_iterator begin() const
		{
			return _t.begin();
		}

		const_iterator end() const
		{
			return _t.end();
		}

		std::pair<iterator, bool> Insert(const std::pair<const K, V>& kv)
		{
			return _t.Insert(kv);
		}

		V& operator[](const K& key)
		{
			std::pair<iterator, bool> ret = Insert(std::make_pair(key, V()));
			return ret.first->second;
		}

	private:
		RBTree<K, std::pair<const K, V>, MapKeyOfT> _t;
	};
	void TestMap1()
	{
		int a[] = { 4,2,6,1,3,5,15,17,16,14 };
		map<int, int> m;
		for (auto e : a)
		{
			m.Insert(std::make_pair(e, e));
		}
		map<int, int>::iterator it = m.begin();

		while (it != m.end())
		{
			//it->first++;
			it->second++;
			std::cout << it->first << ":" << it->second << std::endl;
			++it;
		}
		std::cout << std::endl;
		for (auto e : m)
		{
			std::cout << e.first << ":" << e.second << std::endl;
		}
	}
	void TestMap2()
	{
		std::string arr[] = { "Æ»¹û","Ïã½¶","Àæ×Ó","Ïã½¶","Àæ×Ó","Æ»¹û","Ïã½¶","Ïã½¶","Àæ×Ó","Ïã½¶" };
		map<std::string, int> m;
		for (auto& e : arr)
		{
			m[e]++;
		}
		for (auto e:m)
		{
			std::cout << e.first << ":" << e.second << std::endl;
		}
	}
}

