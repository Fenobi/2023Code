#pragma once

#include <iostream>
#include <string>

enum Colour
{
	RED,
	BLACK
};

template<class T>
struct RBTreeNode
{
	T _data;
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	Colour _col;

	RBTreeNode(const T& data)
		:_data(data),
		_left(nullptr),
		_right(nullptr),
		_parent(nullptr),
		_col(RED)
	{}
};

template<class T, class Ref, class Ptr>
struct __RBTreeIterator
{
	typedef RBTreeNode <T> Node;
	typedef __RBTreeIterator<T, Ref, Ptr> Self;
	typedef __RBTreeIterator<T, T&, T*> iterator;

	Node* _node;

	__RBTreeIterator(Node* node)
		:_node(node)
	{}
	// 普通迭代器的时候，它是拷贝构造
	// const迭代器的时候，它是构造，支持用普通迭代器构造const迭代器
	__RBTreeIterator(const iterator& s)
		:_node(s._node)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &_node->_data;
	}

	Self& operator++()
	{
		if (_node->_right)
		{
			Node* min = _node->_right;
			while (min->_left)
			{
				min = min->_left;
			}
			_node = min;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_right)
			{
				cur = cur->_parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	Self& operator--()
	{
		if (_node->_left)
		{
			Node* max = _node->_left;
			while (max->_right)
			{
				max = max->_right;
			}
			_node = max;
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_left)
			{
				cur = cur->_parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	bool operator!=(const Self& s) const
	{
		return _node != s._node;
	}

	bool operator==(const Self& s) const
	{
		return _node == s._node;
	}
};

template<class K, class T, class KeyOfT>
class RBTree
{
	typedef RBTreeNode <T> Node;
public:
	typedef __RBTreeIterator<T, T&, T*> iterator;
	typedef __RBTreeIterator<T, const T&, const T*> const_iterator;

	iterator begin()
	{
		Node* left = _root;
		while (left && left->_left)
		{
			left = left->_left;
		}
		return iterator(left);
	}

	iterator end()
	{
		return iterator(nullptr);
	}

	const_iterator begin() const
	{
		Node* left = _root;
		while (left && left->_left)
		{
			left = left->_left;
		}
		return const_iterator(left);
	}

	const_iterator end() const
	{
		return const_iterator(nullptr);
	}

	std::pair<iterator, bool> Insert(const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return std::make_pair(iterator(_root), true);
		}

		KeyOfT kot;
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kot(cur->_data) < kot(data))
			{
				parent = cur;
				cur = cur->_right;
			} 
			else if (kot(cur->_data) > kot(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return std::make_pair(iterator(cur), false);
			}
		}

		cur = new Node(data);
		Node* newNode = cur;
		cur->_col = RED;
		if (kot(parent->_data) < kot(data))
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				//情况一：uncle存在且为红
				if (uncle && uncle->_col == RED)
				{
					grandfather->_col = RED;
					parent->_col = uncle->_col = BLACK;

					cur = grandfather;
					parent = cur->_parent;
				}
				else //情况二|三
				{
					if (cur == parent->_left)
					{
						//情况二
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					} 
					else
					{
						//情况三
						RotateL(parent);
						RotateR(grandfather);
						grandfather->_col = RED;
						cur->_col = BLACK;
					}
					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				//情况一：uncle存在且为红
				if (uncle && uncle->_col == RED)
				{
					grandfather->_col = RED;
					parent->_col = uncle->_col = BLACK;

					cur = grandfather;
					parent = cur->_parent;
				}
				else //情况二|三
				{
					if (cur == parent->_right)
					{
						//情况二
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//情况三
						RotateR(parent);
						RotateL(grandfather);
						grandfather->_col = RED;
						cur->_col = BLACK;
					}
					break;
				}
			}
		}
		_root->_col = BLACK;
		return std::make_pair(iterator(newNode), true);
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}

		Node* ppNode = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;

		if (ppNode == nullptr)//注意头
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			// 头的头指向的左右
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}

		Node* ppNode = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;

		if (ppNode == nullptr)
		{
			_root = subL;
			_root->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}
	}

	void Inorder()
	{
		_Inorder(_root);
	}
	void _Inorder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_Inorder(root->_left);
		std::cout << root->_kv.first << ":" << root->_kv.second << std::endl;
		_Inorder(root->_right);
	}

	bool Check(Node* root, int blackNum, const int ref)
	{
		if (root == nullptr)
		{
			if (blackNum != ref)
			{
				return false;
				std::cout << "违反规则：本条路径黑色节点的数量和最左路径不相等" << std::endl;
			}
			return true;
		}

		if (root->_col == RED && root->_parent->_col == RED)
		{
			std::cout << "违反规则：出现连续红色节点" << std::endl;
			return false;
		}
		if (root->_col == BLACK)
		{
			++blackNum;
		}
		return Check(root->_left, blackNum, ref)
			&& Check(root->_right, blackNum, ref);
	}

	bool IsBalance()
	{
		if (_root == nullptr)
		{
			return true;
		}
		if (_root->_col != BLACK)
		{
			return false;
		}
		int ref = 0;
		Node* leftNode = _root;
		while (leftNode)
		{
			if (leftNode->_col == BLACK)
			{
				++ref;
			}
			leftNode = leftNode->_left;
		}
		return Check(_root, 0, ref);
	}

private:
	Node* _root = nullptr;
};