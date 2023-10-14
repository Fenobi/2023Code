#pragma once

#include <iostream>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#include <string>
#include <ctime>
#include <vector>

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

struct HashFuncString
{
	size_t operator()(const std::string& key)
	{
		size_t hash = 0;
		for (auto ch : key)
		{
			hash *= 31;
			hash += ch;
		}
		return hash;
	}
};


namespace closeHash
{
	enum State
	{
		EMPTY,
		EXIST,
		DELETE
	};

	template<class K, class V>
	struct HashData
	{
		std::pair<K, V> _kv;
		State _state = EMPTY;
	};

	template<class K, class V, class Hash = HashFunc<K>>
	class HashTable
	{
		typedef HashData<K, V> Data;
	public:
		HashTable()
		:_n(0)
		{
			_tables.resize(10);
		}

		bool Insert(const std::pair<K, V>& kv)
		{
			if (Find(kv.first))
				return false;
			
			if (_n * 10 / _tables.size() >= 7)
			{
				HashTable<K, V, Hash> newHT;
				newHT._tables.resize(_tables.size() * 2);
				for (auto& e : _tables)
				{
					newHT.Insert(e._kv);
				}
				_tables.swap(newHT._tables);
			}

			Hash hf;
			size_t hashi = hf(kv.first) % _tables.size();
			while (_tables[hashi]._state == EXIST)
			{
				// 线性探测
				++hashi;
				hashi %= _tables.size();
			}

			_tables[hashi]._kv = kv;
			_tables[hashi]._state = EXIST;
			++_n;

			return true;
		}

		Data* Find(const K& key)
		{
			Hash hf;
			size_t hashi = hf(key) % _tables.size();
			while (_tables[hashi]._state != EMPTY)
			{
				if (_tables[hashi]._state == EXIST 
					&& _tables[hashi]._kv.first == key)
				{
					return &_tables[hashi];
				}
				++hashi;
				hashi %= _tables.size();
			}
			return nullptr;
		}

		bool Erase(const K& key)
		{
			Data* ret = Find(key);
			if (ret)
			{
				ret->_state = DELETE;
				--_n;
				return true;
			}
			else
			{
				return false;
			}
		}

	private:
		std::vector<Data> _tables;
		size_t _n = 0; // 表中存储的有效数据的个数
	};

	void TestHT1()
	{
		HashTable<int, int> ht;
		int a[] = { 18,8,7,27,57,3,38 };
		for (auto e : a)
		{
			ht.Insert(std::make_pair(e, e));
		}
		ht.Insert(std::make_pair(17, 17));
		ht.Insert(std::make_pair(5, 5));
		ht.Insert(std::make_pair(15, 15));

		std::cout << ht.Find(7) << std::endl;
		std::cout << ht.Find(27) << std::endl;
		std::cout << ht.Find(57) << std::endl;
		ht.Erase(27);
		std::cout << ht.Find(27) << std::endl;
		std::cout << ht.Find(57) << std::endl;
	}

	void TestHT2()
	{
		HashTable<std::string, int, HashFuncString> ht;
		std::string arr[] = { "苹果","香蕉","梨子","苹果","香蕉" ,"梨子","苹果" ,"香蕉","梨子","苹果" };
		for (auto& e : arr)
		{
			HashData<std::string, int>* ret = ht.Find(e);
			if (ret)
			{
				ret->_kv.second++;
			}
			else
			{
				ht.Insert(std::make_pair(e, 1));
			}
		}
		std::cout << ht.Find("苹果") << std::endl;
		std::cout << ht.Find("香蕉") << std::endl;
		std::cout << ht.Find("梨子") << std::endl;
		ht.Erase("梨子");
		std::cout << ht.Find("梨子") << std::endl;
		std::cout << ht.Find("香蕉") << std::endl;
	}
}

namespace bucketHash
{
	template<class K, class V>
	struct HashNode
	{
		std::pair<K, V> _kv;
		HashNode<K, V>* _next;

		HashNode(const std::pair<K, V>& kv)
			:_kv(kv)
			, _next(nullptr)
		{}
		
	};
	template<class K, class V, class Hash = HashFunc<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		HashTable()
			:_n(0)
		{
			_tables.resize(10);
		}

		HashTable(const HashTable<K, V, Hash>& ht)
		{
			_n = 0;
			_tables.resize(10);
			for (size_t i = 0; i < ht._tables.size(); ++i)
			{
				Node* cur = ht._tables[i];
				while (cur)
				{
					Insert(cur->_kv);
					cur = cur->_next;
				}
			}
		}

		/*HashTable<K, V, Hash>& operator=(const HashTable<K, V, Hash>& ht)
		{
			HashTable<K, V, Hash> tmp;
			std::swap(tmp, ht);
			return tmp;
			
		}*/

		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}

		bool Insert(const std::pair<K, V>& kv)
		{
			if (Find(kv.first))
				return false;
			// 负载因子为1
			if (_tables.size() == _n)
			{
				std::vector<Node*> newTalbe;
				newTalbe.resize(2 * _tables.size(), nullptr);
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						size_t hashi = Hash()(cur->_kv.first) % newTalbe.size();
						// 头插到新表
						cur->_next = newTalbe[hashi];
						newTalbe[hashi] = cur;

						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newTalbe);
				/*HashTable<K, V, Hash> newHT;
				newHT._tables.resize(_tables.size() * 2);

				for (auto cur : _tables)
				{
					while (cur)
					{
						newHT.Insert(cur->_kv);
						cur = cur->_next;
					}
				}
				_tables.swap(newHT._tables);*/

			}
			size_t hashi = Hash()(kv.first) % _tables.size();
			// 头插
			Node* newnode = new Node(kv);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;
			return true;
		}

		Node* Find(const K& key)
		{
			size_t hashi = Hash()(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
				{ 
					return cur;
				}
				else
				{
					cur = cur->_next;
				}
			}
			return nullptr;
		}

		bool Erase(const K& key)
		{
			size_t hashi = Hash()(key) % _tables.size();
			Node* cur = _tables[hashi];
			Node* prev = cur;
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (cur == _tables[hashi])
					{
						_tables[hashi] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}
					delete cur;
					--_n;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
			return false;
		}
	private:
		std::vector<Node*> _tables;
		size_t _n = 0;
	};
	void TestHT1()
	{
		HashTable<int, int> ht;
		int a[] = { 18,8,7,27,57,3,38,1 };
		for (auto e : a)
		{
			ht.Insert(std::make_pair(e, e));
		}
		ht.Insert(std::make_pair(17, 17));
		ht.Insert(std::make_pair(5, 5));
		ht.Erase(17);
		ht.Erase(57);
		ht.Erase(27);
		ht.Erase(7);
		ht.Insert(std::make_pair(15, 15));

	}

	void TestHT2()
	{
		HashTable<std::string, int, HashFuncString> ht;
		std::string arr[] = { "苹果","香蕉","梨子","苹果","香蕉" ,"梨子","苹果" ,"香蕉","梨子","苹果" };
		for (auto& e : arr)
		{
			HashNode<std::string, int>* ret = ht.Find(e);
			if (ret)
			{
				ret->_kv.second++;
			}
			else
			{
				ht.Insert(std::make_pair(e, 1));
			}
		}
		HashTable<std::string, int, HashFuncString> ht1(ht);
	//	ht1 = ht;
		std::cout << ht.Find("苹果") << std::endl;
		std::cout << ht.Find("香蕉") << std::endl;
		std::cout << ht.Find("梨子") << std::endl;
		ht.Erase("梨子");
		std::cout << ht.Find("梨子") << std::endl;
		std::cout << ht.Find("香蕉") << std::endl;
	}
}