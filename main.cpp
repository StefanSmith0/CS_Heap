#include <iostream>
#include <time.h>

using namespace std;

void printTree(int heapSize, int *array);
void swap(int firstIndex, int secondIndex, int *array);
void maxHeapify(int *array, int heapSize, int i);
void sort(int *array, int &heapSize);
void siftdown(int *array, int heapSize, int i);
void build(int *array, int heapSize);

int main() {
  int heapSize = 21;
  int heap[heapSize] = {0};

  srand(time(NULL));
  for(int i = 1; i < heapSize; i++) {
    heap[i] = (rand() % 999) + 1;
  }
  printTree(heapSize, heap);

  cout << "Building..." << endl;
  build(heap, heapSize);
  printTree(heapSize, heap);

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

//prints the array
void printTree(int heapSize, int *array) {
  for(int i = 1; i < heapSize; i++) {
    cout << array[i] << " ";
  }
  cout << endl;
}
