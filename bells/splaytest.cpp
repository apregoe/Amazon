#include <iostream>
#include <string>
#include "splaytree.h"

using namespace std;

int main(){
	SplayTree<string, int>* t = new SplayTree<string,int>;

	cout<<"printing 7 pairs"<<endl;
	t->insert(make_pair("a",2));
	t->insert(make_pair("m",4));
	t->insert(make_pair("n",12));
	t->insert(make_pair("b",5));
	t->insert(make_pair("e",5));
	t->insert(make_pair("d",4));
	t->insert(make_pair("v",0));
	t->print();

	cout<<endl<<"result after finding a and v"<<endl;
	t->find("a");
	t->find("v");
	t->print();

	delete t;


}