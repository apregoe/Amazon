#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>
#include <vector>
#include <iostream>
#include <functional>
#include <string>
#include <cmath>

template <typename T, typename Comparator >
class Heap{
  public:
    /// Constructs an m-ary heap for any m >= 2
    Heap(int m, Comparator c);

    /// Destructor as needed
    ~Heap();

    /// Adds an item
    void push(const T&);

    /// returns the element at the top of the heap 
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;
    void print();
    void update(const T& t_){//has to be guaranteed that T is in heap
      int i = 0;
      while(heap[i] != t_){++i;}
      trickleUp(i);
    }

  private:
    /// Add whatever helper functions and data members you need below
    void swap(int const idx1, int const idx2);
    int height();
    void heapify(const int);
    int find_min_max(std::vector<T> const, int const);
    void trickleUp(int);
    std::vector<T> heap;
    int order;
    Comparator comp;
};

template <typename T, typename Comparator>
Heap<T, Comparator>::~Heap(){}

template <typename T, typename Comparator>
void Heap<T, Comparator>::print(){
  for(int i = 1; i < heap.size(); ++i)
    std::cout<<heap[i]->distance<<" ";
  std::cout<<std::endl;
}



template <typename T, typename Comparator>
void Heap<T, Comparator>::heapify(int idx){
  if(heap.size()-1 <= (order*(idx-1) +1)){
    return;
  }
  std::vector<T> v;
  v.clear();
  for(int i =1; i<= order; ++i){
    if((order*(idx-1) +1 + i) < heap.size())
      v.push_back(heap[order*(idx-1) + 1 + i]);
    else
      break;
  }
  int min_max = find_min_max(v, idx);
  if(comp(heap[min_max], heap[idx])){
    swap(min_max, idx);
    heapify(min_max);
  }
  return;
}



template <typename T, typename Comparator>
int Heap<T, Comparator>::find_min_max(std::vector<T> v, int idx){
  int min_max = 0;
  for(int i = 0; i < v.size(); ++i){
    if(comp(v[i], v[min_max]))
      min_max = i;
  } 
  return order*(idx-1) + 1 + min_max + 1;
}

// Add implementation of member functions here
template <typename T, typename Comparator >
Heap<T, Comparator >::Heap(int m, Comparator c) : order(m) {
  comp = c;
}

template <typename T, typename Comparator >
void  Heap<T, Comparator>::push(const T& t){
  heap.push_back(t);
  if(heap.size() == 1)
    heap.push_back(t);
  trickleUp(heap.size() -1);
}

template <typename T, typename Comparator >
void Heap<T, Comparator>::trickleUp(int loc){
  int parent = floor(((double(loc-2))/double(order)) + 1);
  while((parent>=1) && comp(heap[loc], heap[parent])) {
    swap(loc, parent);
    loc = parent;
    parent = floor(((double(loc-2))/double(order)) + 1);
  }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap[1];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop(){
  if(empty())
    throw std::logic_error("can't pop an empty heap");

  heap[1] = heap.back();
  heap.pop_back();
  heapify(1);
}

template <typename T, typename Comparator>
bool Heap<T, Comparator >::empty() const{
  return heap.size() <= 1;
}

template <class T, class Comparator>
void Heap<T, Comparator >::swap(int idx1, int idx2){
  
  if(empty() or (idx1 > heap.size() )or (idx2 > heap.size()) or (idx2 < 1) or (idx1 < 1)){
    throw std::logic_error("Index in heap out of bounds");
  }

  std::vector<T> v;
  v.push_back(heap[idx1]);
  heap[idx1] = heap[idx2];
  heap[idx2] = v[0];
  return;
}

template <class T, class Comparator>

int Heap<T, Comparator>::height(){
  if(heap.size() <= 1)
    return 0;

  return int(ceil(log(this->order, this->heap.size()-1)));
}


#endif

