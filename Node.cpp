#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(int newValue) {
  value = newValue;
  left = NULL;
  right = NULL;
}

Node::~Node() {
  cout << "Node destroyed." << endl;
}

char Node::getValue() {
  return value;
}

void Node::setValue(int newValue) {
  value = newValue;
}

Node* Node::getLeft() {
  return left;
}

void Node::setLeft(Node* newLeft) {
  left = newLeft;
}

Node* Node::getRight() {
  return right;
}

void Node::setRight(Node* newRight) {
  right = newRight;
}
