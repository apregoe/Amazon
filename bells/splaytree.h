#include "bst.h"
#include <iostream>
#include <exception>
#include <cstdlib>

template<typename KeyType, typename ValueType>
class SplayTree : public BinarySearchTree<KeyType,ValueType>{

private:
	Node_<KeyType, ValueType>* internalFind(const KeyType& k, bool& found) const {
		Node_<KeyType, ValueType> *curr = BinarySearchTree<KeyType,ValueType>::root;
		Node_<KeyType,ValueType>* last_visited = BinarySearchTree<KeyType,ValueType>::root;
		while (curr) {
			if (curr->getKey() == k) {
				found =  1;
		    	return curr;
			}
			else if (k < curr->getKey()) {
				last_visited = curr;
				curr = curr->getLeft();
			}
			else {
				last_visited = curr;
			    curr = curr->getRight();
			}
		}
		return last_visited;
	}

public:
	typename BinarySearchTree<KeyType,ValueType>::iterator find(const KeyType& k){
		if(BinarySearchTree<KeyType,ValueType>::root != NULL){
			bool found = 0;
			Node_<KeyType,ValueType>* searched_node_ = this->internalFind(k, found);
			climb(searched_node_);
			if(found){
				typename BinarySearchTree<KeyType,ValueType>::iterator it(searched_node_);
				return it;
			}
			else{
				typename BinarySearchTree<KeyType,ValueType>::iterator it(NULL);
				return it;
			}
		}
		else{
			typename BinarySearchTree<KeyType,ValueType>::iterator it(NULL);
			return it;
		}
	}

	void insert(const std::pair<const KeyType, ValueType>& new_item){
		if(BinarySearchTree<KeyType,ValueType>::root == NULL){
	      Node_<KeyType,ValueType>* root_ = new Node_<KeyType, ValueType>(new_item.first, new_item.second, NULL);
	      root_->setLeft(NULL);
	      root_->setRight(NULL);
	      BinarySearchTree<KeyType, ValueType>::root = root_;
	      return;
		}
		else{
    		Node_<KeyType,ValueType>* tobefixed = new Node_<KeyType, ValueType>(new_item.first, new_item.second, NULL); 
    		BinarySearchTree<KeyType,ValueType>::insert(tobefixed);
    		climb(tobefixed);
		}
	}

protected:
	void climb(Node_<KeyType,ValueType>* current_node_){
		if(current_node_ == NULL);//NULL calse
		else if(current_node_->getParent() == NULL);//if current is the root
		else if(current_node_->getParent()->getParent() == NULL){
			
			if(AmIaRightChild(current_node_)){
				rotateLeft(current_node_->getParent());
			}
			else if(AmIaLeftChild(current_node_)){
				rotateRight(current_node_->getParent());
			}
		}
		else{
			//case 2: leftzig-zig:
			if(AmIleftzigzig(current_node_)){
				rotateRight(current_node_->getParent()->getParent());
				rotateRight(current_node_->getParent());
			}
			else if(AmIrightzigzig(current_node_)){//case 2: rightzig-zig
				rotateLeft(current_node_->getParent()->getParent());
				rotateLeft(current_node_->getParent());

			}
			else if(AmIleftzigzag(current_node_)){
				//case 3: leftzig-zag. current node_ is leftchild
				//parent of current node_ is right child
				rotateRight(current_node_->getParent());	
				rotateLeft(current_node_->getParent());
			}
			else if(AmIrightzigzag(current_node_)){
				//case 3: right zigzag
				rotateLeft(current_node_->getParent());
				rotateRight(current_node_->getParent());
			}
			climb(current_node_);
		}
	}
	/*		g
	  	   / \
	      p
	     /
	   node_     */
	bool AmIleftzigzig(Node_<KeyType,ValueType>* node_){
		if(AmIaLeftChild(node_)){
			if(AmIaLeftChild(node_->getParent())){
				return true;
			}
			return false;
		}
		return false;
	}
	/*		g
	  	   / \
	          p
	  		   \
	          node_  */
	bool AmIrightzigzig(Node_<KeyType,ValueType>* node_){
		if(AmIaRightChild(node_)){
			if(AmIaRightChild(node_->getParent())){
				return true;
			}
			return false;
		}
		return false;
	}


	/*		g
	  	   / \
	          p
	  		 /
	       node_   */
	bool AmIleftzigzag(Node_<KeyType,ValueType>* node_){
		if(AmIaLeftChild(node_)){
			if(AmIaRightChild(node_->getParent())){
				return true;
			}
			return false;
		}
		return false;
	}
	/*		g
	  	   / \
	      p
	       \
	      node_   */
	bool AmIrightzigzag(Node_<KeyType,ValueType>* node_){
		if(AmIaRightChild(node_)){
			if(AmIaLeftChild(node_->getParent())){
				return true;
			}
			return false;
		}
		return false;
	}

	void rotateRight(Node_<KeyType, ValueType>* node_){
		Node_<KeyType,ValueType>* temp = node_->getLeft();
		node_->setLeft(node_->getLeft()->getRight()); 

		if(temp->getRight() != NULL){
			temp->getRight()->setParent(node_);  
		}

		temp->setParent(node_->getParent());

		if(node_->getParent() == NULL){
			BinarySearchTree<KeyType, ValueType>::root = temp;
		}
		else{
			if(AmIaRightChild(node_)){
				node_->getParent()->setRight(temp);
			}
			else{
				node_->getParent()->setLeft(temp);
			}  
		}

		temp->setRight(node_);
		node_->setParent(temp);
	}
	  
	void rotateLeft(Node_<KeyType, ValueType>* node_){

		Node_<KeyType,ValueType>* temp = node_->getRight();
		node_->setRight(node_->getRight()->getLeft());

		if(temp->getLeft() != NULL){
			temp->getLeft()->setParent(node_);
		}

		temp->setParent(node_->getParent());

		if(node_->getParent() == NULL){
			BinarySearchTree<KeyType, ValueType>::root = temp;
		}
		else{
			if(AmIaLeftChild(node_)){
				node_->getParent()->setLeft(temp);
			}
			else{
				node_->getParent()->setRight(temp);
			}
		}

		temp->setLeft(node_);
		node_->setParent(temp);
	}
	bool AmIaRightChild(const Node_<KeyType, ValueType>* new_item){
		if(new_item->getParent() == NULL){
		  return 0;
		}
		return new_item->getParent()->getRight() == new_item;
	}

	bool AmIaLeftChild(const Node_<KeyType, ValueType>* new_item){
		if(new_item->getParent() == NULL){
		  return 0;
		}
		return new_item->getParent()->getLeft() == new_item;
	}
};