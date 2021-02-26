#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "randmst.h"

class PriorityQueue {
  public:
    ~PriorityQueue();
    PriorityQueue(unsigned int capacity);
    unsigned int size() const;
    bool empty() const;
    bool full() const;
    bool print() const;
    Randmst::node top() const;
    bool add(Randmst::node *val);
    Randmst::node *pop();
    void swap();
    void minHeapify(int i);
    void resort();

  private:
    Randmst::node** heap_;
    unsigned int capacity_;
    unsigned int size_;
};
#endif
