#include "my_datastore.h"
#include "util.h"
#include "product.h"
#include "user.h"
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string> 
#include <sstream>
#include "heap.h"

using namespace std;

MyDataStore::MyDataStore(){}
MyDataStore::~MyDataStore(){
	SimilaritiesGraph = NULL;
	set<Product*>::iterator it = storage.begin();
	while(it != storage.end()){
		delete *it;
		++it;
	}


	HashTable<string, User*>::iterator it_u =  all_users.begin();
	while(it_u != all_users.end()){
		delete it_u->second;
		++it_u;
	}

	//deleting reviews
	map<string, vector<Review*> >::iterator it_review;
	it_review = review_map.begin();
	while(it_review != review_map.end()){

		for(vector<Review*>::iterator it = it_review->second.begin(); it != it_review->second.end(); ++ it)
			delete *it;
		++it_review;
	}

	delete SimilaritiesGraph;

}
void MyDataStore::addProduct(Product* new_){
	storage.insert(new_);
	product_storage.insert(make_pair(new_->getName(), new_));


	set<string> words = new_->keywords();

	for(set<string>::iterator it = words.begin(); it != words.end(); ++it){
		SplayTree<string, set<Product*> >::iterator itkeys = all_keys.find(*it);
		if(itkeys == all_keys.end()){
			set<Product*> v;
			v.insert(new_);
			all_keys.insert(make_pair(*it, v));
		}
		else{
			itkeys->second.insert(new_);
		}
	}
}
void MyDataStore::addUser(User* u){
	all_users.insert(make_pair(u->getName(), u));
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
	int i = terms.size()-1;
	set<Product*>holder;



	if(type == 1){
		while(i >= 0){
			SplayTree<string, set<Product*> >::iterator it = all_keys.find(terms[i]);
			if(it != all_keys.end()){
				holder = setUnion(holder, it->second);
			}
		--i;
		}
	}
	else if(type == 0){
		while(i >= 0){
			SplayTree<string, set<Product*> >::iterator it = all_keys.find(terms[i]);
			if(it != all_keys.end()){
				if(!holder.empty()){
					holder = setIntersection(holder, it->second);
					if(holder.empty())
						break;
				}
				else
					holder = it->second;
			}
			else if(it == all_keys.end()){
				holder.clear();
				break;
			}
		--i;
		}

	}

	vector<Product*> return_;
	for(set<Product*>::iterator it = holder.begin();
	it != holder.end();
	it++) return_.push_back(*it);

	return return_;
} 

void MyDataStore::dump(ostream& ofile){
	string all_info;
	ofile<<"<products>"<<endl;
	for(set<Product*>::iterator it = storage.begin();
	it != storage.end();
	++it){
		(*it)->dump(ofile);
	}
	ofile<<"</products>"<<endl;

	ofile<<"<users>"<<endl;


	HashTable<string, User*>::iterator it_ =  all_users.begin();
	while(it_ != all_users.end()){
		it_->second->dump(ofile);
		++it_;
	}

	ofile<<"</users>"<<endl;
	ofile<<"<reviews>"<<endl;
	map<string, vector<Review*> >::iterator it = review_map.begin();
	while(it != review_map.end()){
		for(unsigned int i = 0; i < it->second.size(); ++i){
			it->second.at(i)->dump(ofile);
		}
		++it;
	}
	ofile<<"</reviews>";
}

User* MyDataStore::search_user(string user_name){
	User* it = all_users.find(user_name);
	if(it != NULL){
		return it;
	}
	else{return NULL;}
} 

Product* MyDataStore::search_product(string product_name){
	return product_storage.find(product_name)->second;
}

void MyDataStore::addReview(Review* r){

	map<string, vector<Review*> >::iterator it = review_map.find(r->prodName);
	if(it == review_map.end()){
		vector<Review*> v;
		v.push_back(r);
		review_map.insert(make_pair(r->prodName, v));
	}
	else{
		it->second.push_back(r);
	}

	map<string, set<string> >::iterator its = review_set.find(r->username);
	if(its == review_set.end()){
		set<string> vs;
		vs.insert(r->prodName);
		review_set.insert(make_pair(r->username, vs));
	}
	else{
		its->second.insert(r->prodName);
	}

	sendrating(r->prodName, r->rating);
}

void MyDataStore::sendrating(string name, int rate){
	Product* temp = search_product(name);
	temp->addrating(double(rate));
}

Product* MyDataStore::calc_basic_similarities(string name){
	delete SimilaritiesGraph;
	SimilaritiesGraph = new Graph(all_users);
	for(map<string, Node*>::iterator it = SimilaritiesGraph->allnodes.begin();
	it != SimilaritiesGraph->allnodes.end(); ++it){

		Node* temp = SimilaritiesGraph->getNode(it->first);

		for(map<Node*, double>::iterator it_ = temp->edges.begin();
		it_ != temp->edges.end(); ++it_){
			intersect(temp->user->getName(), it_->first->user->getName());
		}

	}

	calc_redefined(name);
	return calc_recomendation(name);
}

void MyDataStore::intersect(string name1, string name2){
	map<string, set<string> >::iterator itn1 = review_set.find(name1);
	map<string, set<string> >::iterator itn2 = review_set.find(name2);
	if((itn1 != review_set.end()) && (itn2 != review_set.end())){
		set<string> intersection = setIntersection(itn2->second, itn1->second);
		if(intersection.size() != 0){
			double similar = 0;
			double n1 = 0;
			double n2 = 0;
	 		for(set<string>::iterator it = intersection.begin(); it != intersection.end();++it){
	 			vector<Review*>* v = &(review_map.find(*it)->second);
	 			for(unsigned i = 0; i < v->size(); ++i){
	 				if(v->at(i)->username == name1){
	 					n1 = double(v->at(i)->rating);
	 				}
	 				else if(v->at(i)->username == name2){
	 					n2 = double(v->at(i)->rating);
	 				}
	 			}
	 			similar += double((double(abs(n1-n2)))/(double(4.0)));
	 		}
	 		similar = similar/double(intersection.size());
	 		SimilaritiesGraph->update_connection(name1, name2, similar);
	 	}
	}
}

void MyDataStore::calc_redefined(string name){
	D_algorithm(SimilaritiesGraph->getNode(name));
}

void MyDataStore::D_algorithm(Node* begin){
	begin->distance = double(0);
	Heap<Node*, Comp_node> D_minheap(2, Comp_node());
	for(map<string, Node*>::iterator it = SimilaritiesGraph->allnodes.begin();
		it != SimilaritiesGraph->allnodes.end(); ++it){
		D_minheap.push(it->second);
	}
	while(!D_minheap.empty()){
		Node* min_node = D_minheap.top();
		D_minheap.pop();
		for(map<Node*, double>::iterator it = min_node->edges.begin();
			it != min_node->edges.end(); ++it){
			double tempdistance = min_node->distance + it->second;
			if(tempdistance < it->first->distance){
				it->first->distance = tempdistance;
				D_minheap.update(it->first);
			}
		}
	}
}

Product* MyDataStore::calc_recomendation(string name){
	Set_S.clear();
	//iterator itp first: name of product; second: Product*
	for(map<string, Product*>:: iterator itp = product_storage.begin();
	itp != product_storage.end(); ++itp){
		set<string> subset_S;
		Set_S.insert(make_pair(itp->first, subset_S));
		map<string, set<string> >::iterator it_setS = Set_S.find(itp->first);

		for(map<string, set<string> >::iterator itr = review_set.begin();
		itr != review_set.end(); ++ itr){
			set<string>::iterator it3 = itr->second.find(it_setS->first);
			if(it3 != itr->second.end()){
				it_setS->second.insert(itr->first);
			}
		}
	}
	//removing set and key from where the the user is
	map<string, set<string> >::iterator it = Set_S.begin();
	while(it != Set_S.end()){
		if(it->second.find(name) != it->second.end()){
			map<string, set<string> >::iterator itcopy = it;
			++it;
			Set_S.erase(itcopy);
		}
		else{++it;}
	}
	return calculate_sum(name);
}

Product* MyDataStore::calculate_sum(string name){
	Product* prod_rec = NULL;//returning product

	//I used the review_set and review_map to get r(B,P)
	map<string, double> Set_R;
	//initializing the set of sum for each product in Set_S
	for(map<string, set<string> >::iterator it = Set_S.begin();it!=Set_S.end(); ++it){
		Set_R.insert(make_pair(it->first, 0));
	}


	//this Node* points to a Node that contains the similarities with his neighbors
	Node* A_node = SimilaritiesGraph->allnodes.find(name)->second;
	//for every user B for every product in set_S
	string rec_product_name;
	double max_rec = 0;
	for(map<string, set<string> >::iterator it = Set_S.begin();it!=Set_S.end(); ++it){
		map<string,double>::iterator itR = Set_R.find(it->first);
		double R_P = 0;//Let R(P) be the sum of (1-s(B,A))*r(B,P), over all users B in S.
		double W = 0;//Let W be the sum of (1-s(B,A)) over all users B in S.

		for(set<string>::iterator it2 = it->second.begin(); it2!=it->second.end();++it2){
			//finding Node* of the username
			Node* temp_node = SimilaritiesGraph->allnodes.find(*it2)->second;

			//findig basig similarities between users
			double s_B_A = A_node->edges.find(temp_node)->first->distance;
			double r_B_P = 0;
			string P = it->first;//currrent product in set_S, useful to calculate r(B,P)
			string B = *it2;//current usert in subset of set_S
			map<string, vector<Review*> >::iterator itreviews = review_map.find(P);
			if(itreviews != review_map.end()){
				for(unsigned int i = 0; i < itreviews->second.size();++i){
					if(itreviews->second.at(i)->username == B){
						r_B_P = itreviews->second.at(i)->rating;
					}
				}
			}

			R_P += ( double(1)- s_B_A) * (r_B_P);
			W += (double(1) - s_B_A);
		}

		if(W != 0){
			itR->second = R_P/W;
			if(max_rec < R_P/W){
				max_rec = R_P/W;
				rec_product_name = it->first;
			}
		}
		else{
			itR->second = 0;
		}
	}
	if(max_rec == 0){
		prod_rec = NULL;
	}
	else{
		prod_rec = product_storage.find(rec_product_name)->second;
	}
	return prod_rec;
}