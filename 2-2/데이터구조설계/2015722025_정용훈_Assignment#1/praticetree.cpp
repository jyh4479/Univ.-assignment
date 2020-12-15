#include<iostream>
#include"Tree.h"
using namespace std;

int main()
{
	Tree<int> List(1); //The root's data is 1, and declare the tree
	InorderIterator<int> order(&List); //Send the information of tree for inorder
	int count = 0, Nodecount = 0;

	cout << "Buil the Tree" << endl;
	List.buildTree(); //Build the Tree

	cout << "Preorder >> ";
	List.preorder(List.getRoot());
	cout << endl;

	cout << "Inorder >> ";
	List.inorder(List.getRoot());
	cout << endl;

	cout << "Postorder >> ";
	List.postorder(List.getRoot());
	cout << endl;

	cout << "NonrecInorder>> ";
	List.nonrecInorder();
	cout << endl;

	cout << "LevelOrder >> ";
	List.levelOrder();
	cout << endl;

	//The contents of the tree are printed whenever a function is called.
	cout << "InorderIterator >> ";
	cout << *order.Next() << " ";
	cout << *order.Next() << " ";
	cout << *order.Next() << " ";
	cout << *order.Next() << " ";
	cout << *order.Next() << " ";
	cout << *order.Next() << " ";
	cout << *order.Next() << " ";
	cout << *order.Next() << " ";
	cout << *order.Next() << " ";
	cout << *order.Next() << " ";
	cout << *order.Next();
	cout << endl;
	return 0; //Declare end of main function
}
