#ifndef MY_DATASTORE_H
#define MY_DATASTORE_H

#include "datastore.h"
#include "product.h"
#include "util.h"
#include "review.h"
#include "splaytree.h"
#include "user.h"
#include "hashtable.h"
#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "graph.h"

class MyDataStore : public DataStore{
public:
	//typedef std::unordered_map<string, unordered_map<std::string, int> > BSimMap;
	MyDataStore();
	~MyDataStore();
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	User* search_user(std::string);
	void addReview(Review* r);
	void dump(std::ostream& ofile);
	Product* calc_basic_similarities(std::string);
	void intersect(std::string, std::string);
	std::map<std::string, std::vector<Review*> > review_map;//name of the product who wrote the revire and the review
private:
	Graph* SimilaritiesGraph;
	//key: product name. value: key:username, value:User
	std::map<std::string, std::set<std::string> > Set_S;//Let S be the set of all other users who have rated P, for all users
	std::map<std::string, std::set<std::string> > review_set;//name of users and their reviews
	HashTable<std::string, User*> all_users;
	std::set<Product*> storage;
	SplayTree<std::string, std::set<Product*> > all_keys;
	std::map<std::string, Product*> product_storage;


	void calc_redefined(std::string);
	Product* calc_recomendation(std::string);
	Product* calculate_sum(std::string);
	Graph* RedefinedSimilarities;
	Product* search_product(std::string);
	void sendrating(std::string, int);
	void D_algorithm(Node*);
};
#endif