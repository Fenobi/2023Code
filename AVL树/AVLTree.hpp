#pragma once

#include <iostream>
#include <assert.h>
#include <time.h>

template<class K, class V>
struct AVLTreeNode
{
	std::pair<K, V> _kv;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	int _bf;// balance factor(ƽ������)

	AVLTreeNode(const std::pair<K, V>& kv)
		:_kv(kv),
		_left(nullptr),
		_right(nullptr),
		_parent(nullptr),
		_bf(0) 
	{}
	
};

template<class K, class V>
struct AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool Insert(const std::pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		
		Node* parent = nullptr;
		Node* cur = _root;

		while (cur)
		{
			if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(kv);
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
		// 1������ƽ������
		while (parent) 
		{
			// �������ң�parent->bf++;
			// ��������parent->bf--;
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}

			// �Ƿ�����������ݣ������ĸ߶��Ƿ�仯
			// 1��parent->_bf == 0 ˵��֮ǰ��parent->_bf��1����-1
			// ˵��֮ǰparentһ�߸�һ�ߵͣ���β������ϰ����Ǳߣ�parent���������߶Ȳ��䣬����Ҫ�������ϸ���
			// 2��parent->_bf == 1��-1��˵��֮ǰ��parent->_bf��0��
			// 3��parent->_bf == 2��-2��˵��֮ǰparent->_bf == 1��-1�����ڲ������ز�ƽ�⣬Υ������
			// �͵ش��� -- ��ת

			// ��ת��
			// 1������������߶Ȳ����1
			// 2����ת�����м�����������������
			// 3�����µ������ӽڵ��ƽ������
			// 4������������ĸ߶ȸ�����ǰ����һ��

			if (parent->_bf ==0)
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				// ��ת
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateR(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)//������
				{
					RotateLR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)//������
				{
					RotateRL(parent);
				}
				else
				{
					assert(false);
				}
				break;
			}
			else
			{
				assert(false);
			}
		}

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

		if (ppNode == nullptr)//ע��ͷ
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			// ͷ��ͷָ�������
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
		
		parent->_bf = subR->_bf = 0;
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
		subL->_bf = parent->_bf = 0;
	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		if (bf == -1) //subLR����������
		{
			subL->_bf = 0;
			parent->_bf = 1;
			subLR->_bf = 0;
		}
		else if (bf == 1) //subLR����������
		{
			subL->_bf = -1;
			parent->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == 0) //subLR�Լ�����
		{
			subL->_bf = 0;
			parent->_bf = 0;
			subLR->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);

		if (bf == -1) //subRL����������
		{
			subR->_bf = 1;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == 1) //subRL����������
		{
			subR->_bf = 0;
			parent->_bf = -1;
			subRL->_bf = 0;
		}
		else if (bf == 0) //subRL�Լ�����
		{
			subR->_bf = 0;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
		else
		{
			assert(false);
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

	int Height(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		int lh = Height(root->_left);
		int rh = Height(root->_right);

		return lh > rh ? lh + 1 : rh + 1;
	}

	bool IsBalance()
	{
		return IsBalance(_root);
	}

	bool IsBalance(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}

		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);

		if (rightHeight - leftHeight != root->_bf)
		{
			std::cout << root->_kv.first << ":ƽ�������쳣" << std::endl;
			return false;
		}

		return abs(rightHeight - leftHeight) < 2
			&& IsBalance(root->_left)
			&& IsBalance(root->_right);
	}
private:
	Node* _root = nullptr;
};

void TestAVLTree()
{
	int a[] = { 8,3,1,10,6,4,7,14,13 };

	AVLTree<int, int> avl;
	for (auto e : a)
	{
		avl.Insert(std::make_pair(e, e));
		avl.IsBalance();
	}
	avl.Inorder();
	std::cout << avl.IsBalance() << std::endl;
}

void TestAVLTree1()
{
	srand(time(0));
	const size_t N = 10000;
	AVLTree<int, int> avl;
	for (int i=0;i<N;++i)
	{
		int x = rand();
		avl.Insert(std::make_pair(x, x));
	}
	avl.Inorder();
	std::cout << avl.IsBalance() << std::endl;
}

