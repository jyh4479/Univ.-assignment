#pragma once
#include <iostream>
#include <queue>
using namespace std;

template <typename K, typename E>
class Dictionary
{
public:
	virtual bool IsEmpty() const = 0;
	virtual pair<K, E> *Get(const K&) const = 0;
	virtual void Insert(const pair<K, E>&) = 0;
	virtual void Delete(const K k) = 0;
};

template <typename T>
class TreeNode
{
public:
	T data;
	TreeNode<T> *leftChild;
	TreeNode<T> *rightChild;
	TreeNode(T temp) :data(temp), leftChild(NULL), rightChild(NULL)
	{
	}
};

template <typename K, typename E>
class BST :public Dictionary<K, E>
{
private:
	TreeNode<pair<K, E>> *root;
public:

	void Insert(const pair<K, E> &thePair);
	pair<K, E> *Get(const K& k)const;
	pair<K, E> *Get(TreeNode<pair<K, E>>* p, const K & k)const;
	void Delete(const K k);

	void visit(TreeNode<pair<K, E>>* cur)
	{
		cout << "<" << cur->data.first << ", " << cur->data.second << ">" << endl;
	}
	BST() :root(NULL)
	{}
	bool IsEmpty() const
	{return (root == NULL);}
	void levelOrder();
};

template<typename K, typename E>
inline pair<K, E> *BST<K, E>::Get(const K & k)const
{
	return Get(root, k);
}

template<typename K, typename E>
inline pair<K, E> *BST<K, E>::Get(TreeNode<pair<K, E>>* p, const K & k)const
{ //program 5.18 
	if (!p) //if the node is not there
	{
		cout << "There is no node" << endl;
		return 0;
	}
	if (k < p->data.first) //if the key smaller
		return Get(p->leftChild, k);
	if (k > p->data.first) //if the key bigger
		return Get(p->rightChild, k);
	return &p->data;
}

template<typename K, typename E>
inline void BST<K, E>::Delete(const K k) // The function of delete
{
	TreeNode<pair<K, E>>*p = root, *q = 0;
	while (p && k != p->data.first)
	{
		q = p;
		if (k < p->data.first) p = p->leftChild;
		else p = p->rightChild;
	}

	if (p == 0) return;

	if (p->leftChild == 0 && p->rightChild == 0) //p is leaf
	{
		if (q == 0) root = 0;
		else if (q->leftChild == p) q->leftChild = 0;
		else q->rightChild = 0;
		delete p;
	}

	else if (p->leftChild == 0)// p only has right child
	{
		if (q == 0) root = p->rightChild;
		else if (q->leftChild == p) q->leftChild = p->rightChild;
		else q->rightChild = p->rightChild;
		delete p;
	}

	else if (p->rightChild == 0) // p only has left child
	{
		if (q == 0) root = p->leftChild;
		else if (q->leftChild == p) q->leftChild = p->leftChild;
		else q->rightChild = p->leftChild;
		delete p;
	}
	// p has left and right child;
	else
	{
		TreeNode<pair<K, E>>*prevprev = p, *prev = p->rightChild, *curr = p->rightChild->leftChild;

		while (curr)
		{
			prevprev = prev;
			prev = curr;
			curr = curr->leftChild;
		}

		p->data = prev->data;
		if (prevprev == p)prevprev->rightChild = prev->rightChild;
		else prevprev->leftChild = prev->rightChild;
		delete prev;
	}
}

/*template<typename K, typename E>
inline pair<K, E> *BST<K, E>::Get(const K & k)const
{ //program 5.19
	TreeNode<pair<K, E>> *currentNode = root;
	while (currentNode)
	{
		if (k < currentNode->data.first)
			currentNode = currentNode->leftChild;
		else if (k > currentNode->data.first)
			currentNode = currentNode->rightChild;
		else return &currentNode->data;
	}
	return 0;
}*/

template<typename K, typename E>
inline void BST<K, E>::Insert(const pair<K, E>& thePair)
{ //program 5.21
	TreeNode<pair<K, E>> *p = root, *pp = 0; //p 초기노드, pp 부모노드
	while (p)
	{
		pp = p;

		if (thePair.first < p->data.first)
			p = p->leftChild;
		else if (thePair.first > p->data.first)
			p = p->rightChild;

		else //if the key is equal
		{
			p->data.second = thePair.second;
			return;
		}
	}
	p = new TreeNode<pair<K, E>>(thePair);

	if (root)
	{
		// compare the p node and current
		if (thePair.first < pp->data.first)
			pp->leftChild = p;
		else
			pp->rightChild = p;
	}
	else
		root = p;
}

template<typename K, typename E>
inline void BST<K, E>::levelOrder() //The level order for showing
{
	queue<TreeNode<pair<K, E>>*> q;
	TreeNode<pair<K, E>> *currentNode = root;
	while (currentNode)
	{
		visit(currentNode);
		if (currentNode->leftChild) q.push(currentNode->leftChild);
		if (currentNode->rightChild) q.push(currentNode->rightChild);
		if (q.empty()) return;
		currentNode = q.front();
		q.pop();
	}
}