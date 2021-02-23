#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

class PriorityQueue {
  public:
    ~PriorityQueue();
    typedef int DataType;
    PriorityQueue(unsigned int capacity);
    unsigned int size() const;
    bool empty() const;
    bool full() const;
    bool print() const;
    DataType top() const;
    bool add(DataType val);
    bool pop();
    void swap();

  private:
    DataType* heap_;
    unsigned int capacity_;
    unsigned int size_;
};
#endif
