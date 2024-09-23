#include <iostream>
#include <fstream>
#include "PROJECT3.h"
#pragma warning(suppress : 4996)
using namespace std;
int main()
{
	cout << "enter a number from this list\n\n" << endl;
	cout << "1. insert data." << endl;
	cout << "2. delete data." << endl;
	cout << "3. get height." << endl;
	cout << "4. print in order." << endl;
	int x,c;
	cin >> x;
	MyAVL tree;
	switch (1)
	{
    case(1):
	{
		cout << "enter a num" << endl;
		cin >> c;
		tree.root = tree.insertData(tree.root, c);
		break;
	}
	case (2):
	{
		cout << "enter a num" << endl;
		cin >> c;
		tree.root = tree.deleteData(tree.root, c);
		break;
	}
	case (3):
	{ 
      tree.getHeight(tree.root);
		break;
	}
	case (4):
	{
		tree.printInOrder(tree.root);

	}
	default:
		cout << "enter a num again" << endl;
		break;

	}while (x != 0);
}