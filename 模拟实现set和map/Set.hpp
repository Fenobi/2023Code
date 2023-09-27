#pragma once

#include "RBTree.hpp"

namespace fu
{
	template<class K>
	class set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename RBTree<K, K, SetKeyOfT>::const_iterator iterator;
		typedef typename RBTree<K, K, SetKeyOfT>::const_iterator const_iterator;
		
		iterator begin() const
		{
			return _t.begin();
		}

		iterator end() const
		{
			return _t.end();
		}

		std::pair<iterator, bool> Insert(const K& key)
		{
			std::pair<typename RBTree<K, K, SetKeyOfT>::iterator, bool> ret = _t.Insert(key);
			return std::pair<iterator, bool>(ret.first, ret.second);
		}

	private:
		RBTree<K, K, SetKeyOfT> _t;
	};
	void TestSet1()
	{
		int a[] = { 4,2,6,1,3,5,15,17,16,14 };
		set<int> s;
		for (auto e : a)
		{
			s.Insert(e);
		}
		set<int>::iterator it = s.begin();
		
		while (it != s.end())
		{
			std::cout << *it << " ";
			++it;
		}
		for (auto e : s)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}
}

