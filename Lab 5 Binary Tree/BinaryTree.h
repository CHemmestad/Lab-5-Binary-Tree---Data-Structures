#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

struct Node;

//GOAL:
//Sort strings of website names int alphabetic order and reverse 
//alphabetical order

class BiTree {
public:
	BiTree(); //Done
	~BiTree();

	void Add(string item); //Done
	void Remove(string item); //Done
	void ResetLevel(Node* level); //Bone
	int FindLevel(); //Done
	void Print(Node* print); //Done
	void TPrint(); //Done
	void RPrint();
	void APrint();
	int& CountNodes(Node* count); //Done
	int& Fill(string* array_, Node* fill);
	void Bubble(int item, int gap); //Done
	Node* EmptyNode(); //Done
	Node* GetPointer(); //Done
	Node* Search(int item); //Done
	void PreloadedWebsites();
	
	bool isFull(); //Done
	bool isEmpty(); //Done

private:
	Node* top;
	Node* pos;
	Node* save;
};

#endif BINARYTREE_H