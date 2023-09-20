#pragma once

#include <iostream>
#include <ctime>

enum Colour
{
	RED,
	BLACK
};

template<class K,class V>
struct RBTreeNode
{
	std::pair<K, V> _kv;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	Colour _col;

	RBTreeNode(const std::pair<K, V>& kv)
		:_kv(kv),
		_left(nullptr),
		_right(nullptr),
		_parent(nullptr),
		_col(RED)
	{}
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode <K, V> Node;
public:
	bool Insert(const std::pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			} 
			else if(cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(kv);
		cur->_col = RED;
		if (parent->_kv.first < kv.first)
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
		return true;
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

void TestRBTree()
{
	int a[] = { 8,3,1,10,6,4,7,14,13 };
	//int a[] = { 16,3,7,11,9,26,18,14,15 };
	//int a[] = { 4,2,6,1,3,55,15,7,16,14 };
	RBTree<int, int> rb;

	for (auto e : a)
	{
		rb.Insert(std::make_pair(e, e));
	}
	
	rb.Inorder();
	std::cout << rb.IsBalance() << std::endl;
}

void TestRBTree1()
{
	srand(time(0));
	const size_t N = 10000;
	RBTree<int, int> rb;
	for (int i = 0; i < N; ++i)
	{
		int x = rand();
		rb.Insert(std::make_pair(x, x));
		/*if (!rb.IsBalance())
		{
			std::cout << "error" << std::endl;
			break;
		}*/
	}
	rb.Inorder();
	std::cout << rb.IsBalance() << std::endl;
}