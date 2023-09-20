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

	int _bf;// balance factor(平衡因子)

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
		// 1、更新平衡因子
		while (parent) 
		{
			// 新增在右，parent->bf++;
			// 新增在左，parent->bf--;
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}

			// 是否继续更新依据：子树的高度是否变化
			// 1、parent->_bf == 0 说明之前的parent->_bf是1或者-1
			// 说明之前parent一边高一边低，这次插入填上矮的那边，parent所在子树高度不变，不需要继续往上更新
			// 2、parent->_bf == 1或-1，说明之前的parent->_bf是0，
			// 3、parent->_bf == 2或-2，说明之前parent->_bf == 1或-1，现在插入严重不平衡，违反规则
			// 就地处理 -- 旋转

			// 旋转：
			// 1、让这颗子树高度差不超过1
			// 2、旋转过程中继续保持他是搜索树
			// 3、更新调整孩子节点的平衡因子
			// 4、让这棵子树的高度根插入前保持一致

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
				// 旋转
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateR(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)//左右旋
				{
					RotateLR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)//左右旋
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

		if (bf == -1) //subLR左子树新增
		{
			subL->_bf = 0;
			parent->_bf = 1;
			subLR->_bf = 0;
		}
		else if (bf == 1) //subLR右子树新增
		{
			subL->_bf = -1;
			parent->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == 0) //subLR自己新增
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

		if (bf == -1) //subRL左子树新增
		{
			subR->_bf = 1;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == 1) //subRL右子树新增
		{
			subR->_bf = 0;
			parent->_bf = -1;
			subRL->_bf = 0;
		}
		else if (bf == 0) //subRL自己新增
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
			std::cout << root->_kv.first << ":平衡因子异常" << std::endl;
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

