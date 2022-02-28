//Author: Nathan Zou
//Date: 3/2/22
//Shunting Yard Algorithm with help from Stefan Ene and Chris Zou
/*Other Online Sources:

 */

#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

//Stack functions
void push(Node* &top, char* value);
void pop(Node* &top);
void peek(Node* top);
//Precedence function
int precedence(char* p);
//Queue functions
void enqueue(Node* &front, Node* &rear, char* value);
void dequeue(Node* &front, Node* &rear);
bool isEmpty(Node* front, Node* rear);
void showFront(Node* front, Node* rear);
void displayQueue(Node* front, Node* rear);

int main() {
  Node* top = NULL; //Stack, latest node add in stack
  Node* front = NULL; //Queue, first node in queue
  Node* rear = NULL; //Queue, last node in queue

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
      cout << "Input equation in the infix notation: ";
      cin.get(input, 100);
      cin.clear();
      cin.ignore(10000, '\n');
      char** modifyIf = new char*[100]; //Used to clear char* array
      //Clear stack and queues
      top = NULL; 
      front = NULL;
      rear = NULL;
      int first = 0; //Keeps track of the # of chars before space
      int inputCount = 0; //Number of chars
      for (int i = 0; i < strlen(input); i++) {
	if (input[i] == ' ') {
	  if (first == 1) {
	    char *temp = new char[10];
	    for (int z = 0; z < sizeof(temp); z++) { //Clear temp memory
	      temp[z] = 0;
	    }
	    temp[0] = input[i-1];
	    modifyIf[inputCount] = temp;
	    inputCount++;
	    first = 0;
	  }
	  else {
	    char* temp = new char[10];
	    for (int z = 0; z < sizeof(temp); z++) { //Clear temp memory
	      temp[z] = 0;
	    }
	    for (int z = 0; z < 1; z++) {
	      temp[z] = input[i-1+z];
	    }
	    modifyIf[inputCount] = temp;
	    inputCount++;
	    first = 0;
	  }
	}
	else {
	  char* temp = new char[10];
	  for (int z = 0; z < sizeof(temp); z++) { //Clear temp memory
	    temp[z] = 0;
	  }
	  first++;
	  if (i == strlen(input) - 1) { //The last possible pair of chars
	    for (int z = 0; z < 1; z++) {
	      temp[z] = input[i+z+1-first];
	    }
	    modifyIf[inputCount] = temp;
	    inputCount++;
	  }
	}
      }
      cout << "Input Recieved" << endl << endl;
      for (int z = 0; z < inputCount; z++) { //Print out all tokens w/ the precedence of each
	cout << modifyIf[z] << " precedence: " << precedence(modifyIf[z]) << endl;
      }
      int sy = 0;
      //Start of Shunting Yard Algorithm
      while (sy < inputCount) {
	if (precedence(modifyIf[sy]) == 0) { //If token is a number
	  enqueue(front, rear, modifyIf[sy]);
	}
	if (precedence(modifyIf[sy]) == 1 || precedence(modifyIf[sy]) == 2 || precedence(modifyIf[sy]) == 3) { //If token is a operator
	  if (top != NULL) {
	    while (precedence(top->getData()) >= precedence(modifyIf[sy]) && *top->getData() != '(') { 
	      enqueue(front, rear, top->getData()); //pop from stack and enqueue on output queue
	      pop(top);
	      if (top == NULL) break;
	    }
	  }
	  push(top, modifyIf[sy]); //Push to stack
	}
	if (*modifyIf[sy] == '(') { //If token is a left parenthesis
	  push(top, modifyIf[sy]); //Push to stack
	}
	if (*modifyIf[sy] == ')') { //If token is a right parenthesis
	  while (*top->getData() != '(') {
	    enqueue(front, rear, top->getData());
	    pop(top);
	  }
	  if (*top->getData() == '(') {
	    pop(top); //Pop from stack and remove
	  }
	}
	sy++; //Next token
      }
      if (sy == inputCount) {
	while (top != NULL) {
	  enqueue(front, rear, top->getData());
	  pop(top);
	}
      }
      cout << "Binary Tree Created" << endl;
      displayQueue(front, rear);
      
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

/*void peek(Node* top) {
  if (top == NULL) {
    cout << "Stack is empty" << endl;
    Node* none = new Node();
    return none;
  }
  else {
    return top;
  }
  }*/

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

void enqueue(Node* &front, Node* &rear, char* value) {
  Node* temp = new Node();
  temp->setData(value);
  temp->setNext(NULL);
  if (front == NULL) {
    front = temp;
    rear = temp;
  }
  else {
    rear->setNext(temp);
    rear = temp;
  }
}

void dequeue(Node* &front, Node* &rear) {
  if (isEmpty(front, rear)) {
    cout << "Empty queue" << endl;
  }
  else if (front == rear) {
    front == NULL;
    rear == NULL;
  }
  else {
    Node* temp = front;
    front = front->getNext();
    temp->setNext(NULL);
  }
}

bool isEmpty(Node* front, Node* rear) {
  if (front == NULL && rear == NULL) {
    return true;
  }
  else {
    return false;
  }
}

void showFront(Node* front, Node* rear) {
  if (isEmpty(front, rear)) {
    cout << "Empty queue" << endl;
  }
  else {
    cout << front->getData();
  }
}

void displayQueue(Node* front, Node* rear) {
  if (isEmpty(front, rear)) {
    cout << "Empty queue" << endl;
  }
  else {
    Node* temp = front;
    while (temp != NULL) {
      cout << temp->getData() << " ";
      temp = temp->getNext();
    }
    cout << endl;
  }
}
