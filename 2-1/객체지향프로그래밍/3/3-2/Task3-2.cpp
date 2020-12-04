#include <iostream>
#include <string>

#include "LinkedList.h"

using namespace std;

int main()
{

	kw::LinkedList<int> linkedList;

	cout << "Initialization" << endl << endl;

	cout << "insertion (1)" << endl << endl;
	cout << "insertion (3)" << endl << endl;
	cout << "insertion (4)" << endl << endl;
	cout << "insertion (6)" << endl << endl;

	linkedList.insert(1);
	linkedList.insert(3);
	linkedList.insert(4);
	linkedList.insert(6);

	cout << linkedList << endl;

	cout << "After reverse function" << endl << endl;

	linkedList.reverse();

	cout << linkedList << endl;

	cout << "After sort function" << endl << endl;

	linkedList.sort();

	cout << linkedList << endl;

	return 0;
}