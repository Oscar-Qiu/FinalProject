#pragma once
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

struct Node {

	Node* left;
	Node* right;
	string text;
	string question;  // Store two types "A" && " Q "

	Node(string text_) {
		text = text_;
		left = nullptr;
		right = nullptr;
		question = "A";
	}

};

class QuestionGame
{

private:

	Node* root; // Give the access to the root node

	// Create a helper function to help us delete the memory
	void cleanMemory(Node* root) {
		Node* curr = root;
		// Base case, if the root reaches the nullptr
		if (curr == nullptr) return;
		// else traverse the whole tree to delete the node
		cleanMemory(root->left);
		cleanMemory(root->right);
		// Free the memory
		delete curr;
		// Set it to nullptr
		curr = nullptr;

	}
	// Create a helper function to read the file and traverse the whole tree
	Node* readHelper(Node* root, ifstream& inFile) {

		string lineToRead;
		// As long as there is a line to read
		if (getline(inFile, lineToRead)) {

			root->text = lineToRead;
			// if the first character is " Q "
			if (lineToRead[0] == 'Q') {
				// Update the question type of the function
				root->question = "Q";
				// Recursively call the helper function to build up the tree
				root->left = readHelper(root->left, inFile);
				root->right = readHelper(root->right, inFile);
			}
		}
		return root;
	}
	// Create a helper function to output the file and traverse the whole tree
	void writeHealper(Node* root, ofstream& outFile) {
		if (root == nullptr) return;
		// Write back the root's data to the file
		outFile << root->text << endl;
		// Perform this operation to the whole bst
		writeHealper(root->left, outFile);
		writeHealper(root->right, outFile);
		
	}
	
public:
	
	// Constructor for Question Game
	QuestionGame() {
		// Initialize the default root to be computer
		root = new Node("computer");
		// Initialize the default quesiton to A
		root->question = "A";

	}

	// Destructor for cleaning the memory
	~QuestionGame() {
		// delete the whole tree
		
		cleanMemory(root);


	}

	void write(ofstream& outFile) {
		// Call the helper function to output the data
		writeHealper(root, outFile);
	}
	void read(ifstream& inFile) {
		// Call the helper function to clean up the existing tree
		cleanMemory(root);
		// Call the helper to read the data passed_in and build the tree
		root = readHelper(root, inFile); // Update the root


	}
	void askQuestions();
	bool yesTo(string prompt);




	



};

