#include <cmath>
#include "priorityQueue.h"

//void MaxHeapify(Randmst::node* arr[], int i, int n);
//void convertMaxHeap(Randmst::node* arr[], int n);

PriorityQueue::PriorityQueue(unsigned int capacity) {
  capacity_ = capacity;
  size_ = 0;
  heap_ = new Randmst::node*[capacity_+1];
  for(int i = 0; i < capacity; ++i)
    heap_[i] = nullptr;
}

PriorityQueue::~PriorityQueue() {
  delete [] heap_;
}

unsigned int PriorityQueue::size() const {
  return size_;
}

bool PriorityQueue::empty() const {
  return size_ == 0;
}

bool PriorityQueue::full() const {
  return size_ == capacity_;
}

bool PriorityQueue::add(Randmst::node *val) {
  //if(full()) return false;
  //heap_[++size_] = val;
  size_++;
  int new_index = size_ - 1;
  heap_[new_index] = val;
  //int parent = ((int) new_index/2);
  //if(heap_[parent] > heap_[new_index]) {
    //Randmst::node *temp = heap_[parent];
    //heap_[parent] = heap_[new_index];
    //heap_[new_index] = temp;
  //}
  //while(new_index/2 != 0 && heap_[new_index]->closest_distance > heap_[new_index/2]->closest_distance) {
  while(new_index != 0 && heap_[new_index/2]->closest_distance > heap_[new_index]->closest_distance) {
    Randmst::node *temp = heap_[new_index];
    heap_[new_index] = heap_[new_index/2];
    heap_[new_index/2] = temp;
    new_index = new_index / 2;
  }
  return true;
}

void PriorityQueue::minHeapify(int i) {
  int l = 2*i +1; 
  int r = 2*i +2; 
  int smallest = i; 
  if (l < size_ && heap_[l]->closest_distance < heap_[i]->closest_distance) 
      smallest = l; 
  if (r < size_ && heap_[r]->closest_distance < heap_[smallest]->closest_distance) 
      smallest = r; 
  if (smallest != i) 
  { 
      Randmst::node* temp = heap_[i];
      heap_[i] = heap_[smallest];
      heap_[smallest] = temp;
      minHeapify(smallest); 
  } 
}

Randmst::node* PriorityQueue::pop() {
  if(size_ == 0) return nullptr;
  //convertMaxHeap(heap_, size_);
  //printf("HEAP SIZE: %d\n", size_);
  Randmst::node *to_pop = heap_[0];
  heap_[0] = heap_[size_-1];
  --size_;
  minHeapify(0); 
  /**
  int larger;
  while(2 * i < size_ && (heap_[i]->closest_distance < heap_[2*i]->closest_distance || 
        heap_[i]->closest_distance < heap_[2*i+1]->closest_distance)) {
    larger = (heap_[2*i]->closest_distance > heap_[2*i+1]->closest_distance) ? 2 * i : 2 * i + 1;
    Randmst::node *temp = heap_[i];
    heap_[i] = heap_[larger];
    heap_[larger] = temp;
    i = larger;
  }
  */
  return to_pop;
}
/**
void MaxHeapify(Randmst::node* arr[], int i, int n) 
{ 
    int l = 2*i + 1; 
    int r = 2*i + 2; 
    int largest = i; 
    if (l < n && arr[l]->closest_distance > arr[i]->closest_distance) 
        largest = l; 
    if (r < n && arr[r]->closest_distance > arr[largest]->closest_distance) 
        largest = r; 
    if (largest != i) 
    { 
        swap(arr[i], arr[largest]); 
        MaxHeapify(arr, largest, n); 
    } 
} 
  
// This function basically builds max heap 
void convertMaxHeap(Randmst::node* arr[], int n) 
{ 
    // Start from bottommost and rightmost 
    // internal mode and heapify all internal 
    // modes in bottom up way 
    for (int i = (n-2)/2; i >= 0; --i) 
        MaxHeapify(arr, i, n); 
} 
*/

