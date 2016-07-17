#pragma once

enum Colour{
	RED,
	BLACK,
};

template<class K,class V>
struct RBTreeNode{
	RBTreeNode<K,V> *_right;
	RBTreeNode<K,V> *_left;
	RBTreeNode<K,V> *_parent;

    K _key;
	V _value;

	Colour _col;

	RBTreeNode(const K &key,const V &value,Colour col = RED)
		:_right(NULL)
		,_left(NULL)
		,_parent(NULL)
		,_key(key)
		,_value(value)
		,_col(col)
	{}
};

template<class K,class V>
class RBTree{
	typedef RBTreeNode<K,V> Node;
public:
	RBTree()
		:_root(NULL)
	{}

	bool Insert(const K &key,const V &value)
	{
		//1.树为空
		if(_root == NULL)
		{
			_root = new Node(key,value,BLACK);
			return true;
		}
		//2.树不为空，找正确位置
		Node *parent = NULL;
		Node *cur = _root;
		while(cur)
		{
			if(cur->_key > key)
			{
				parent  = cur;
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				parent  = cur;
				cur = cur->_right;
			}
			else 
				return false;
		}
		cur = new Node(key,value,RED);
		if(key > parent->_key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		//3.调整
		bool isRotate = false;
		Node *ppNode = NULL;
		while(cur != _root && parent->_col == RED)
		{
			Node *grandfather = parent->_parent;
			if(parent == grandfather->_left)
			{
				Node *uncle = grandfather->_right;
				if(uncle && uncle->_col == RED)  //case1
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else   //case2 || case3
				{
					if(cur == parent->_right)     //case3->case2
					{
						_RotateL(parent);
						swap(cur,parent);
					}
						grandfather->_col = RED;   //case2
						parent->_col = BLACK;
						_RotateR(grandfather);
				}
			}
			else
			{
				Node *uncle = grandfather->_left;

				if(uncle && uncle->_col == RED)  //case1
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if(cur == parent->_left)  //case3->case2
					{	
						_RotateR(parent);
						swap(cur,parent);
					}

						grandfather->_col = RED;
						parent->_col = BLACK;	
						_RotateL(grandfather);
				}
			}
		}
		_root->_col = BLACK;

	}
	bool IsBalance()
	{

	}
	void InOrder()
	{
		_InOrder(_root);
	}
protected:
	void _InOrder(Node *root)
	{
		if(root == NULL)
			return;

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}
	void _RotateL(Node *& parent)
	{
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		
		parent->_right = subRL;
		if(subRL != NULL)
			subRL->_parent = parent;

		subR->_left = parent;
		subR->_parent = parent->_parent;
		parent->_parent = subR;

		if(subR->_parent == NULL)
			_root = subR;
		else
		{
			if(subR->_key < subR->_parent->_key)
				subR->_parent->_left = subR;
			else
				subR->_parent->_right = subR;
		}

	}
	void _RotateR(Node *& parent)
	{
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		
		parent->_left = subLR;
		if(subLR != NULL)
			subLR->_parent = parent;

		subL->_right = parent;
		subL->_parent = parent->_parent;
		parent->_parent = subL;

		if(subL->_parent == NULL)
			_root = subL;
		else
		{
			if(subL->_key < subL->_parent->_key)
				subL->_parent->_left = subL;
			else
				subL->_parent->_right = subL;
		}
	}
private:
	Node *_root;
};