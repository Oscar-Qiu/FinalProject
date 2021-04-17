// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<fstream>
#include"QuestionGame.h"
using namespace std;


int main()
{
	cout << "Welcome to the cse143 question program." << endl;
	cout << endl;
	// Create a infile stram to the file
	ifstream inFile("spec-questions.txt");
	// Create an output file stream
	ofstream outFile("OutTest.txt");
	// Create a QuestionGame Object
	QuestionGame* question = new QuestionGame;
	if (question->yesTo("Do you want to read in the previous tree?")) {
		question->read(inFile);
	}
	cout << endl;
	do {
		cout << "Please think of an object for me to guess.";
		question->askQuestions();
		cout << endl;



	} while (question->yesTo("Do you want to go again?"));
	question->write(outFile);

	


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
