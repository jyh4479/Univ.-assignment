#include "CarBST.h"
#include <queue>
#include <stack>

CarBST::CarBST()//constructor
{
}
	
CarBST::~CarBST()//destructor
{
	exit(root); //The function for delete
	/* You must fill here */
}

void CarBST::Insert(CarNode * node)
{ //For inserting car Node
	CarNode*p = root, *pp = 0;
	while (p) //if p is not null, repeat the function
	{ //searching the space for inserting Node
		pp = p;
		if (node->GetcarNum() < p->GetcarNum())
			p = p->GetLeft();
		else if (node->GetcarNum() > p->GetcarNum())
			p = p->GetRight();

		else
		{
			if (node->GetcarNum() < pp->GetcarNum())
				pp->SetLeft(node);
			else if (node->GetcarNum() > pp->GetcarNum())
				pp->SetRight(node);
			return;
		}
	}

	if (root) //if root is null, return false
	{ //link the node
		if (node->GetcarNum() < pp->GetcarNum())
			pp->SetLeft(node);
		else
			pp->SetRight(node);
	}
	else
		root = node; //make root
}

CarNode * CarBST::Delete(int num)
{ //For deleting Node
	CarNode * p = root, *q = 0;
	while (p&&num != p->GetcarNum())
	{
		q = p;
		if (num < p->GetcarNum()) p = p->GetLeft();
		else p = p->GetRight();
	}

	if (p == 0)return NULL;

	if (p->GetLeft() == 0 && p->GetRight() == 0)//p is leaf
	{
		if (q == 0) root = 0;
		else if (q->GetLeft() == p) q->SetLeft(0);
		else q->SetRight(0);
		delete p;
	}

	else if (p->GetLeft() == 0)// p only has right child
	{
		if (q == 0) root = p->GetRight();
		else if (q->GetLeft() == p) q->SetLeft(p->GetRight());
		else q->SetRight(p->GetRight());
		delete p;
	}

	else if (p->GetRight() == 0)// p only has left child
	{
		if (q == 0)root = p->GetLeft();
		else if (q->GetLeft() == p) q->SetLeft(p->GetLeft());
		else q->SetRight(p->GetLeft());
		delete p;
	}

	else // p has left and right child;
	{
		CarNode*prevprev = p, *prev = p->GetRight(), *curr = p->GetRight()->GetLeft();

		while (curr)
		{
			prevprev = prev;
			prev = curr;
			curr = curr->GetLeft();
		}
		p->SetcarNum(prev->GetcarNum());
		p->SetcarOwner(prev->GetcarOwner());
		p->Setstate(prev->Getstate());
		if (prevprev == p)prevprev->SetRight(prev->GetRight());
		else prevprev->SetLeft(prev->GetRight());
		delete prev;
	}
	return NULL;
}

CarNode * CarBST::Search(int num, ofstream& flog,char*codename)
{ //The function for searching Node
	if (NULL == this)
		return NULL;

	CarNode * tmp = root;

	while (tmp)
	{ //repeat the function if the tmp is not null
		if (num < tmp->GetcarNum())
			tmp = tmp->GetLeft(); //move to left	
		else if (num > tmp->GetcarNum())
			tmp = tmp->GetRight(); //move to rigt
		else
		{
			flog << "======== " << codename << " ========" << endl;
			flog << tmp->GetcarNum() << " ";
			flog << tmp->GetcarOwner() << " ";
			flog << tmp->Getstate() << endl;
			flog << "=======================" << endl << endl;
			return tmp;
		}
	}
	return NULL;
}

bool CarBST::Print(const char * order, ofstream & flog)
{ //for print orders
	if (strcmp(order, "R_IN"))
		Inorder(order,flog); //The function that is Recursive function
	else if (strcmp(order, "R_PRE"))
		Preorder(order, flog); 
	else if (strcmp(order, "R_POST"))
		Postorder(order, flog); 
	else if (strcmp(order, "I_PRE"))
		I_preorder(order, flog); //The function that is Iterator function
	else if (strcmp(order, "I_IN"))
		I_inorder(order, flog);
	else if (strcmp(order, "I_POST"))
		I_postorder(order, flog);
	else if (strcmp(order, "I_LEVEL"))
		levelOrder(order, flog);
	return false;
}

bool CarBST::Save()
{
	return false;
}

void CarBST::Inorder(const char* order, ofstream&flog)
{ //The function for R_IN
	Inorder(order, root,flog);
}

void CarBST::Inorder(const char* order, CarNode* current,ofstream&flog)
{ //left Sub tree -> Node -> right Sub tree
	if (current != NULL)
	{
		Inorder(order, current->GetLeft(),flog);
		visit(current, flog); //Print element
		Inorder(order, current->GetRight(),flog);
	}
}

void CarBST::Preorder(const char* order, ofstream & flog)
{ //The function for R_PRE
	Preorder(order, root, flog);
}

void CarBST::Preorder(const char* order, CarNode * current, ofstream & flog)
{ //Node -> left Sub tee -> right Sub tree
	if (current != NULL)
	{
		visit(current, flog); //Print element
		Preorder(order, current->GetLeft(), flog);
		Preorder(order, current->GetRight(), flog);
	}
}

void CarBST::Postorder(const char* order, ofstream & flog)
{ //The function for R_POST
	Postorder(order, root, flog);
}

void CarBST::Postorder(const char* order,CarNode * current, ofstream & flog)
{ //left Sub tree -> right Sub tree -> Node
	if (current != NULL)
	{
		Postorder(order, current->GetLeft(), flog);
		Postorder(order, current->GetRight(), flog);
		visit(current, flog); //Print element
	}
}

void CarBST::levelOrder(const char* order, ofstream & flog)
{ //The function for iterator level order
	queue<CarNode*> q;
	CarNode* currentNode = root;

	while (currentNode) //repeat the function if currentNode is not NULL
	{
		visit(currentNode, flog); //Print current Node
		if (currentNode->GetLeft()) q.push(currentNode->GetLeft());
		if (currentNode->GetRight()) q.push(currentNode->GetRight());
		if (q.empty()) return; //check empty
		currentNode = q.front(); //save front data
		q.pop(); //delete queue element
	}
}

void CarBST::I_preorder(const char* order, ofstream & flog)
{ //The function for iterator preorder
	stack<CarNode*> stack; //declare stack
	CarNode* pNode = root;
	stack.push(pNode); //insert Node

	while (!stack.empty()) //repeat the function if stack is not NULL
	{
		CarNode* current = stack.top(); //save top data
		stack.pop(); //delete stack data
		visit(current, flog); //Print
		CarNode* tmp = current->GetRight();
		if (tmp != NULL) //if tmp is not NULL
			stack.push(tmp); //push tmp
		tmp = current->GetLeft(); //save current->left to tmp
		if (tmp != NULL)
			stack.push(tmp);
	}
}

void CarBST::I_inorder(const char* order, ofstream & flog)
{ //The function for iterator inorder
	stack<CarNode*> stack;
	CarNode* current = root;
	
	while (1) //repeat the function before break
	{ 
		while (current != NULL) //repeat the function if current is not NULL
		{
			stack.push(current); //push
			current = current->GetLeft(); //move pointer to left
		}

		if (!stack.empty()) //stack is not NULL, practice the function
		{
			current = stack.top(); //save data of stack's top
			stack.pop(); //deleete
		}
		if (current == NULL) //if current is NULL
			break; //break
		visit(current, flog); //Print
		current = current->GetRight(); //move pointer to right
	}
}

void CarBST::I_postorder(const char* order, ofstream & flog)
{ //The function for iterator postorder
	stack<CarNode*> stack;
	CarNode* current = root;
	CarNode* prev = NULL;

	stack.push(root); //push data of root

	while (!stack.empty()) //repeat the function if stack is not NULL
	{
		current = stack.top(); //Save the top data of stack
		if (!prev || prev->GetLeft() == current || prev->GetRight() == current)
		{ //If prev is not NULL, or prev's left is equal currnet, or prev's right is equal current
			if (current->GetLeft())
			{ //if current's left is not NULL
				stack.push(current->GetLeft()); //push
			}
			else if (current->GetRight())
			{ //if cureent's right is not NULL
				stack.push(current->GetRight()); //push
			}
		}
		else if (current->GetLeft() == prev)
		{ //if current's left is equal prev
			if (current->GetRight())
			{ //if current's right is not NULL
				stack.push(current->GetRight()); //push
			}
		}
		else
		{ //else
			visit(current, flog); //Print
			stack.pop(); //delete
		}
		prev = current; //save current to prev
	}
}

CarNode * CarBST::Complete(int num, ofstream & flog)
{ //for completing function
	if (this == NULL) //if this is NULL, return NULL
		return NULL;

	CarNode * tmp = root;
	while (tmp) //repeat the function if tmp is not NULL
	{
		if (num < tmp->GetcarNum())
			tmp = tmp->GetLeft(); //Move to left
		else if (num > tmp->GetcarNum())
			tmp = tmp->GetRight(); //Move to right
		else
			return tmp; //return tmp
	}
	return NULL; //return NULL
}

void CarBST::savepreorder(ofstream&e_list)
{ //for saving function
	savepreorder(root, e_list);
}

void CarBST::exit(CarNode*node)
{ //The function for delete Car BST Node(POST order)
	if (node != NULL)
	{
		exit(node->GetLeft());
		exit(node->GetRight());
		delete node;
	}
}

void CarBST::savepreorder(CarNode* current, ofstream&e_list)
{ //The order for using save function (PRE order)
	if (current != NULL)
	{
		visit(current, e_list);//visit the Node
		savepreorder(current->GetLeft(), e_list);
		savepreorder(current->GetRight(), e_list);
	}
}
