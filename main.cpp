/*
  Stefan Smith
  4/3/2022
  Heap

  Commands:
  add - Adds a student to the list.
  delete - Removes a student from the list.
  print - Prints list to console.
  quit - Ends the program and deletes the list.

  Code Used:
  - printBT by Adrian Schneider - https://stackoverflow.com/users/2631225/adrian-schneider
 */

#include <iostream>
#include <time.h>
#include <string>
#include <cstring>

using namespace std;

void printTree(int heapSize, bool isLeft, int *array, int index, const string &prefix);
void swap(int firstIndex, int secondIndex, int *array);
void maxHeapify(int *array, int heapSize, int i);
void sort(int *array, int &heapSize);
void siftdown(int *array, int heapSize, int i);
void build(int *array, int heapSize);

int main() {
  int heapSize = 101;
  int heap[heapSize] = {0};
  string prefix = "";
  char input[30];
  bool validCmd = false;
  cout << "Fill heap manually, randomly, or by file? (m/r/f): ";
  while(!validCmd) {
    cin >> input;
    cin.clear();
    cin.ignore();
    if(!strcmp(input, "m")) {
      char manual[350] = {0};
      char* manualInput = manual;
      int newHeapSize = 0;
      cout << "Enter numbers separated by spaces, hit return to finish." << endl;
      cin.getline(manualInput, 350);
      int intFromInput;
      int len = sizeof(manual)/sizeof(manual[0]);
      for(int i = 1; i < manual.size(); i++) {
	sscanf(manualInput, "%d", &intFromInput);
	heap[i] = intFromInput;
	newHeapSize++;
	if(intFromInput < 10) {
	  manualInput += 2;
	}
	else if(intFromInput < 100) {
	  manualInput += 3;
	}
	if(intFromInput < 1000) {
	  manualInput += 4;
	}
	else {
	  manualInput += 5;
	}
      }
      heapSize = newHeapSize;
      validCmd = true;
    }
    else if(!strcmp(input, "r")) { 
      srand(time(NULL));
      for(int i = 1; i < heapSize; i++) {
	heap[i] = (rand() % 999) + 1;
      }
      validCmd = true;
    }
    else if(!strcmp(input, "f")) {

      validCmd = true;
    }
    else {
      cout << "Command not recognized." << endl;
      cout << "(m/r/f): ";
    }
  }
  
  printTree(heapSize, false, heap, 1, prefix);
  prefix = "";
  
  cout << "Building..." << endl;
  build(heap, heapSize);
  printTree(heapSize, false, heap, 1, prefix);

  cout << "Sorting..." << endl;
  sort(heap, heapSize);
  return 0;
}

//Builds heap
void build(int *array, int heapSize) {
  for(int i = (heapSize - 1 / 2); i > 0; i--) {
    siftdown(array, heapSize, i);
  }
}

//Sifts an element down array until sorted
void siftdown(int *array, int heapSize, int i) {
  int parent = array[i];
  int lchild = 0;
  int rchild = 0;
  if(heapSize > (i * 2)) {
    lchild = (i * 2);
  }
  if(heapSize > ((i * 2) + 1)) {
    rchild = (i * 2) + 1;
  }
  if(array[lchild] > parent || array[rchild] > parent) {
    if(array[lchild] > array[rchild]) {
      swap(i, lchild, array);
      siftdown(array, heapSize, lchild);
    }
    else {
      swap(i, rchild, array);
      siftdown(array, heapSize, rchild);
    }
  }
}

//Heapsort printed to console
void sort(int *array, int &heapSize) {
  int initialSize = heapSize;
  for(int i = 1; i < initialSize; i++) {
    cout << array[1] << " ";
    swap(1, heapSize, array);
    siftdown(array, heapSize, 1);
    heapSize--;
  }
  cout << endl;
}

//swaps two elements in an int array
void swap(int firstIndex, int secondIndex, int *array) {
  int tempValue = array[secondIndex];
  array[secondIndex] = array[firstIndex];
  array[firstIndex] = tempValue;
}

//Prints the heap as a horizontal tree - printBT by Adrian Schneider (modified)
void printTree(int heapSize, bool isLeft, int *array, int index, const string &prefix) {
  if(index < heapSize) {
    cout << prefix;

    cout << (isLeft ? "├──" : "└──" );
    
    cout << array[index] << endl;
    printTree(heapSize, true, array, (index * 2), prefix + (isLeft ? "|   " : "    " ));
    printTree(heapSize, false, array, (index * 2) + 1, prefix + (isLeft ? "|   " : "    " ));
  }
}
