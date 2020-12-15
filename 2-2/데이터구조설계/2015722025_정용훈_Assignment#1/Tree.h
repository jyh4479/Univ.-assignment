#pragma once
#include<stack> //Declare STL of stack
#include<queue> //Declare STL of queue
using namespace std;

template<class T> class Tree; //a forward declaration
template<class T> class InorderIterator; //a forward declaration

template<class T> //Declare template
class TreeNode //Declare class
{
	friend class Tree<T>; //For using other private member
	friend class InorderIterator<T>; //For using other private member
private:
	T data; // For saving data
	TreeNode<T>* leftChild; //For saving ohter Node's address
	TreeNode<T>* rightChild; //For saving ohter Node's address
public:
	TreeNode(T data=0,TreeNode* leftChild=NULL,TreeNode* rightChild=NULL)//constructor
	{ 
		this->data = data;
		this->leftChild = leftChild;
		this->rightChild = rightChild;
	};
};

template<class T>
class Tree //Declare class
{
private:
	TreeNode<T>* root = NULL; //Declare the root of binary tree
public:
	Tree(T data = 0)
	{
		root = new TreeNode<T>(data);//constructor
	};

	void buildTree() //The function of building Tree
	{
		root->leftChild = new TreeNode<T>(2,new TreeNode<T>(4,new TreeNode<T>(8),new TreeNode<T>(9)),new TreeNode<T>(5,new TreeNode<T>(10),new TreeNode<T>(11)));
		root->rightChild = new TreeNode<T>(3,new TreeNode<T>(6),new TreeNode<T>(7));
	}

	TreeNode<T>* getRoot() //The function for using information of root
	{
		return root;
	}

	void visit(TreeNode<T>* current) //For printing data
	{
		cout << current->data << " ";
	}

	//traveling functions
	void inorder(); 
	void inorder(TreeNode<T>* current); 
	void preorder();
	void preorder(TreeNode<T>*current);
	void postorder(); 
	void postorder(TreeNode<T>*current); 
	void nonrecInorder(); 
	void levelOrder(); 
};

template<class T>
class InorderIterator
{
private:
	stack<TreeNode<T>*> s;
	TreeNode<T>*currentNode;
public:
	InorderIterator(Tree<T>* tree)
	{
		currentNode = tree->getRoot();
	}
	T *Next();
};

template <class T>
T* InorderIterator<T>::InorderIterator::Next()
{
	while (currentNode)
	{//Move the information of the node to the leftmost position
		s.push(currentNode);
		currentNode = currentNode->leftChild;
	}

	if (s.empty()) return 0;
	currentNode = s.top();
	s.pop();
	T& temp = currentNode->data;
	currentNode = currentNode->rightChild;
	if (temp == NULL && s.empty())
		return &temp;
}

	// preorder Current - Left - Right
template<class T>
void Tree<T>::preorder()
{
	preorder(root);
}
template<class T>
void Tree<T>::preorder(TreeNode<T>* current)
{
	if (current != NULL) 
	{
		visit(current);
		preorder(current->leftChild);
		preorder(current->rightChild);
	}
}

// inorder Left - Current - Right
template<class T>
void Tree<T>::inorder()
{
	inorder(root);
}
template<class T>
inline void Tree<T>::inorder(TreeNode<T>* current)
{
	if (current != NULL)
	{
		inorder(current->leftChild);
		visit(current);
		inorder(current->rightChild);
	}
}

// postorder Left - Right - Current
template<class T>
void Tree<T>::postorder()
{
	postorder(root);
}
template<class T>
void Tree<T>:: postorder(TreeNode<T>* current)
{
	if (current != NULL) 
	{
		postorder(current->leftChild);
		postorder(current->rightChild);
		visit(current);
	}
}

//nonrecInorder
template<class T>
void Tree<T>::nonrecInorder()
{
	stack<TreeNode<T>*> s;
	TreeNode<T> *currentNode = root;
	while (1)
	{
		while (currentNode)
		{
			s.push(currentNode);
			currentNode = currentNode->leftChild;
		}
		if (s.empty()) return;
		currentNode = s.top();
		s.pop();
		visit(currentNode);
		currentNode = currentNode->rightChild;
	}
}

//levelOrder
template<class T>
void Tree<T>::levelOrder()
{
	queue<TreeNode<T>*> q;
	TreeNode<T> *currentNode = root;
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
