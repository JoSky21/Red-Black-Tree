#include <iostream>
#include <string>
#include "rb_tree.h"

using std::cout;
using std::string;
using std::endl;

void doesnotExist() {
	std::cout << "The element doesn't exist in the tree \n";
}

void RedBlack::insert(string item) {
	Node* tempo = getRoot();
	if (tempo == nullptr) {
		tempo = new Node(item);
		tempo->parent = nullptr;
		tempo->color = "black";
	}
	else {
		Node* temp = getRoot();
		Node* temp2 = new Node(item);

		while (temp != nullptr) {
			if (temp->data > item) {
				if (temp->left == nullptr) {
					temp->left = temp2;
					temp2->parent = temp;
					break;
				}
				else {
					temp = temp->left;
				}
			}
			else {
				if (temp->right == nullptr) {
					temp->right = temp2;
					temp2->parent = temp;
					break;
				}
				else {
					temp = temp->right;
				}
			}
		}
		fix_color_insert(temp2);
	}
	root = tempo;
}

void RedBlack::fix_color_insert(Node* n) {
	Node* tempo = getRoot();
	while (n->parent->color == "red") {
		Node* grandparent = n->parent->parent;
		Node* uncle = getRoot();
		if (n->parent == grandparent->left) {
			if (grandparent->right != nullptr) {
				uncle = grandparent->right;
			}
			if (uncle->color == "red") {
				n->parent->color = "black";
				uncle->color = "black";
				grandparent->color = "red";
				if (grandparent->data != tempo->data) {
					n = grandparent;
				}
				else { break; }
			}
			else if (n == grandparent->left->right) {
				rotateLeft(n->parent);
			}
			else {
				n->parent->color = "black";
				grandparent->color = "red";
				rotateRight(grandparent);
				if (grandparent->data != tempo->data) {
					n = grandparent;
				}
				else { break; }
			}
		}
		else {
			if (grandparent->left != nullptr) {
				uncle = grandparent->left;
			}
			if (uncle->color == "red") {
				n->parent->color = "black";
				uncle->color = "black";
				grandparent->color = "red";
				if (grandparent->data != tempo->data) {
					n = grandparent;
				}
				else { break; }
			}
			else if (n == grandparent->right->left) {
				rotateRight(n->parent);
			}
			else {
				n->parent->color == "black";
				grandparent->color == "red";
				rotateLeft(grandparent);
				if (grandparent->data != tempo->data) {
					n = grandparent;
				}
				else { break; }
			}
		}
	}
	tempo->color = "black";
	root = tempo;
}

void RedBlack::removeNode(Node* parent, Node* n, string item) {
	Node* tempo = getRoot();
	if (n == nullptr) { return; }
	if (n->data == item) {
		//Case 1 Node is a leaf
		if (n->left == nullptr && n->right == nullptr) {
			if (parent->data == n->data) {
				tempo = nullptr;
			}
			else if (parent->right = n) {
				fix_color_remove(n);
				parent->right = nullptr;
			}
			else {
				fix_color_remove(n);
				parent->left = nullptr;
			}
		}
		//Case 2 Node has a child on either left or right
		else if (n->left != nullptr && n->right == nullptr) {
			string temp = n->data;
			n->data = n->left->data;
			n->left->data = temp;
			removeNode(n, n->right, item);
		}
		else if (n->left == nullptr && n->right != nullptr) {
			string temp = n->data;
			n->data = n->right->data;
			n->right->data = temp;
			removeNode(n, n->right, item);
		}
		//Case 3 Node has 2 children
		else {
			bool flag = false;
			Node* temp = n->right;
			while (temp->left != nullptr) {
				flag = true;
				parent = temp;
				temp = temp->left;
			}
			if (!flag) {
				parent = n;
			}
			string swap = n->data;
			n->data = temp->data;
			temp->data = swap;
			removeNode(parent, temp, swap);
		}
	}
	root = tempo;
}

void RedBlack::remove(string item) {
	Node* temp = getRoot();
	Node* parent = temp;
	bool flag = false;
	if (temp != nullptr) {
		removeNode(nullptr, nullptr, item);
	}

	while (temp != nullptr) {
		if (item == temp->data) {
			flag = true; 
			removeNode(parent, temp, item);
			break;
		}
		else if (item < temp->data) {
			parent = temp;
			temp = temp->left;
		}
		else {
			parent = temp;
			temp = temp->right;
		}
	}

	if (!flag) {
		doesnotExist();
	}

}

void RedBlack::fix_color_remove(Node* n) {
	Node* tempo = getRoot();
	while (n->data != tempo->data && n->color == "black") {
		Node* sibling = tempo;
		if (n->parent->left = n) {
			if (n->parent->right != nullptr) {
				sibling = n->parent->right;
			}
			if (sibling != nullptr) {
				//Case 1
				if (sibling->color == "red") {
					sibling->color == "black";
					n->parent->color == "red";
					rotateLeft(n->parent);
					sibling = n->parent->right;
				}
				//Case 2
				if (sibling->left == nullptr && sibling->right == nullptr) {
					sibling->color = "red";
					n = n->parent;
				}
				else if (sibling->left->color == "black" && sibling->right->color == "black") {
					sibling->color = "red";
					n = n->parent;
				}
				//Case 3
				else if (sibling->right->color == "black") {
					sibling->left->color = "black";
					sibling->color = "red";
					rotateRight(sibling);
					sibling = n->parent->right;
				}
				else {
					sibling->color = n->parent->color;
					n->parent->color = "black";
					if (sibling->right != nullptr) {
						sibling->right->color == "black";
					}
					rotateLeft(n->parent);
					n = tempo;
				}
			}
		}
		else {
			if (n->parent->right = n) {
				if (n->parent->left != nullptr) {
					sibling = n->parent->left;
				}
				if (sibling != nullptr) {
					//Case 1
					if (sibling->color == "red") {
						sibling->color = "black";
						n->parent->color = "red";
						rotateRight(n->parent);
						sibling = n->parent->left;
					}
					//Case 2
					if (sibling->left == nullptr && sibling->right == nullptr) {
						sibling->color == "red";
						n = n->parent;
					}
					else if (sibling->left->color == "black" && sibling->right->color == "black") {
						sibling->color == "red";
						n = n->parent;
					}
					//Case 3
					else if (sibling->left->color == "black") {
						sibling->right->color == "black";
						sibling->color = "red";
						rotateRight(sibling);
						sibling = n->parent->left;
					}
					else {
						sibling->color = n->parent->color;
						n->parent->color = "black";
						if (sibling->left != nullptr) {
							sibling->left->color == "black";
						}
						rotateLeft(n->parent);
						n = tempo;
					}
				}
			}
		}
	}
	n->color = "black";
}

string RedBlack::search(string item) {
	Node* temp = getRoot();
	string empty = "The item is not in the tree.";
	if (temp == nullptr) {
		return empty;
	}

	while (temp != nullptr) {
		if (item == temp->data) {
			return item;
		}
		else if (item < temp->data) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	return empty;
}

void RedBlack::rotateLeft(Node* n) {
	Node* temp = new Node();
	if (n->right->left) {
		temp->right = n->right->left;
	}
	temp->left = n->left;
	temp->data = n->data;
	temp->color = n->color;
	n->data = n->right->data;

	n->left = temp;
	if (temp->left != nullptr) {
		temp->left->parent = temp;
	}
	if (temp->right != nullptr) {
		temp->right->parent = temp;
	}
	temp->parent = n;

	if (n->right->right != nullptr) {
		n->right = n->right->right;
	}
	else {
		n->right = nullptr;
	}
	if (n->right != nullptr) {
		n->right->parent = n;
	}
}

void RedBlack::rotateRight(Node* n) {
	Node* temp = new Node();
	if (n->left->right) {
		temp->right = n->left->right;
	}
	temp->right = n->right;
	temp->data = n->data;
	temp->color = n->color;

	n->data = n->left->data;
	n->color = n->left->color;

	n->right = temp;
	if (temp->left != nullptr) {
		temp->left->parent = temp;
	}
	if (temp->right != nullptr) {
		temp->right->parent = temp;
	}
	temp->parent = n;

	if (n->left->left != nullptr) {
		n->left = n->left->left;
	}
	else {
		n->left = nullptr;
	}
	if (n->left != nullptr) {
		n->left->parent = n;
	}
}

void RedBlack::rpreOrder(Node* n, ostream& os) {
	if (n == nullptr) { return; }
	os << n->data << " <" << n->color << ">" << std::endl;
	rpreOrder(n->left, os);
	rpreOrder(n->right, os);
}

void RedBlack::rpostOrder(Node* n, ostream& os) {
	if (n == nullptr) { return; }
	rpostOrder(n->left, os);
	rpostOrder(n->right, os);
	os << n->data << " <" << n->color << ">" << std::endl;
}

