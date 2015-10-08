#include <string>
#include <iostream>
#include "hashtable.h"

using namespace std;

int main(){

	cout<<"printing 7 pairs"<<endl;
	HashTable<string, int>* t = new HashTable<string, int>;
	t->insert(make_pair("a",2));
	t->insert(make_pair("m",4));
	t->insert(make_pair("n",12));
	t->insert(make_pair("b",5));
	t->insert(make_pair("e",5));
	t->insert(make_pair("d",4));
	t->insert(make_pair("v",0));
	cout<<"Size should be 7:" <<t->getSize()<<endl;
	t->print();



	cout<<endl<<"This should print the same as before.. inserting repeated values at the end"<<endl;
	t->insert(make_pair("e",5));
	t->insert(make_pair("d",4));
	t->insert(make_pair("v",0));
	t->print();
	

	cout<<endl<<"Removing pair <b,5>"<<endl;
	t->remove("b");
	t->print();



	cout<<endl<<"Removing something that does exist: z"<<endl;
	t->remove("z");

	cout<<endl<<"Testing the iterator"<<endl;
	for(HashTable<string, int>::iterator it = t->begin(); it != t->end(); ++ it){
		cout<<it->first<<" "<<it->second<<endl;
	}

	delete t;


	return 0;
}