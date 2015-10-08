#ifndef GRAPH_H
#define GRAPH_H

#include "review.h"
#include "user.h"
#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <cfloat>
#include <string>
#include "hashtable.h"
#include <vector>

//this is the node for the graph that I am going to use for D. algorithm
struct Node{
	Node(){
		distance = DBL_MAX;//distance = infinity (max number)
	}
	~Node(){}
	User* user;
	double distance;//distance from source to this node... for D. Algorithm
	//set<string, Review*> my_reviews;
	std::map<Node*, double> edges;
};

struct Graph{

	Graph(HashTable<std::string, User*>& users){
		for(HashTable<std::string, User*>::iterator it =  users.begin(); it != users.end(); ++it){
			Node* temp = new Node;
			temp->user = it->second;
			allnodes.insert(std::make_pair(it->first, temp));
		}
		for(std::map<std::string, Node*>::iterator it = allnodes.begin(); it != allnodes.end(); ++it){
			for(std::map<std::string, Node*>::iterator it_ = allnodes.begin(); it_ != allnodes.end(); ++it_){
				if(it != it_){
					it->second->edges.insert(std::make_pair(it_->second, 1));
				}
			}
		}
	}
	~Graph(){
		for(std::map<std::string, Node*>::iterator it = allnodes.begin();
		it != allnodes.end(); ++it){
			delete it->second;
		}
	}
	Node* get_first(){return allnodes.begin()->second;}
	void update_connection(Node* one, Node* two, double sim){
		one->edges.find(two)->second = sim;
		two->edges.find(one)->second = sim;
	}
	void update_connection(std::string one, std::string two, double sim){
		Node* n1 = allnodes.find(one)->second;
		Node* n2 = allnodes.find(two)->second;
		update_connection(n1, n2, sim);
	}
	Node* getNode(std::string name){
		std::map<std::string, Node*>::iterator it = allnodes.find(name);
		if(it != allnodes.end()){
			return it->second;
		}
		else{
			return NULL;
		}
	}

	//Used only for debug
	void printd(){
		for(std::map<std::string, Node*>::iterator it = allnodes.begin(); it != allnodes.end(); ++it){
			std::cout<<"Username: "<<it->second->user->getName()<<std::endl;
			std::cout<<" This is the d_al distance"<<it->second->distance<<std::endl;
			std::cout<<std::endl;
		}
	}
	void print(){
		for(std::map<std::string, Node*>::iterator it = allnodes.begin(); it != allnodes.end(); ++it){
			std::cout<<"Username: "<<it->second->user->getName()<<std::endl;
			for(std::map<Node*, double>::iterator it_ = it->second->edges.begin(); it_ != it->second->edges.end(); ++it_){
				std::cout<<it_->first->user->getName()<<" "<<it_->second<<std::endl;
			}
		}
		printd();
	}


	std::map<std::string, Node*> allnodes;
};

struct Comp_node{
	bool operator()(const Node* lhs, const Node* rhs){
		return lhs->distance < rhs->distance;
	}
};


#endif