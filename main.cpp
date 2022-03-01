//Author: Nathan Zou
//Date: 3/2/22
//Shunting Yard Algorithm with help from Stefan Ene and Chris Zou
/*Other Online Sources:
    Stack & Queues: https://www.youtube.com/watch?v=kKjYSBeDpFA
                    https://www.youtube.com/watch?v=A3ZUpyrnCbM
    Shunting Yard Algorithm: https://en.wikipedia.org/wiki/Shunting-yard_algorithm
                             https://rosettacode.org/wiki/Parsing/Shunting-yard_algorithm
    Binary Tree: https://en.wikipedia.org/wiki/Binary_expression_tree
                 https://www.geeksforgeeks.org/binary-tree-set-1-introduction/
                 https://www.geeksforgeeks.org/binary-tree-set-2-properties/
    Infix->Postfix/Prefix: https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/
                           https://www.geeksforgeeks.org/convert-infix-prefix-notation/

 */

#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

//Stack functions
void push(Node* &top, char* value);
void pop(Node* &top);
Node* peek(Node* top);
//Precedence function
int precedence(char* p);
//Queue functions
void enqueue(Node* &front, Node* &rear, char* value);
void dequeue(Node* &front, Node* &rear);
bool isEmpty(Node* front, Node* rear);
void showFront(Node* front, Node* rear);
void displayQueue(Node* front, Node* rear);
//Tree functions
void pushTree(Node* &tree, Node* &add);
void popTree(Node* &tree);
//Display tree funcitons
void disInfix(Node* InF);
void disPrefix(Node* PreF);
void disPostfix(Node* PosF);

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
            char** modifyIf = new char* [100]; //Used to clear char* array
            //Clear stack and queues
            top = NULL;
            front = NULL;
            rear = NULL;
            int first = 0; //Keeps track of the # of chars before space
            int inputCount = 0; //Number of chars
            for (int i = 0; i < strlen(input); i++) {
                if (input[i] == ' ') {
                    if (first == 1) {
                        char* temp = new char[10];
                        for (int z = 0; z < sizeof(temp); z++) { //Clear temp memory
                            temp[z] = 0;
                        }
                        temp[0] = input[i - 1];
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
                            temp[z] = input[i - 1 + z];
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
                            temp[z] = input[i + z + 1 - first];
                        }
                        modifyIf[inputCount] = temp;
                        inputCount++;
                    }
                }
            }
            cout << "Input Recieved" << endl << endl << "Tokens: " << endl;;
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
                            if (top == NULL) {
                                break;
                            }
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
            cout << "Binary Tree Created From: " << endl;
            displayQueue(front, rear);
            cout << endl << "Created with " << inputCount << " tokens." << endl << endl;
            //Start of Binary Tree 
            Node* tree = NULL; //Top of tree stack
            //Turn queue into tree stack
            while (front != rear) {
                Node* t = new Node();
                t->setData(front->getData());
                pushTree(tree, t);
                front = front->getNext();
            }
            //Rear done same as front
            Node* t = new Node();
            t->setData(rear->getData());
            pushTree(tree, t);

            //Display final result
            cout << "in for infix notation, pre for prefix notation, or post for postfix notation" << endl;
            char display[5];
            cin.get(display, 5);
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "--Output--" << endl;
            if (strcmp(display, "in") == 0) { //infix notation
                disInfix(tree); 
            }
            else if (strcmp(display, "pre") == 0) { //prefix notation
                disPrefix(tree);
            }
            else if (strcmp(display, "post") == 0) { //postfix notation
                disPostfix(tree);
            }
            else {
                cout << "Input invalid, start over from the beginning you noob" << endl;
            }
            cout << endl << endl;
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

//Adds new elements at the end of stack
void push(Node* &top, char* value) { //Push function
    Node* temp = new Node();
    temp->setData(value);
    temp->setNext(top);
    top = temp;
}

//Removes newest added element
void pop(Node* &top) { //Pop function
    if (top == NULL) {
        cout << "Empty" << endl;
    }
    else {
        Node* temp = top;
        top = top->getNext();
        temp->setNext(NULL);
    }
}

//Semi-useless, already have top :/
Node* peek(Node* top) { //Peek function
  if (top == NULL) {
    cout << "Stack is empty" << endl;
    Node* none = new Node();
    return none;
  }
  else {
    return top;
  }
}

//Determines the importance of characters, Precedence function
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
        return 5; //Can be anything, as long as it is differentiated from the rest
    }
    else {
        return 0; //Lowest, which are the numbers
    }
}

//Adds node to queue 
void enqueue(Node* &front, Node* &rear, char* value) { //Enqueue function
    Node* temp = new Node();
    temp->setData(value);
    temp->setNext(NULL);
    if (front == NULL) { //No nodes yet
        front = temp;
        rear = temp;
    }
    else { //At least one node exists
        rear->setNext(temp);
        rear = temp;
    }
}

//Removes first node in queue
void dequeue(Node* &front, Node* &rear) { //Dequeue function
    if (isEmpty(front, rear)) {
        cout << "Empty queue" << endl;
    }
    else if (front == rear) { //If there is one node
        //Delete node
        front == NULL;
        rear == NULL;
    }
    else {
        Node* temp = front;
        front = front->getNext();
        temp->setNext(NULL);
    }
}

bool isEmpty(Node* front, Node* rear) { //IsEmpty function, used to check if queue is empty
    if (front == NULL && rear == NULL) {
        return true;
    }
    else {
        return false;
    }
}

void showFront(Node* front, Node* rear) { //ShowFront function
    if (isEmpty(front, rear)) {
        cout << "Empty queue" << endl;
    }
    else {
        cout << front->getData();
    }
}

void displayQueue(Node* front, Node* rear) { //DisplayQueue function
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

//Tree functions
void pushTree(Node* &tree, Node* &add) { //PushTree function
    if (tree == NULL) { //Empty tree
        add->setNext(tree);
        tree = add;
    }
    else {
        if (precedence(add->getData()) == 0) { //Checking for numbers
            add->setNext(tree);
            tree = add;
        }
        else { //If token is operator
            //Pop the last two nodes and keep them
            Node* left = tree;
            popTree(tree);
            left->setNext(NULL);
            Node* right = tree;
            popTree(tree);
            right->setNext(NULL);
            //Push operator node
            add->setNext(NULL);
            tree = add;
            //Make the two popped numbers left and right pointers of operator node
            tree->setLeft(left);
            tree->setRight(right);
        }
    }
}

void popTree(Node* &tree) { //PopTree function
    if (tree == NULL) {
        cout << "Tree stack is empty" << endl;
    }
    else {
        Node* temp = tree;
        tree = tree->getNext();
        temp->setNext(NULL);
    }
}

//Display tree functions
void disInfix(Node* InF) { //Display Infix Function
    if (InF != NULL) {
        if (precedence(InF->getData()) != 0) {
            cout << "( ";
        }
        disInfix(InF->getLeft());
        cout << InF->getData() << " ";
        disInfix(InF->getRight());
        if (precedence(InF->getData()) != 0) {
            cout << ") ";
        }
    }
}

void disPrefix(Node* PreF) { //Display Prefix Function
    if (PreF != NULL) {
        cout << PreF->getData() << " ";
        disPrefix(PreF->getLeft());
        disPrefix(PreF->getRight());
    }
}

void disPostfix(Node* PosF) { //Display Postfix Function
    if (PosF != NULL) {
        disPostfix(PosF->getLeft());
        disPostfix(PosF->getRight());
        cout << PosF->getData() << " ";
    }
}
