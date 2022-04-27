#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main() {

	BiTree bitree;

	bitree.PreloadedWebsites();

	bool con = true;

	while (con) {
		system("cls");
		cout << "1 to print website and levels" << endl;
		cout << "2 to print from A to Z" << endl;
		cout << "3 to print from Z to A" << endl;
		cout << "4 to print tree" << endl;
		cout << "5 to add website" << endl;
		cout << "6 to remove website" << endl;
		cout << "7 to exit" << endl;
		int x = NULL;
		string web;
		cin >> x;
		system("cls");
		switch (x) {
		case 1:
			bitree.FindLevel();
			bitree.Print(bitree.GetPointer());
			system("pause");
			break;
		case 2:
			bitree.APrint();
			system("pause");
			break;
		case 3:
			bitree.RPrint();
			system("pause");
			break;
		case 4:
			bitree.TPrint();
			system("pause");
			break;
		case 5:
			cout << "What do you want to add? (string) : ";
			cin.ignore();
			getline(cin, web);
			bitree.Add(web);
			system("pause");
			break;
		case 6:
			cout << "What do you want to remove? (string) : ";
			cin.ignore();
			getline(cin, web);
			bitree.Remove(web);
			system("pause");
			break;
		case 7:
			con = false;
			bitree.~BiTree();
			break;
		default:
			cout << "Invalid" << endl;
			system("pause");
		}
	}

	return 0;
}
