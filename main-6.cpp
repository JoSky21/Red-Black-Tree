/*
	Author: Jonathan Harjono
	NetID: jh4482
	Compiler used: Visual Studio 2019
	Program description: This program allows the user to create an red black tree
						that supports insert, delete, and search.

	Credits: https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/
			 https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
			 https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
			 btechsmartclass.com/data_structures/red-black-trees.html
			 https://medium.com/basecs/painting-nodes-black-with-red-black-trees-60eacb2be9a5
			 https://cs.lmu.edu/~ray/notes/redblacktrees/
			 https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html
			 https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
			 http://pages.cs.wisc.edu/~skrentny/cs367-common/readings/Red-Black-Trees/
*/


#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include "rb_tree.h"

using std::string;

struct WrongInput : public std::exception {
	const char* what() const throw() {
		return "Wrong input. Try again.";
	}
};

int main() {
	string choice;
	std::cout << "Welcome to the Red_Black program." << std::endl;
	RedBlack* tree1 = new RedBlack();
	std::cout << "Here is the menu for the program." << std::endl;
	do {
		std::cout << std::endl;
		std::cout << "1. Create a Red_Black." << std::endl;
		std::cout << "2. Insert a string to Red_Black." << std::endl;
		std::cout << "3. Search a string from Red_Black." << std::endl;
		std::cout << "4. Remove a string from Red_Black." << std::endl;
		std::cout << "5. Output the pre-order traversal." << std::endl;
		std::cout << "6. Output the post-order traversal." << std::endl;
		std::cout << "0. Exit the program." << std::endl;

		std::cin >> choice;
		if (choice == "1") {
			delete tree1;
			tree1 = new RedBlack();
			std::cout << "Red_Black tree has been created." << std::endl;
		}
		if (choice == "2") {
			string input;
			std::cout << "Please input the string." << std::endl;
			std::cin >> input;
			tree1->insert(input);
		}
		if (choice == "3") {
			string search;
			std::cout << "Please insert string to search." << std::endl;
			std::cin >> search;
			string result;
			result = tree1->search(search);
			std::cout << result << std::endl;
		}
		if (choice == "4") {
			string delete_data;
			std::cout << "Please insert string to delete." << std::endl;
			std::cin >> delete_data;
			tree1->remove(delete_data);
		}
		if (choice == "5") {
			tree1->preorder(std::cout);
		}
		if (choice == "6") {
			tree1->postorder(std::cout);
		}

	} while (choice != "0");

	std::cout << "Thank you for using this program." << std::endl;

	return 0;
}