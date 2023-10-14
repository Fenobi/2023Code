#pragma once

#include "HashTable.hpp"

namespace fu
{
	template<class K, class V, class Hash = HashFunc<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const std::pair<const K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename bucketHash::HashTable<K, std::pair<K, V>, Hash, MapKeyOfT>::iterator iterator;
		typedef typename bucketHash::HashTable<K, std::pair<K, V>, Hash, MapKeyOfT>::const_iterator const_iterator;

		std::pair<iterator, bool> Insert(const std::pair<K, V>& data)
		{
			return _ht.Insert(data);
		}

		V& operator[](const K& key)
		{
			std::pair<iterator, bool> ret = _ht.Insert(std::make_pair(key, V()));
			return ret.first->second;
		}

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

		iterator Find(const K& key)
		{
			return _ht.Find(key);
		}

		bool Erase(const K& key)
		{
			return _ht.Erase(key);
		}
	private:
		bucketHash::HashTable<K, std::pair<K, V>, Hash, MapKeyOfT> _ht;
	};

	void Test_unordered_map()
	{
		unordered_map<std::string, int,HashFuncString> um;
		std::string arr[] = { "Æ»¹û","Ïã½¶","Àæ×Ó","Æ»¹û","Ïã½¶" ,"Àæ×Ó","Æ»¹û" ,"Ïã½¶","Àæ×Ó","Æ»¹û" ,"Ïã½¶","Àæ×Ó","Àæ×Ó","Àæ×Ó" };
		for (auto& e : arr)
		{
			um[e]++;
		}
		for (const auto& kv : um)
		{
			std::cout << kv.first << ":" << kv.second << std::endl;
		}
		um.Find("Æ»¹û");
		um.Erase("Æ»¹û");
	}
}