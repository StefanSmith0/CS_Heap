#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

class Node {
public:
  Node(int);
  ~Node();
  char getValue();
  void setValue(int);
  Node* getLeft();
  void setLeft(Node*);
  Node* getRight();
  void setRight(Node*);
private:
  int value;
  Node* left;
  Node* right;
};
#endif
