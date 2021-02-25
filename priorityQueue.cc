#include <cmath>
#include <malloc.h>
#include "priorityQueue.h"

PriorityQueue::PriorityQueue(unsigned int capacity) {
  capacity_ = capacity;
  size_ = 0;
  heap_ = new Randmst::node*[capacity_+1];
  //heap_ = (Randmst::node*) malloc(sizeof(Randmst::node*) * capacity + sizeof(Randmst::node*));
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
  heap_[++size_] = val;
  int new_index = size_;
  while(new_index/2 != 0 && heap_[new_index]->closest_distance > heap_[new_index/2]->closest_distance) {
    Randmst::node *temp = heap_[new_index];
    heap_[new_index] = heap_[new_index/2];
    heap_[new_index/2] = temp;
    new_index = new_index / 2;
  }
  return true;
}

Randmst::node* PriorityQueue::pop() {
  if(size_ == 0) return nullptr;
  //printf("HEAP SIZE: %d\n", size_);
  heap_[0] = heap_[size_];
  Randmst::node *to_pop = heap_[size_];
  --size_;
  int i = 1;
  int larger;
  while(2 * i < size_ && (heap_[i]->closest_distance < heap_[2*i]->closest_distance || 
        heap_[i]->closest_distance < heap_[2*i+1]->closest_distance)) {
    larger = (heap_[2*i]->closest_distance > heap_[2*i+1]->closest_distance) ? 2 * i : 2 * i + 1;
    Randmst::node *temp = heap_[i];
    heap_[i] = heap_[larger];
    heap_[larger] = temp;
    i = larger;
  }
  return to_pop;
}

