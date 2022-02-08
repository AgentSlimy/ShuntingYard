#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

void push(Node* &top, char* value);
void pop(Node* &top);
void peek();
//void enqueue();
//void dequeue();

int main() {
  Node* top = NULL;
  
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

