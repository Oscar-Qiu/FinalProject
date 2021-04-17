#pragma once
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
struct Node {
	Node* left;
	Node* right;
	string text;
	string question; // Store yes or no

	Node(string text_) {
		text = text_;
		left = nullptr;
		right = nullptr;
	}

};
class QuestionGame
{
private:
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
public:
	
	// Constructor for Question Game
	QuestionGame() {
		// Initialize the default root to be computer
		Node* root = new Node("computer");
		// Initialize the default quesiton to A
		root->question = "A";

	}

	// Destructor for cleaningt the memory
	~QuestionGame() {
		// delete the whole tree
		Node* root;
		cleanMemory(root);


	}
	void write(ofstream& outFile);
	void read(ifstream& inFile);
	void askQuestions();
	bool yesTo(string& prompt);




	



};

