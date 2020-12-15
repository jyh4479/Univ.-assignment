#include "NumberBST.h"
#include <queue>
#include <stack>


NumberBST::NumberBST()//constructor
{
	int info[10] = { 7,3,9,1,0,2,5,4,6,8 };
	int count = 0;

	while (count != 10)
	{ //Biild the Number BST
		NumberNode* p = new NumberNode(info[count++]);
		Insert(p); //For inset Node
	}
}

NumberBST::~NumberBST()//destructor
{
	exit(root);
	/* You must fill here */
}

NumberNode *NumberBST::Checknumber(int num)
{
	int checknum = 0;
	char carnumber[10];
	char fcarnumber[10];

	sprintf(carnumber,"%d",num); //change type of value
	fcarnumber[0] = carnumber[0];
	checknum = atoi(fcarnumber);
	NumberNode *tmp = root;

	while (tmp)
	{ //if tmp is not null, repeat the function
		if (checknum < tmp->GetNumber())
			tmp = tmp->GetLeft();
		else if (checknum > tmp->GetNumber())
			tmp = tmp->GetRight();
		else
			return tmp; //return tmp
	}
}

void NumberBST::Insert(NumberNode * node)
{ //for making number BST
	NumberNode*p = root, *pp = 0;
	while (p)
	{ //if p is not null, repeat the function
		pp = p;
		if (node->GetNumber() < p->GetNumber())
			p = p->GetLeft(); //move the node to left
		else if (node->GetNumber() > p->GetNumber())
			p = p->GetRight(); //move the node to right

		else
		{
			if (node->GetNumber() < pp->GetNumber())
				pp->SetLeft(node); //link the Node
			else if (node->GetNumber() > pp->GetNumber())
				pp->SetRight(node);

			return;
		}
	}

	if (root)
	{ //if root is not null, practice the function
		if (node->GetNumber() < pp->GetNumber())
			pp->SetLeft(node);
		else
			pp->SetRight(node);
	}
	else
		root = node; //make the root
}

NumberNode * NumberBST::Search(int num, ofstream& flog)
{
	if (this == NULL)
		return NULL; //for checking ther is data or no data

	char fnum[10];
	char fnum2[10];
	char command[20]={"SEARCH"};
	int frontnum = 0;

	sprintf(fnum,"%d",num);
	fnum2[0] = fnum[0];
	frontnum = atoi(fnum2); //save the first number of array

	NumberNode * tmp = root;
	while (tmp)
	{ //if tmp is not null, repeat the function
		if (frontnum < tmp->GetNumber())
			tmp = tmp->GetLeft(); //move the node to left
		else if (frontnum > tmp->GetNumber())
			tmp = tmp->GetRight(); //move the node th right
		else
		{
			if (tmp->GetBST()->Search(num,flog,command) != NULL)
				return tmp; //Search the node that corret information
			else
				return NULL;
		}
	}
	return NULL;
}

bool NumberBST::Print(char * BST, ofstream & flog)
{ //for print and check information according to order
	char R_IN[10]={"R_IN"};
	char R_POST[10]={"R_POST"};
	char R_PRE[10]={"R_PRE"};
	char I_IN[10]={"I_IN"};
	char I_POST[10]={"I_POST"};
	char I_PRE[10]={"I_PRE"};
	char I_LEVEL[10]={"I_LEVEL"};

	if (strncmp(BST, "R_IN",4)==0)
	{ //Recursive inorder function
		flog << "======== " << "PRINT R_IN" << " ========" << endl;
		Inorder(R_IN,flog);
		flog << "=======================" << endl << endl;
		return 1;
	}

	else if (strncmp(BST, "R_PRE",5) == 0)
	{ //Recursive preorder function
		flog << "======== " << "PRINT R_PRE" << " ========" << endl;
		Preorder(R_PRE,flog);
		flog << "=======================" << endl << endl;
		return 1;
	}

	else if (strncmp(BST, "R_POST",6) == 0)
	{ //Recursive postorder function
		flog << "======== " << "PRINT R_POST" << " ========" << endl;
		Postorder(R_POST,flog);
		flog << "=======================" << endl << endl;
		return 1;
	}

	else if (strncmp(BST, "I_PRE",5) == 0)
	{ //Iterator preorder function
		flog << "======== " << "PRINT I_PRE" << " ========" << endl;
		I_preorder(I_PRE, flog);
		flog << "=======================" << endl << endl;
		return 1;
	}

	else if (strncmp(BST, "I_IN",4) == 0)
	{ //Iterator inorder function
		flog << "======== " << "PRINT I_IN" << " ========" << endl;
		I_inorder(I_IN, flog);
		flog << "=======================" << endl << endl;
		return 1;
	}

	else if (strncmp(BST, "I_POST",6) == 0)
	{ //Iterator postorder function
		flog << "======== " << "PRINT I_POST" << " ========" << endl;
		I_postorder(I_POST, flog);
		flog << "=======================" << endl << endl;
		return 1;
	}

	else if (strncmp(BST, "I_LEVEL",7) == 0)
	{ //the level order
		flog << "======== " << "PRINT I_LEVEL" << " ========" << endl;
		levelOrder(I_LEVEL, flog);
		flog << "=======================" << endl << endl;
		return 1;
	}
	return 0;
}

void NumberBST::Inorder(char* order,ofstream&flog)
{
	Inorder(order,root,flog);
}

void NumberBST::Inorder(char* order, NumberNode* current,ofstream&flog)
{
	if (current != NULL)
	{
		Inorder(order, current->GetLeft(),flog);
		visit(current,flog);
		if (current->GetBST() != NULL) //call the function that is carbst order
			current->GetBST()->Inorder(order,flog);
		Inorder(order, current->GetRight(),flog);
	}
}

void NumberBST::Preorder(char* order,ofstream & flog)
{ //Recursive function of preorder
	Preorder(order,root, flog);
}

void NumberBST::Preorder(char* order, NumberNode * current, ofstream & flog)
{
	if (current != NULL)
	{
		visit(current, flog);
		if (current->GetBST() != NULL) //call the function that is carbst order
			current->GetBST()->Preorder(order, flog);
		Preorder(order, current->GetLeft(), flog);
		Preorder(order, current->GetRight(), flog);
	}
}

void NumberBST::Postorder(char* order,ofstream & flog)
{ //Recursive function of postorder
	Postorder(order, root, flog);
}

void NumberBST::Postorder(char* order, NumberNode * current, ofstream & flog)
{
	if (current != NULL)
	{
		Postorder(order, current->GetLeft(), flog);
		Postorder(order, current->GetRight(), flog);
		visit(current, flog);
		if (current->GetBST() != NULL) //call the function that is carbst order
			current->GetBST()->Postorder(order, flog);
	}
}

void NumberBST::I_preorder(char* order, ofstream & flog)
{ //Iterator function of preorder
	stack<NumberNode*> stack;
	NumberNode* pNode = root;

	stack.push(pNode);

	while (!stack.empty())
	{
		NumberNode* current = stack.top();
		stack.pop();
		visit(current, flog);
		if (current->GetBST() != NULL)
			current->GetBST()->I_preorder("I_PRE", flog);
		NumberNode* tmp = current->GetRight();
		if (tmp != NULL)
			stack.push(tmp);
		tmp = current->GetLeft();
		if (tmp != NULL)
			stack.push(tmp);
	}
}

void NumberBST::I_inorder(char* order, ofstream & flog)
{ //Iterator function of inorder
	stack<NumberNode*> stack;
	NumberNode* current = root;

	while (1)
	{
		while (current != NULL)
		{
			stack.push(current);
			current = current->GetLeft();
		}

		if (!stack.empty())
		{
			current = stack.top();
			stack.pop();
		}
		if (current == NULL)
			break;
		visit(current,flog);
		if (current->GetBST() != NULL)
			current->GetBST()->I_inorder("I_IN", flog);
		current = current->GetRight();
	}
}

void NumberBST::I_postorder(char* order, ofstream & flog)
{ //Iterator function of postorder
	stack<NumberNode*> stack;
	NumberNode* current = root;
	NumberNode* prev = NULL;

	if (!root)
		return;

	stack.push(root);

	while (!stack.empty())
	{
		current = stack.top();
		if (!prev || prev->GetLeft() == current || prev->GetRight() == current)
		{
			if (current->GetLeft())
			{
				stack.push(current->GetLeft());
			}
			else if (current->GetRight())
			{
				stack.push(current->GetRight());
			}
		}
		else if (current->GetLeft() == prev)
		{
			if (current->GetRight())
			{
				stack.push(current->GetRight());
			}
		}
		else
		{
			visit(current, flog);
			if (current->GetBST() != NULL)
				current->GetBST()->I_postorder("I_POST", flog);
			stack.pop();
		}
		prev = current;
	}
}



void NumberBST::levelOrder(char* order, ofstream & flog)
{ //Iterator function of levelorder
	queue<NumberNode*> q;
	NumberNode* currentNode = root;

	while (currentNode)
	{
		visit(currentNode, flog);
		if (currentNode->GetBST() != NULL)
			currentNode->GetBST()->levelOrder(order, flog);
		if (currentNode->GetLeft()) q.push(currentNode->GetLeft());
		if (currentNode->GetRight()) q.push(currentNode->GetRight());
		if (q.empty()) return;
		currentNode = q.front();
		q.pop();
	}
}

void visit(NumberNode* cur) //for print information of node
{
	cout << cur->GetNumber() << " ";
}

NumberNode * NumberBST::Delete(int num, ofstream & flog)
{  //for practicing complete function
	char fnum[10];
	char fnum2[10];
	int frontnum = 0;

	sprintf(fnum, "%d", num);
	fnum2[0] = fnum[0];
	frontnum = atoi(fnum2); //checking the first number

	NumberNode * tmp = root;
	while (tmp)
	{ //searching algorithm
		if (frontnum < tmp->GetNumber())
			tmp = tmp->GetLeft();
		else if (frontnum > tmp->GetNumber())
			tmp = tmp->GetRight();
		else
		{
			if (tmp->GetBST()->Complete(num, flog) != NULL)
				return tmp;
			else
				return NULL;
		}
	}
	return NULL;
}



bool NumberBST::Save()
{ //for saving data of BST
	ofstream e_list("event_list_car.txt");
	savepreorder(e_list); //for saving BST, used the function that is preorder
	return false;
}

void NumberBST::exit(NumberNode*node)
{ //The function for delete BST
	if (node != NULL)
	{ //for delete BST, used the function that is post order
		exit(node->GetLeft());
		exit(node->GetRight());
		delete node->GetBST();
		delete node;
	}
}

void NumberBST::savepreorder(ofstream&e_list)
{
	savepreorder(root,e_list);
}

void NumberBST::savepreorder(NumberNode* current, ofstream&e_list)
{ //The function for saveing information that will be used for LOAD command
	if (current != NULL)
	{
		if (current->GetBST() != NULL)
			current->GetBST()->savepreorder(e_list);
		savepreorder(current->GetLeft(), e_list);
		savepreorder(current->GetRight(), e_list);
	}
}
