#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
using namespace std;

struct Node {

	Node* Yes;
	Node* No;
	string text;
	string question;  // Store two types "A" && " Q "
	

	Node(string text_) {
		text = text_;
		Yes = nullptr;
		No = nullptr;
		question = "A:";
		
	}

};

class QuestionGame
{

private:
	map<string, int> myMap;
	int numberOfQuestions;
	Node* root; // Give the access to the root node

	// Create a helper function to help us delete the memory
	void cleanMemory(Node* root) {
		Node* curr = root;
		// Base case, if the root reaches the nullptr
		if (curr == nullptr) return;
		// else traverse the whole tree to delete the node
		cleanMemory(root->Yes);
		cleanMemory(root->No);
		// Free the memory
		delete curr;
		// Set it to nullptr
		curr = nullptr;

	}
	// Create a helper function to read the file and traverse the whole tree
	Node* readHelper(Node* root, ifstream& inFile) {

		string questionType;
		getline(inFile, questionType);
		string textToRead;
		getline(inFile, textToRead);
		// reassign the value of the root node with the value passed in
		root = new Node(textToRead);
		//Update the root's question type
		root->question = questionType;

		myMap[textToRead] = 1;

		// if the questiontype is equal to Q, we build a tree step by step
		if (root->question == "Q:") {

			root->Yes = readHelper(root->Yes, inFile);
			root->No = readHelper(root->No, inFile);
		}

		return root;
		
	}
	// Create a helper function to output the file and traverse the whole tree
	void writeHealper(Node* root, ofstream& outFile) {

		if (root == nullptr) return;
		// Write back the root's data to the file
		outFile << root->text << endl;
		// Perform this operation to the whole bst
		writeHealper(root->Yes, outFile);
		writeHealper(root->No, outFile);
		
	}
	Node* askQuestion(Node* root) {
		

		if (root->question == "A:") {

			if (yesTo("Would your object happen to be " + root->text + "?")) {
				cout << "Great, I got it right!" << endl;
			}

			else {
				cout << "What is the name of your object?";
				string temp;
				getline(cin, temp);
				Node* temp1 = root;
				cout << "Please give me a yes/no question that" << endl;
				cout << "distinguishes between your object" << endl;
				cout << "and mine ----> ";
				getline(cin, temp);
				root = new Node(temp);
				root->question = "Q:";
				cout << "And what is the answer for your object? (y/n)?";
				getline(cin, temp);

				if (temp == "y") {
					root->Yes = new Node(temp);
					root->Yes->question = "A:";
					root->No = temp1;
				}
				else {
					root->Yes = temp1;
					root->No = new Node(temp);
					root->No->question = "A:";
				}
			}
		}
		else {
			if (yesTo(root->text)) {
				root->Yes = askQuestion(root->Yes);
			}
			else {
				root->No = askQuestion(root->No);
			}
		}
		return root;
	
	}
	string adJustString(string input) {  
		//change string to Lower case
		for (int i = 0; input[i] != '\0'; i++) {

			if (input[i] >= 'A' && input[i] <= 'Z') {          // if upper case, change to lower case
				input[i] += 32;
			}
		}
		return input;
	}
	
	
public:
	
	// Constructor for Question Game
	QuestionGame() {
		// Initialize the default root to be computer
		root = new Node("computer");
		numberOfQuestions = 0;

	}

	// Destructor for cleaning the memory
	~QuestionGame() {
		// delete the whole tree
		
		cleanMemory(root);


	}
	int countQuestions() {

		for (auto it = myMap.begin(); it != myMap.end(); it++) {
			numberOfQuestions++;
		}
		return numberOfQuestions;
	}
	// Create a vector to store all the question
	/* void dfs(Node* root, vector<Node*>& ret) {
		if (root == nullptr) return;
		ret.push_back(root);
		dfs(root->left, ret);
		dfs(root->right, ret);


	} */

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
	void askQuestions() {

		Node* finalAnswer = askQuestion(root);

	}
	bool yesTo(string prompt) {

		cout << prompt + " (y/n)? ";
		string response;
		getline(cin, response);
		response = adJustString(response);

		while (response != "y" && response != "n") {  //while not y/n, keep ask
			cout << "Please enter y or n " << endl;
			cout << prompt + " (y/n)? ";

			getline(cin, response);
			response = adJustString(response);
		}

		if (response == "y") {

			return true;
		}
		return false;
	}




	



};

