#include "BinaryTree.h"

struct Node {
	int item;
	int level;
	string website;
	Node* prev;
	Node* left;
	Node* right;
};

//Description : Constructing
//Precondition : Nothing is defined
//Postcondition : Defines everything
BiTree::BiTree() {
	top = NULL;
	pos = NULL;
	save = NULL;
}

//Description : Deconstructing
//Precondition : Memory still storing information
//Postcondition : Deleting information to free memory
BiTree::~BiTree() {
	delete[] pos;
	delete[] top;
	delete[] save;
}

//Description : Getting the top pointer
//Precondition : Need the top pointer to go through the tree
//Postcondition : Gets the pointer to use in main
Node* BiTree::GetPointer() {
	pos = top;
	return pos;
}

//Description : Adding a node to the binary tree
//Precondition : Want to add something to the tree
//Postcondition : Adds something to the tree
void BiTree::Add(string item) {
	if (!isFull()) {
		pos = top;
		char firstLetter = item[0];
		int number = int(firstLetter);
		Node* temp = new Node();
		temp->website = item;
		temp->item = number;
		temp->level = NULL;
		temp->left = NULL;
		temp->right = NULL;
		temp->prev = NULL;

		if (top == NULL) {
			top = temp;
			pos = temp;
		}
		while (number != pos->item) {
			if (number > pos->item) {
				if (pos->right == NULL) {
					temp->prev = pos;
					pos->right = temp;
					pos = pos->right;
				}
				else {
					pos = pos->right;
				}
			}
			else if (number < pos->item) {
				if (pos->left == NULL) {
					temp->prev = pos;
					pos->left = temp;
					pos = pos->left;
				}
				else {
					pos = pos->left;
				}
			}
		}
	}
}

//Description : Removing an item from the tree
//Precondition : Want to remove an item from the tree
//Postcondition : Removes the item from the tree
void BiTree::Remove(string item) {
	if (!isEmpty()) {
		int first = int(item[0]);
		Node* temp = Search(first);
		while (pos != NULL) {
			if (first > pos->item) {
				if (pos->right == temp) {
					if ((pos->right->right == NULL) && (pos->right->left == NULL)) {
						pos->right = NULL;
					}
					else {
						Node* moveBranch = pos->right->left;
						pos->right = pos->right->right;
						if (pos->right != NULL) {
							pos->right->prev = pos;
						}
						else {
							moveBranch->prev = pos;
							pos->right = moveBranch;
							break;
						}
						while ((pos != NULL) && (moveBranch != NULL)) {
							if (moveBranch->item > pos->item) {
								if (pos->right == NULL) {
									moveBranch->prev = pos;
									pos->right = moveBranch;
									break;
								}
								else {
									pos = pos->right;
								}
							}
							else if (moveBranch->item < pos->item) {
								if (pos->left == NULL) {
									moveBranch->prev = pos;
									pos->left = moveBranch;
									break;
								}
								else {
									pos = pos->left;
								}
							}
						}
					}
				}
				else {
					pos = pos->right;
				}
			}
			else if (first < pos->item) {
				if (pos->left == temp) {
					if ((pos->left->left == NULL) && (pos->left->right == NULL)) {
						pos->left = NULL;
					}
					else {
						Node* moveBranch = pos->left->right;
						pos->left = pos->left->left;
						if (pos->left != NULL) {
							pos->left->prev = pos;
						}
						else {
							moveBranch->prev = pos;
							pos->left = moveBranch;
							break;
						}
						while ((pos != NULL) && (moveBranch != NULL)) {
							if (moveBranch->item > pos->item) {
								if (pos->right == NULL) {
									moveBranch->prev = pos;
									pos->right = moveBranch;
									break;
								}
								else {
									pos = pos->right;
								}
							}
							else if (moveBranch->item < pos->item) {
								if (pos->left == NULL) {
									moveBranch->prev = pos;
									pos->left = moveBranch;
									break;
								}
								else {
									pos = pos->left;
								}
							}
						}
					}
				}
				else {
					pos = pos->left;
				}
			}
			else if (pos == temp) {
				if (pos->left != NULL) {
					Node* moveBranch = pos->right;
					pos = pos->left;
					top = pos;
					while ((pos != NULL) && (moveBranch != NULL)) {
						if (moveBranch->item > pos->item) {
							if (pos->right == NULL) {
								moveBranch->prev = pos;
								pos->right = moveBranch;
								break;
							}
							else {
								pos = pos->right;
							}
						}
						else if (moveBranch->item < pos->item) {
							if (pos->left == NULL) {
								moveBranch->prev = pos;
								pos->left = moveBranch;
								break;
							}
							else {
								pos = pos->left;
							}
						}
					}
				}
				else if (pos->left == NULL) {
					pos = pos->right;
					top = pos;
				}
			}
		}
		delete temp;
	}
}

//Description : Sets all the level pointers for each node back to null
//Precondition : Need the levels to be null for the find level function to work
//Postcondition : Sets all the levels back to null
void BiTree::ResetLevel(Node* level) {
	if (!isEmpty()) {
		level->level = NULL;
		if ((level->left != NULL) && (level->right != NULL)) {
			ResetLevel(level->left);
			ResetLevel(level->right);
		}
		else if ((level->left != NULL) && (level->right == NULL)) {
			ResetLevel(level->left);
		}
		else if ((level->left == NULL) && (level->right != NULL)) {
			ResetLevel(level->right);
		}
	}
}

//Description : Need to know what level each node is at to print
//Precondition : All nodes are equal to level NULL
//Postcondition : Sets level in each node equal to their level
int BiTree::FindLevel() {
	pos = top;
	int max = 0;
	ResetLevel(pos);
	if (!isEmpty()) {
		pos = top;
		int level = 0;
		Node* temp = new Node();
		pos->prev = temp;
		pos->level = level;
		while (pos != temp) {
			if ((pos->left != NULL) && (pos->right != NULL)) {
				if (pos->left->level == NULL) {
					pos = pos->left;
					level++;
					pos->level = level;
					if (level > max) {
						max = level;
					}
				}
				else if (pos->right->level == NULL) {
					pos = pos->right;
					level++;
					pos->level = level;
					if (level > max) {
						max = level;
					}
				}
				else {
					pos = pos->prev;
					level--;
				}
			}
			else if ((pos->left == NULL) && (pos->right != NULL)) {
				if (pos->right->level == NULL) {
					pos = pos->right;
					level++;
					pos->level = level;
					if (level > max) {
						max = level;
					}
				}
				else {
					pos = pos->prev;
					level--;
				}
			}
			else if ((pos->left != NULL) && (pos->right == NULL)) {
				if (pos->left->level == NULL) {
					pos = pos->left;
					level++;
					pos->level = level;
					if (level > max) {
						max = level;
					}
				}
				else {
					pos = pos->prev;
					level--;
				}
			}
			else if ((pos->left == NULL) && (pos->right == NULL)) {
				pos = pos->prev;
				level--;
			}
		}
		pos = top;
		delete temp;
	}
	return max;
}

//Description : Prints everything
//Precondition : Want to see everything in the tree
//Postcondition : Prints all the items in the tree and levels
void BiTree::Print(Node* print) {
	if (!isEmpty()) {
		if ((print->left != NULL) && (print->right != NULL)) {
			cout << print->level << " - " << print->website << endl;
			Print(print->left);
			Print(print->right);
		}
		else if ((print->left != NULL) && (print->right == NULL)) {
			cout << print->level << " - " << print->website << endl;
			Print(print->left);
		}
		else if ((print->left == NULL) && (print->right != NULL)) {
			cout << print->level << " - " << print->website << endl;
			Print(print->right);
		}
		else {
			cout << print->level << " - " << print->website << endl;
		}
	}
}

//Description : Prints everything in a tree formation
//Precondition : Want to see how it looks in the tree
//Postcondition : Prints everything like how it would look
void BiTree::TPrint() {
	if (!isEmpty()) {
		save = top;
		top = EmptyNode();
		pos = top;
		int maxDepth = FindLevel();
		double maxNodes = pow(2, maxDepth);
		int gap = 0;
		int depth = 0;
		for (int x = 0; x < maxDepth; x++) {
			gap = 2 * (gap + 1);
		}
		while (depth <= maxDepth) {
			cout << "Level " << depth << " -";
			ResetLevel(pos);
			if (!isEmpty()) {
				int level = 0;
				Node* temp = new Node();
				pos->prev = temp;
				pos->level = level;
				if (pos->level == depth) {
					Bubble(pos->item, gap);
				}
				while (pos != temp) {
					if ((pos->left != NULL) && (pos->right != NULL)) {
						if (pos->left->level == NULL) {
							pos = pos->left;
							level++;
							pos->level = level;
							if (pos->level == depth) {
								Bubble(pos->item, gap);
							}
						}
						else if (pos->right->level == NULL) {
							pos = pos->right;
							level++;
							pos->level = level;
							if (pos->level == depth) {
								Bubble(pos->item, gap);
							}
						}
						else {
							pos = pos->prev;
							level--;
						}
					}
					else if ((pos->left == NULL) && (pos->right == NULL)) {
						pos = pos->prev;
						level--;
					}
				}
				pos = top;
				delete temp;
			}
			gap = ((gap / 2) - 1);
			depth++;
			cout << endl;
			cout << endl;
		}
		top = save;
		pos = top;
		save = NULL;
	}
}

//Description : Fills in the empty nodes for printing the tree
//Precondition : Left and right equal null at some levels so printing evenly is hard
//Postcondition : Adds empty nodes for left and right pointers so tree can be printed evenly
Node* BiTree::EmptyNode() {
	pos = top;
	int maxDepth = FindLevel();
	int level = 0;
	Node* tip = new Node();
	Node* clonePos = NULL;
	Node* cloneTop = NULL;
	while (clonePos != tip) {
		Node* temp = new Node();
		temp->item = NULL;
		temp->left = NULL;
		temp->right = NULL;
		temp->level = NULL;
		temp->prev = NULL;
		if (clonePos == NULL) {
			temp->level = level;
			temp->prev = tip;
			temp->item = pos->item;
			clonePos = temp;
			cloneTop = clonePos;
		}
		else if (level != maxDepth) {
			if (clonePos->left == NULL && clonePos->right == NULL) {
				level++;
				temp->level = level;
				temp->prev = clonePos;
				if (pos->left != NULL && pos->level == clonePos->level) {
					pos = pos->left;
					temp->item = pos->item;
				}
				clonePos->left = temp;
				clonePos = clonePos->left;
			}
			else if (clonePos->left == NULL && clonePos->right != NULL) {
				level++;
				temp->level = level;
				temp->prev = clonePos;
				if (pos->left != NULL && pos->level == clonePos->level) {
					pos = pos->left;
					temp->item = pos->item;
				}
				clonePos->left = temp;
				clonePos = clonePos->left;
			}
			else if (clonePos->left != NULL && clonePos->right == NULL) {
				level++;
				temp->level = level;
				temp->prev = clonePos;
				if (pos->right != NULL && pos->level == clonePos->level) {
					pos = pos->right;
					temp->item = pos->item;
				}
				clonePos->right = temp;
				clonePos = clonePos->right;
			}
			else if (clonePos->left != NULL && clonePos->right != NULL) {
				level--;
				if (pos->level == clonePos->level) {
					pos = pos->prev;
				}
				clonePos = clonePos->prev;
				delete temp;
			}
		}
		else {
			level--;
			if (pos->level == clonePos->level) {
				pos = pos->prev;
			}
			clonePos = clonePos->prev;
			delete temp;
		}
	}
	delete tip;
	return cloneTop;
}


//Description : Makes circle around the items
void BiTree::Bubble(int item, int gap) {
	for (int x = 0; x < gap; x++) {
		cout << " ";
	}
	if (item == NULL) {
		cout << "    ";
	}
	else {
		cout << "(" << setw(2) << char(item) << ")";
	}
	for (int x = 0; x < gap; x++) {
		cout << " ";
	}
}

//Description : Prints everything in reverse alphabetical order
//Precondition : Want to print everything from Z to A
//Postcondition : Prints everything from Z to A
void BiTree::RPrint() {
	pos = top;
	int* x = &CountNodes(pos);
	int const size = *x;
	*x = 0;
	string* array = new string[size + 1];
	pos = top;
	x = &Fill(array, pos);
	*x = 0;
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			string website = array[x];
			string website2 = array[x + 1];
			int letter = int(website[0]);
			int letter2 = int(website2[0]);
			if (letter < letter2) {
				string temp = website2;
				array[x] = temp;
				array[x + 1] = website;
			}
		}
	}
	for (int x = 0; x < size; x++) {
		cout << array[x] << endl;
	}
}

//Description : Prints everything in alphabetical order
//Precondition : Want to print everything from A to Z
//Postcondition : Prints everything from A to Z
void BiTree::APrint() {
	pos = top;
	int* x = &CountNodes(pos);
	int const size = *x;
	*x = 0;
	string* array = new string[size + 1];
	pos = top;
	x = &Fill(array, pos);
	*x = 0;
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			string website = array[x];
			string website2 = array[x + 1];
			int letter = int(website[0]);
			int letter2 = int(website2[0]);
			if (letter > letter2) {
				string temp = website;
				array[x] = website2;
				array[x + 1] = temp;
			}
		}
	}
	for (int x = 1; x <= size; x++) {
		cout << array[x] << endl;
	}
}

//Description : Need to know how many nodes there are for the size of the array
//Precondition : Dont know how many nodes there are
//Postcondition : Count all the nodes and return nodes so i can set the static value back to zero
int& BiTree::CountNodes(Node* count) {
	int static nodes = 0;
	if (!isEmpty()) {
		if ((count->left != NULL) && (count->right != NULL)) {
			nodes++;
			CountNodes(count->left);
			CountNodes(count->right);
		}
		else if ((count->left != NULL) && (count->right == NULL)) {
			nodes++;
			CountNodes(count->left);
		}
		else if ((count->left == NULL) && (count->right != NULL)) {
			nodes++;
			CountNodes(count->right);
		}
		else {
			nodes++;
		}
	}
	return nodes;
}

//Description : Fills the array with the items in the tree
//Precondition : Array is empty and we want to fill it
//Postcondition : Fills array with items so we can sort in alphabetical order
int& BiTree::Fill(string *array_, Node* fill) {
	int static x = 0;
	if (!isEmpty()) {
		if ((fill->left != NULL) && (fill->right != NULL)) {
			array_[x] = fill->website;
			x++;
			Fill(array_, fill->left);
			x++;
			Fill(array_, fill->right);
		}
		else if ((fill->left != NULL) && (fill->right == NULL)) {
			array_[x] = fill->website;
			x++;
			Fill(array_, fill->left);
		}
		else if ((fill->left == NULL) && (fill->right != NULL)) {
			array_[x] = fill->website;
			x++;
			Fill(array_, fill->right);
		}
		else {
			array_[x] = fill->website;
		}
	}
	return x;
}

//Description : Finds an item in the tree
//Precondition : Want to find specific item in the tree
//Postcondition : Finds the item that we are looking for
Node* BiTree::Search(int item) {
	pos = top;
	Node* temp;
	if (!isEmpty()) {
		while ((pos != NULL) && (pos->item != item)) {
			if (item > pos->item) {
				pos = pos->right;
			}
			else if (item < pos->item) {
				pos = pos->left;
			}
		}
		if (pos == NULL) {
			cout << "Item not found." << endl;
			return NULL;
		}
		else {
			cout << pos->item << " found." << endl;
			temp = pos;
			pos = top;
			return temp;
		}
	}
	else {
		return  NULL;
	}
}

//Description : Need to check to see if the list is full
//Precondition : Dont know if the list is full
//Postcondition : Doesnt let you add if the list is full
bool BiTree::isFull() {
	Node* temp = new Node();
	if (!temp) {
		cout << "Tree is full" << endl;
		return true;
	}
	else {
		delete temp;
		return false;
	}
}

//Description : Need to check to see if the list is empty
//Precondition : Dont know if the list empty
//Postcondition : Doesnt do stuff if the list is empty
bool BiTree::isEmpty() {
	if (top == NULL) {
		cout << "Tree is empty" << endl;
		return true;
	}
	else {
		return false;
	}
}

//Just for fun
void BiTree::PreloadedWebsites() {
	Add("Hero_news.org");
	Add("Slanted_retangles_are_better_than_rhombuses.edu");
	Add("Zebras_have_black_stripes.edu");
	Add("Apples_do_not_have_cameras_in_them.gov");
	Add("Jesus_supports_cannibalism.com");
	Add("Boobs_are_awesome_;).com");
	Add("Cookie_recipe.com");
}