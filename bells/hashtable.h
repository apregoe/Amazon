#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <cmath>


template <typename KeyType, typename ValueType>
class HashTable {
public:
	class iterator{
	public:
		iterator(std::vector<std::pair<KeyType, ValueType> >** data, int i, int j, int* size){
			this->data = data;
			this->i = i;
			this->j = j;
			this->size = size;
		}
		~iterator(){}
		std::pair<KeyType,ValueType>& operator*(){
			return (data[i]->at(j));
		}

		std::pair<KeyType,ValueType>* operator->(){
			return &data[i]->at(j);
		}

		bool operator==(const iterator& rhs) const{
			if((rhs.i >= *this->size) && (this->i >= *this->size)){
				return true;
			}
			if((rhs.i >=* this->size) && (this->i < *this->size)){
				return false;
			}
			if((rhs.i < *this->size) && (this->i >= *this->size)){
				return false;
			}
			return (rhs.data[i]->at(j) == (*this).data[i]->at(j));
		}

		bool operator!=(const iterator& rhs) const{
			return !(*this == rhs);
		}

	    iterator& operator++(){
	      if(i >= *size){return *this;}
	      else{
		  	if(j >= data[i]->size()-1){
		  		j = 0;
		  		++i;
		  		if(i<*size){
			  		while(data[i]->size() == 0){
						++i;
						if(i >= *size){break;}
					}
					return *this;
				}
				else{
					return *this;
				}
		  	}
		  	else{
		  		++j;
			  	return *this;
		  	}
	      }
	    }
	protected:
		std::vector<std::pair<KeyType, ValueType> >** data;
		int i;
		int j;
		int* size;
	};

	
	iterator end(){
		iterator it(data, size, 0, &size);
		return it;
	}

	iterator begin(){
		int i = 0;
		while(data[i]->size() == 0){
			++i;
			if(i >= size)break;
		}
		iterator it(data,i,0,&size);
		return it;
	}

	HashTable(){
		this->size = 3;
		amount = 0;
		data = new std::vector<std::pair<KeyType, ValueType> >*[size];

		for(int i = 0; i < size; i++) {
			data[i] = new std::vector<std::pair<KeyType, ValueType> >;
		}
	}
	~HashTable(){
		for(int i = 0; i < size; i++) {
			delete data[i];
		}
		delete [] data;
	}

	void insert(std::pair<KeyType, ValueType> t){

		if(amount/double(size) >= 0.5){
    		this->resize();
  		}

		int hash = this->hash_(t.first);
		// do the rest here!

		for(unsigned int i = 0; i < data[hash]->size(); ++i){
			if(data[hash]->at(i).first == t.first){
				return;
			}
		}
		data[hash]->push_back(t);
		++amount;
	}


	ValueType find(KeyType name){
		int hash = hash_(name);

		for(unsigned int i = 0; i < data[hash]->size(); ++i){
			if(data[hash]->at(i).first == name){
				return data[hash]->at(i).second;
			}
		}
		return NULL;
	}

	ValueType operator[](KeyType key){
		return find(key);
	}

	void remove(KeyType name){
		int hash = hash_(name);

		for(unsigned int i= 0; i < data[hash]->size(); ++i){
			if(data[hash]->at(i).first == name){
				data[hash]->erase(data[hash]->begin()+i);
				--amount;
			}
		}
	}

	unsigned getSize(){return (unsigned)(int(amount));}

	void print(){
		for(int i = 0; i < size; ++i){
			std::cout<<"////////"<<std::endl;
			for(unsigned int j = 0; j < data[i]->size();++j){
				std::cout<<data[i]->at(j).first<<" "<<data[i]->at(j).second<<std::endl;
			}
		}
	}

private:
	int hash_(KeyType c){

		long long int id = 0;
		int i = c.length() -1;
		int j = 0;
		while(i >= 0){
			id += (long long)((int(c[i]))*(pow((long long)128,j)));
			--i;
			++j;
		}
		unsigned int digits[4] = {0};
		for(int i = 3; i >=0; --i){
			digits[i]=id%size;
			id = id/size;
		}

		return ((digits[0]*45912)+ (digits[1]*35511) + (digits[2]*65169) +(digits[3]*4625))%size;
	}
	void resize(){
		int old = size;
		size = 2*size + 1;
		std::vector<std::pair<KeyType, ValueType> >** temp = new std::vector<std::pair<KeyType, ValueType> >*[size];
		for(int i = 0; i < size; i++) {
			temp[i] = new std::vector<std::pair<KeyType, ValueType> >;
		}

		//rehashing
		for(int i=0; i < old; i++){
			for(unsigned int j = 0; j < data[i]->size(); ++j){

				KeyType key = data[i]->at(j).first;
				ValueType value = data[i]->at(j).second;
				std::pair<KeyType, ValueType> p(key, value);

				int hash = hash_(key);

				temp[hash]->push_back(p);
			}
		}

		for(int i = 0; i < old; i++) {
			delete data[i];
		}
		delete [] data;
		data = temp;
	}
	std::vector<std::pair<KeyType, ValueType> >** data;
	int size;
	double amount;
};

#endif