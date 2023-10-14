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
			size_t starti = hashi;
			while (_tables[hashi]._state != EMPTY)
			{
				if (_tables[hashi]._state == EXIST 
					&& _tables[hashi]._kv.first == key)
				{
					return &_tables[hashi];
				}
				++hashi;
				hashi %= _tables.size();

				//极端场景下没有空，全是存在或者删除状态
				if (hashi == starti)
				{
					break;
				}
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
	template<class T>
	struct HashNode
	{
		//std::pair<K, V> _kv;
		T _data;
		HashNode<T>* _next;

		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
		
	};
	// 前置声明
	template<class K, class T, class Hash, class KeyOfT>
	class HashTable;

	template<class K, class T, class Ref, class Ptr, class Hash, class KeyOfT>
	struct const_HTIterator;

	template<class K, class T,class Ref, class Ptr, class Hash, class KeyOfT>
	struct __HTIterator
	{
		typedef HashNode<T> Node;
		typedef __HTIterator<K, T, Ref, Ptr, Hash, KeyOfT> iterator;
		typedef const_HTIterator<K, T, Ref, Ptr, Hash, KeyOfT> const_iterator;

		typedef HashTable<K, T, Hash, KeyOfT> HT;

		Node* _node;
		HT* _ht;
		
		__HTIterator(Node* node, HT* ht)
			:_node(node),
			_ht(ht)
		{}

		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}

		bool operator != (const iterator& s) const
		{
			return _node != s._node;
		}
		
		iterator& operator++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				// 当前桶走完了，要找下一个桶的第一个
				KeyOfT kot;
				Hash hash;
				
				size_t hashi = hash(kot(_node->_data)) % _ht->_tables.size();
				++hashi;
				
				while (hashi < _ht->_tables.size())
				{
					if (_ht->_tables[hashi])
					{
						_node = _ht->_tables[hashi];
						break;
					}
					else
					{
						++hashi;
					}
				}
				// 后面没有桶了
				if (hashi == _ht->_tables.size())
					_node = nullptr;	
			}
			return *this;
		}
	};

	template<class K, class T, class Ref, class Ptr, class Hash, class KeyOfT>
	struct const_HTIterator
	{
		typedef HashNode<T> Node;
		typedef __HTIterator<K, T, Ref, Ptr, Hash, KeyOfT> iterator;
		typedef const_HTIterator<K, T, Ref, Ptr, Hash, KeyOfT> const_iterator;

		typedef HashTable<K, T, Hash, KeyOfT> HT;

		const Node* _node;
		const HT* _ht;

		const_HTIterator(const Node* node, const HT* ht)
			:_node(node),
			_ht(ht)
		{}

		Ref operator*() const
		{
			return _node->_data;
		}

		Ptr operator->() const
		{
			return &_node->_data;
		}

		bool operator != (const const_iterator& s) const
		{
			return _node != s._node;
		}

		const_iterator& operator ++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				// 当前桶走完了，要找下一个桶的第一个
				KeyOfT kot;
				Hash hash;

				size_t hashi = hash(kot(_node->_data)) % _ht->_tables.size();
				++hashi;

				while (hashi < _ht->_tables.size())
				{
					if (_ht->_tables[hashi])
					{
						_node = _ht->_tables[hashi];
						break;
					}
					else
					{
						++hashi;
					}
				}
				// 后面没有桶了
				if (hashi == _ht->_tables.size())
					_node = nullptr;
			}
			return *this;
			
		}
	};

	template<class K, class T, class Hash, class KeyOfT>
	class HashTable
	{
		typedef HashNode<T> Node;

		template<class K, class T, class Ref, class Ptr, class Hash, class KeyOfT>
		friend struct __HTIterator;

		template<class K, class T, class Ref, class Ptr, class Hash, class KeyOfT>
		friend struct const_HTIterator;

	public:
		typedef __HTIterator<K, T, T&, T*, Hash, KeyOfT> iterator;
		typedef const_HTIterator<K, T, const T&, const T*, Hash, KeyOfT> const_iterator;

		iterator begin()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				if (_tables[i])
				{
					return iterator(_tables[i], this);
				}
			}

			return iterator(nullptr, this);
		}

		iterator end()
		{
			return iterator(nullptr, this);
		}

		const_iterator begin() const
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				if (_tables[i])
				{
					return const_iterator(_tables[i], this);
				}
			}

			return const_iterator(nullptr, this);
		}

		const_iterator end() const
		{
			return const_iterator(nullptr, this);
		}

		HashTable()
			:_n(0)
		{
			_tables.resize(10);
		}

		HashTable(const HashTable<K, T, Hash, KeyOfT>& ht)
		{
			KeyOfT kot;
			_n = 0;
			_tables.resize(10);
			for (size_t i = 0; i < ht._tables.size(); ++i)
			{
				Node* cur = ht._tables[i];
				while (cur)
				{
					Insert(kot(cur->_data));
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

		std::pair<iterator, bool> Insert(const T& data)
		{
			KeyOfT kot;

			iterator it = Find(kot(data));
			if (it != end())
				return std::make_pair(it, false);
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
						size_t hashi = Hash()(kot(cur->_data)) % newTalbe.size();
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
			size_t hashi = Hash()(kot(data)) % _tables.size();
			// 头插
			Node* newnode = new Node(data);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;
			return std::make_pair(iterator(newnode, this), true);
		}

		iterator Find(const K& key)
		{
			KeyOfT kot;
			size_t hashi = Hash()(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{ 
					return iterator(cur, this);
				}
				else
				{
					cur = cur->_next;
				}
			}
			return end();
		}

		bool Erase(const K& key)
		{
			KeyOfT kot;
			size_t hashi = Hash()(key) % _tables.size();
			Node* cur = _tables[hashi];
			Node* prev = cur;
			while (cur)
			{
				if (kot(cur->_data) == key)
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

	//void TestHT1()
	//{
	//	HashTable<int, int> ht;
	//	int a[] = { 18,8,7,27,57,3,38,1 };
	//	for (auto e : a)
	//	{
	//		ht.Insert(std::make_pair(e, e));
	//	}
	//	ht.Insert(std::make_pair(17, 17));
	//	ht.Insert(std::make_pair(5, 5));
	//	ht.Erase(17);
	//	ht.Erase(57);
	//	ht.Erase(27);
	//	ht.Erase(7);
	//	ht.Insert(std::make_pair(15, 15));

	//}

	//void TestHT2()
	//{
	//	HashTable<std::string, int, HashFuncString> ht;
	//	std::string arr[] = { "苹果","香蕉","梨子","苹果","香蕉" ,"梨子","苹果" ,"香蕉","梨子","苹果" };
	//	for (auto& e : arr)
	//	{
	//		HashNode<std::string, int>* ret = ht.Find(e);
	//		if (ret)
	//		{
	//			ret->_kv.second++;
	//		}
	//		else
	//		{
	//			ht.Insert(std::make_pair(e, 1));
	//		}
	//	}
	//	HashTable<std::string, int, HashFuncString> ht1(ht);
	////	ht1 = ht;
	//	std::cout << ht.Find("苹果") << std::endl;
	//	std::cout << ht.Find("香蕉") << std::endl;
	//	std::cout << ht.Find("梨子") << std::endl;
	//	ht.Erase("梨子");
	//	std::cout << ht.Find("梨子") << std::endl;
	//	std::cout << ht.Find("香蕉") << std::endl;
	//}
}