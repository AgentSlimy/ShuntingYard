#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

void push(Node* &top, char* value);
void pop(Node* &top);
void peek(Node* top);
int precedence(char* p);

//void enqueue();
//void dequeue();

int main() {
  Node* top = NULL;
  Node* front = NULL;
  Node* rear = NULL;

  int signCount = 0;
  int numCount = 0;

  bool running = true;
  char command[10];
  char input[100];
  
  cout << "Welcome to Shunting Yard" << endl;

  while (running == true) {
    cout << endl << "Options: Calculate or Quit" << endl;
    cin.get(command, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(command, "Calculate") == 0 || strcmp(command, "calculate") == 0) { // Calculate command
      cout << "-------Calculate-------" << endl << endl;
      cout << "Input equation in the infix notation:";
      cin.get(input, 100);
      cin.clear();
      cin.ignore(10000, '\n');
      char** modifyIf = new char*[100];
      top = NULL;
      front = NULL;
      rear = NULL;
      int first = 0; //Keeps track of the # of chars before space
      int inputCount = 0; //Number of chars
      for (int i = 0; i < strlen(input); i++) {
	if (input[i] == ' ') {
	  if (first == 1) {
	    char *temp = new char[10];
	    for (int z = 0; z < sizeof(temp); z++) {
	      temp[z] = 0;
	    }
	    temp[0] = input[i-1];
	    modifyIf[inputCount] = temp;
	    inputCount++;
	    first = 0;
	  }
	  else {

	  }
    }
    else if (strcmp(command, "Quit") == 0 || strcmp(command, "quit") == 0) { //Quit command
      cout << "--Quitting Shunting Yard--" << endl;
      running = false;
    }
    else { //Input is not the word calculate or quit
      cout << endl << "Invalid input, try again." << endl;
    }
  }
}

void push(Node* &top, char* value) {
  Node* temp = new Node();
  temp->setData(value);
  temp->setNext(top);
  top = temp;
}

void pop(Node* &top) {
  if (top == NULL) {
    cout << "Empty" << endl;
  }
  else {
    Node* temp = top;
    top = top->getNext();
    temp->setNext(NULL);
  }
}

void peek(Node* top) {
  if (top == NULL) {
    cout << "Stack is empty" << endl;
    Node* none = new Node();
    return none;
  }
  else {
    return top;
  }
}

//Determines the importance of characters
int precedence(char* p) {
  if (*p == '^') {
    return 3; //Highest
  }
  else if (*p == '*' || *p == '/') {
    return 2; //Second highest
  }
  else if (*p == '+' || *p == '-') {
    return 1; //Second lowest
  }
  else if (*p == '(' || *p == ')') {
    return 5;
  }
  else {
    return 0; //Lowest, which are the numbers
  }
}
