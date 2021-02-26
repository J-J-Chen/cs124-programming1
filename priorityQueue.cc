#include <cmath>
#include <stdio.h>
#include "priorityQueue.h"

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
  size_++;
  int new_index = size_ - 1;
  heap_[new_index] = val;
  while(new_index != 0 && heap_[(new_index-1)/2]->closest_distance > heap_[new_index]->closest_distance) {
    Randmst::node *temp = heap_[new_index];
    heap_[new_index] = heap_[new_index/2];
    heap_[new_index/2] = temp;
    new_index = (new_index - 1) / 2;
  }
  return true;
}

void PriorityQueue::resort(Randmst::node* val) {
  int loc = 0;
  for(int i = 0; i < size_; ++i) {
    if(heap_[i] == val) {
      loc = i;
      break;
    }
  }

  if(loc == -1) {
    printf("NOOOO\n");
    return;
  }

  while(heap_[loc]->closest_distance > heap_[(loc-1)/2]->closest_distance) {
    Randmst::node *temp = heap_[(loc-1)/2];
    heap_[(loc-1)/2] = heap_[loc];
    heap_[loc] = temp;
    loc = (loc - 1) / 2;
    minHeapify(loc);
  }
  minHeapify(loc/2);
}

void PriorityQueue::minHeapify(int i) {
  int l = 2*i +1; 
  int r = 2*i +2; 
  int smallest = i; 
  if (l < size_ && heap_[l]->closest_distance < heap_[i]->closest_distance) 
    smallest = l; 
  if (r < size_ && heap_[r]->closest_distance < heap_[smallest]->closest_distance) 
    smallest = r; 
  if (smallest != i) {
    Randmst::node* temp = heap_[i];
    heap_[i] = heap_[smallest];
    heap_[smallest] = temp;
    minHeapify(smallest); 
  } 
}

Randmst::node* PriorityQueue::pop() {
  if(size_ == 0) return nullptr;
  if(size_ == 1) {
    --size_;
    return heap_[0];
  }
  Randmst::node *to_pop = heap_[0];
  heap_[0] = heap_[size_-1];
  --size_;
  minHeapify(0); 
  return to_pop;
}

