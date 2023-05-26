#pragma once

#include <iostream>

using namespace std;

template<class K>
struct BSTreeNode
{
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;

	BSTreeNode<K>(const K& key)
	:_left(nullptr)
	,_right(nullptr)
	,_key(key)
	{}
};

template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	BSTree()
		:_root(nullptr)
	{}

	BSTree(const BSTree<K>& t)
	{
		_root = Copy(t._root);
	}
	
	BSTree<K>& operator=(BSTree<K> t)
	{
		swap(_root, t._root);
		return *this;
	}

	~BSTree()
	{
		Destory(_root);
		_root = nullptr;
	}
	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(key);
		if (parent->_key < key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}

		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
	}

	bool Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	bool Erase(const K& key)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				// 1、左为空
				// 2、右为空
				// 3、左右都不为空，替换删除
				if (cur->_left == nullptr)//左为空
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;
						}
					}

					delete cur;
				}
				else if (cur->_right == nullptr)//右为空
				{
					if (_root == cur)
					{
						_root = cur->_left;
					}
					else
					{
						if (parent->_left = cur)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
					delete cur;
				}
				else//左右都不为空
				{
					Node* parent = cur;//注意不能是nullptr
					Node* minRight = cur->_right;
					while (minRight->_left)
					{
						parent = minRight;
						minRight = minRight->_left;
					}
					cur->_key = minRight->_key;
					if(minRight==parent->_left)//注意要判断
					{
						parent->_left = minRight->_right;
					}
					else
					{
						parent->_right = minRight->_right;

					}
					delete minRight;

				}

				return true;
			}
		}

		return false;
	}

	bool FindR(const K& key)
	{
		return _FindR(_root, key);
	}

	bool InsertR(const K& key)//注意加&
	{
		return _InsertR(_root, key);
	}

	bool EraseR(const K& key)
	{
		return _EraseR(_root, key);
	}

private:
	Node* Copy(Node* root)//前序构建
	{
		if (root == nullptr)
			return nullptr;
		
		Node* newRoot = new Node(root->_key);
		newRoot->_left = Copy(root->_left);
		newRoot->_right = Copy(root->_right);

		return newRoot;
	}

	void Destory(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		Destory(root->_left);
		Destory(root->_right);
		delete root;
	}

	bool _EraseR(Node*& root, const K& key)
	{
		if (root==nullptr)
		{
			return false;
		}
		if (root->_key < key)
		{
			return _EraseR(root->_right, key);
		}
		else if (root->_key > key)
		{
			return _EraseR(root->_left, key);
		}
		else
		{
			Node* del = root;
			if (root->_right == nullptr)
			{
				root = root->_left;
			}
			else if (root->_left == nullptr)
			{
				root = root->_right;
			}
			else
			{
				Node* minRight = root->_right;
				while (minRight->_left)
				{
					minRight = minRight->_left;
				}

				swap(root->_key, minRight->_key);
				
				return _EraseR(root->_right, key);
			}
			delete del;

			return true;
		}

	}

	bool _FindR(Node* root, const K& key)
	{
		if (root == nullptr)
			return false;

		if (root->_key < key)
			return _FindR(root->_right, key);
		else if (root->_key > key)
			return _FindR(root->_left, key);
		else
			return true;

	}

	bool _InsertR(Node*& root, const K& key)//注意加&
	{
		if (root == nullptr)
		{
			root = new Node(key);
			return true;
		}

		if (root->_key < key)
			return _InsertR(root->_right, key);
		else if (root->_key > key)
			return _InsertR(root->_left, key);
		else
			return false;
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	Node* _root = nullptr;
};

void BSTreeTest1()
{
	int n[] = { 8,5,4,9,3,2,7,6,1 };
	BSTree<int> bst;
	for (auto e : n)
	{
		bst.Insert(e);
	}
	bst.InOrder();
	cout << endl;
	cout << bst.Find(9) << endl;
	cout << bst.Find(1) << endl;
	cout << bst.Find(22) << endl;
	cout << bst.Find(93) << endl;
}

void BSTreeTest2()
{
	int n[] = { 8,3,1,10,6,4,7,14,13 };
	BSTree<int> bst;
	for (auto e : n)
	{
		bst.Insert(e);
	}
	for (auto e : n)
	{
		bst.Erase(e);
		bst.InOrder();
		cout << endl;
	}
	//bst.InOrder();
	//cout << endl;
	////bst.Erase(3);
	//bst.Erase(8);
	//cout << endl; 
	//bst.InOrder();
}

void BSTreeTest3()
{
	int n[] = { 8,5,4,9,3,2,7,6,1 };
	BSTree<int> bst;
	for (auto e : n)
	{
		bst.InsertR(e);
	}
	bst.InOrder();
	cout << bst.FindR(9) << endl;
	cout << bst.FindR(8) << endl;
	cout << bst.FindR(23) << endl;
	cout << bst.FindR(22) << endl;
}

void BSTreeTest4()
{
	int n[] = { 8,3,1,10,6,4,7,14,13 };
	BSTree<int> bst;
	for (auto e : n)
	{
		bst.InsertR(e);
	}
	/*for (auto e : n)
	{
		bst.EraseR(e);
		bst.InOrder();
		cout << endl;
	}*/
	bst.InOrder();
	cout << endl;
	//bst.Erase(3);
	bst.EraseR(8);
	cout << endl; 
	bst.InOrder();
	bst.InsertR(8);
	cout << endl;
	bst.InOrder();
}

void BSTreeTest5()
{
	int n[] = { 8,3,1,10,6,4,7,14,13 };
	BSTree<int> bst;
	for (auto e : n)
	{
		bst.Insert(e);
	}
	bst.InOrder();
	cout << endl;
	BSTree<int> bst1(bst);
	bst1.InOrder();
	cout << endl;
	BSTree<int> bst2 = bst1;
	bst2.InOrder();
	cout << endl;

}