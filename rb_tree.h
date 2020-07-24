#pragma once
#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::ostream;

class Node {
public:
	string data;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;
	string color;

	Node() :data(""), right(nullptr), left(nullptr), color("black") {}
	Node(string data) :data(data), right(nullptr), left(nullptr), color("red") {}
};

class RedBlack {
private:
	Node* root;
	void rpreOrder(Node* n, ostream& os);
	void rpostOrder(Node* n, ostream& os);
public:
	RedBlack(): root(nullptr){}

	Node* getRoot() { return root; }
	void insert(string item);
	void fix_color_insert(Node* n);
	string search(string item);
	void removeNode(Node* parent, Node* n, string item);
	void remove(string item);
	void fix_color_remove(Node* n);
	void rotateLeft(Node* n);
	void rotateRight(Node* n);
	void preorder(ostream& os) {
		rpreOrder(root, os);
		Node* temp = new Node();
		temp = getRoot();
		if (temp == nullptr) {
			isEmpty();
		}
	}
	void postorder(ostream& os) {
		rpostOrder(root, os);
		Node* temp = new Node();
		temp = getRoot();
		if (temp == nullptr) {
			isEmpty();
		}
	}
	void isEmpty() {
		cout << "The tree is empty." << std::endl;
	}




};