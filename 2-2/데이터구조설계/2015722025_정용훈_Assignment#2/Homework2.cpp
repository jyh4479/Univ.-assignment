#include<iostream>
#include"Dictionary.h"
using namespace std;

int main()
{
	BST<int, char> BSTtree; //The tree

	cout << "Build Tree" << endl;
	cout <<"Created order is 5,8,7,1,6,2,4,3,9" << endl;

	BSTtree.Insert(pair<int, char>(5, 'a')); //the order of insert tree
	BSTtree.Insert(pair<int, char>(8, 'b'));
	BSTtree.Insert(pair<int, char>(7, 'c'));
	BSTtree.Insert(pair<int, char>(1, 'd'));
	BSTtree.Insert(pair<int, char>(6, 'e'));
	BSTtree.Insert(pair<int, char>(2, 'f'));
	BSTtree.Insert(pair<int, char>(4, 'g'));
	BSTtree.Insert(pair<int, char>(3, 'h'));
	BSTtree.Insert(pair<int, char>(9, 'i'));

	cout << endl << "Level Order" << endl;
	BSTtree.levelOrder(); //show the tree

	cout << endl << "Search" << endl;
	cout << "Key is 1 : " << BSTtree.Get(1)->second << endl; //print value
	cout << "Key is 6 : " << BSTtree.Get(6)->second << endl;
	cout << "Key is 9 : " << BSTtree.Get(9)->second << endl;	
	cout << "Key is 7 : " << BSTtree.Get(7)->second << endl;

	cout << endl << "Delete" << endl;
	cout << "Key is 2, 3, 1, 8" << endl;
	BSTtree.Delete(2); //practice delete
	BSTtree.Delete(3);
	BSTtree.Delete(1);
	BSTtree.Delete(8);

	cout << endl << "Level Order" << endl;
	BSTtree.levelOrder(); //show the tree

	return 0;
}