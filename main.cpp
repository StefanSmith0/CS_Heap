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
#include <fstream>

using namespace std;

void printTree(int heapSize, bool isLeft, int *array, int index, const string &prefix);
void swap(int firstIndex, int secondIndex, int *array);
void maxHeapify(int *array, int heapSize, int i);
void sort(int *array, int &heapSize);
void siftdown(int *array, int heapSize, int i);
void build(int *array, int heapSize);
void stringToHeap(int *array, char* input, int &heapSize);
int spaces(char* input);
void stringFromFile(char* input, char* inputFileName, bool &success);

int main() {
  int heapSize = 101;
  int heap[heapSize] = {0};
  string prefix = "";
  char input[30];
  bool validCmd = false;
  while(!validCmd) {
    cout << "Fill heap manually, randomly, or by file? (m/r/f): ";
    cin >> input;
    cin.clear();
    cin.ignore();
    if(!strcmp(input, "q")) {
      return 0;
    }
    if(!strcmp(input, "m")) {
      char manual[350] = {0};
      char* manualInput = manual;
      int newHeapSize = 0;
      cout << "Enter numbers separated by spaces, hit return to finish." << endl;
      cin.getline(manualInput, 350);
      stringToHeap(heap, manualInput, heapSize);
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
      char fileInput[350];
      char fileName[30];
      cout << "File name: ";
      cin.getline(fileName, 30);
      stringFromFile(fileInput, fileName, validCmd);
      if(validCmd) {
	stringToHeap(heap, fileInput, heapSize);
      }
    }
    else {
      cout << "Command not recognized." << endl;
    }
  }
  
  printTree(heapSize, false, heap, 1, prefix);
  
  cout << "Building..." << endl;
  build(heap, heapSize);
  printTree(heapSize, false, heap, 1, prefix);

  cout << "Sorting..." << endl;
  sort(heap, heapSize);
  return 0;
}

//Fills a char array from the first line of a file
void stringFromFile(char* input, char* inputFileName, bool &success) {
  fstream file;
  string output;
  int length = 0;
  file.open(inputFileName, ios::in);
  if(file.is_open()) {
    getline(file, output);
    file.close();
    strcpy(input, output.c_str());
    success = true;
  }
  else {
    cout << "Couldn't open file." << endl;
  }
}

//Counts the spaces in a string
int spaces(char* input) {
  int output = 0;
  int it = 0;
  while(input[it] != '\0') {
    if(input[it] == ' ') {
      output++;
    }
    it++;
  }
  return output;
}

//Extracts ints from a string, adds them to heap
void stringToHeap(int *array, char* input, int& heapSize) {
  int newHeapSize = 1;
  int intFromInput = 0;
  int intspaces = spaces(input);
  for(int i = 1; i < intspaces + 2; i++) {
    sscanf(input, "%d", &intFromInput);
    array[i] = intFromInput;
    newHeapSize++;
    if(intFromInput < 10) {
      input += 2;
    }
    else if(intFromInput < 100) {
      input += 3;
    }
    else if(intFromInput < 1000) {
      input += 4;
    }
    else {
      input += 5;
    }
  }
  heapSize = newHeapSize;
  cout << endl;
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
