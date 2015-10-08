#ifndef MSORT_
#define MSORT_

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <math.h>
#include <set>
#include "review.h"
#include "product.h"

struct AlphaStrComp {
    bool operator()(const Product* lhs, const Product* rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs->getName() < rhs->getName(); 
    }
 };

 struct ReviewComp{

 	bool operator()(const Review* lhs, const Review* rhs){
 		return *lhs < *rhs;//lhs->operator<(*rhs);
 	}

 };

 struct RateComt{
 	bool operator()(const Product* lhs, const Product* rhs){
 		return lhs->getAverage() < rhs->getAverage();
 	}
 };

template <class T, class Comparator>
void merge(std::vector<T>& v, double low, double middle, double high, Comparator comp){
  std::vector<T> temp;

  for(int i = low; i<=high; ++i)
    temp.push_back(v[i]);

  int i = low;
  int j = middle +1;
  int k = low;
  while( i <= middle && j <= high){
    if(comp(temp[i-low], temp[j-low])){
      v[k] = temp[i-low];
      ++i;
    }
    else{
      v[k] = temp[j-low];
      ++j;
    }
    ++k;
  }
  while(i <= middle){
    v[k] = temp[i-low];
    ++k;
    ++i;
  }
}

template <class T, class Comparator>
void helper1_(std::vector<T>& v, int low, int high, Comparator comp){
  if(low < high){
    int middle = (low+high)/2;
    helper1_(v, low, middle, comp);
    helper1_(v, middle+1, high, comp);
    merge(v, low, middle, high, comp);
  }
}

template <class T, class Comparator>
void mergeSort(std::vector<T>& vec_, Comparator comp){

	if(vec_.size() == 0)
		return;

	helper1_(vec_, 0, vec_.size() -1, comp);
	return;
}

#endif