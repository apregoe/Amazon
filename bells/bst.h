/**
 * bst.h
 *  Implements a(n unbalanced) BST storing Key,Value pairs
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/* -----------------------------------------------------
 * Regular Binary Tree Node_s 
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
  class Node_ {
 public:
  Node_ (const KeyType & k, const ValueType & v, Node_<KeyType, ValueType> *p)
    : _item(k, v)
   // the default is to create new node_s as leaves
    { _parent = p; _left = _right = NULL; }
  
  virtual ~Node_()
  { }
  
  std::pair<const KeyType, ValueType> const & getItem () const
    { return _item; }
  
  std::pair<const KeyType, ValueType> & getItem ()
    { return _item; }
  
  const KeyType & getKey () const
  { return _item.first; }
  
  const ValueType & getValue () const
  { return _item.second; }
  
  /* the next three functions are virtual because for Red-Black-Trees,
     we'll want to use Red-Black node_s, and for those, the 
     getParent, getLeft, and getRight functions should return 
     Red-Black node_s, not just ordinary node_s.
     That's an advantage of using getters/setters rather than a struct. */
  
  virtual Node_<KeyType, ValueType> *getParent () const
    { return _parent; }
  
  virtual Node_<KeyType, ValueType> *getLeft () const
    { return _left; }
  
  virtual Node_<KeyType, ValueType> *getRight () const
    { return _right; }
  
  
  void setParent (Node_<KeyType, ValueType> *p)
  { _parent = p; }
  
  void setLeft (Node_<KeyType, ValueType> *l)
  { _left = l; }
  
  void setRight (Node_<KeyType, ValueType> *r)
  { _right = r; }
  
  void setValue (const ValueType &v)
  { _item.second = v; }
  
 protected:
  std::pair<const KeyType, ValueType> _item;
  Node_ <KeyType, ValueType> *_left, *_right, *_parent;
};








/* -----------------------------------------------------
 * Regular Binary Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class BinarySearchTree {
 protected:
  // Main data member of the class
  Node_<KeyType, ValueType> *root;

 public:
  /**
   * Constructor
   */
  BinarySearchTree () {root = NULL; }

  /**
   * Destructor
   */
  ~BinarySearchTree () { deleteAll (root); }

  void insert(Node_<KeyType,ValueType>* n){
    insert_(n, root);
  }

  /**
   * Prints the entire tree structure in a nice format 
   *  
   * It will denote subtrees in [] brackets.
   *  This could be helpful if you want to debug your functions. 
   */  
  void print () const
  { 
    printRoot (root);
    std::cout << "\n";
  }
  /**
   * An In-Order iterator
   *  !!! You must implement this !!!
   */
  class iterator {
  public:
    /**
     * Initialize the internal members of the iterator
     */
    iterator(Node_<KeyType,ValueType>* ptr){
    	curr = ptr;
    }
    
    std::pair<const KeyType,ValueType>& operator*()
      { return curr->getItem();  }
    
    std::pair<const KeyType,ValueType>* operator->() 
      { return &(curr->getItem()); }
    
    /**
     * Checks if 'this' iterator's internals have the same value
     *  as 'rhs'
     */
    bool operator==(const iterator& rhs) const{
      	return (rhs.curr == (*this).curr);
    }
    
    /**
     * Checks if 'this' iterator's internals have a different value
     *  as 'rhs'
     */
    bool operator!=(const iterator& rhs) const{
      return !(*this == rhs);
    }
    
    /*
     * Advances the iterator's location using an in-order sequencing
     */
    iterator& operator++(){
      if(curr == NULL){return *this;}
      if(AmIlastnode_(curr)){
      	curr = NULL;
      	return *this;
      }
      else if(curr->getRight() != NULL){
        curr = curr->getRight();
        while(curr->getLeft() != NULL){curr = curr->getLeft();}
        return *this;
      }
      else{
        while(1){
          if(curr->getParent() == NULL){
            curr = NULL; 
            return *this;
          }
          if(curr->getParent()->getLeft() == curr){
            curr = curr->getParent();
            return *this;
          }
          curr = curr->getParent();
        }
      }
    }
    
    
    Node_<KeyType, ValueType>* curr;
    protected:
    //you are welcome to add any necessary variables and helper functions here.
    bool AmIlastnode_(Node_<KeyType,ValueType>* n){
    	if(n->getRight() != NULL){
    		return 0;
    	}

    	while(n->getParent() != NULL){
    		if(n->getParent()->getKey() < n->getKey()){
    			n = n->getParent();
    			continue;
    		}
    		return 0;
    	}
    	return 1;

    }

  };
  /**
   * Returns an iterator to the "smallest" item in the tree
   */
  iterator begin(){
    Node_<KeyType, ValueType>* temp = root;
    while(temp->getLeft() != NULL){
    	temp = temp->getLeft();
    }
    iterator ite(temp);
    return ite;
  }

  /**
   * Returns an iterator whose value means INVALID
   */
  iterator end(){
  	iterator ite(NULL);
    return ite;
  }

  /**
   * Returns an iterator to the item with the given key, k
   * or the end iterator if k does not exist in the tree
   */
  iterator find (const KeyType & k) const 
  {
    Node_<KeyType, ValueType> *curr = internalFind(k);
    iterator it(curr);
    return it;
  }
  
  
 protected:
  void insert_(Node_<KeyType,ValueType>* tobefixed, Node_<KeyType, ValueType>* temp){
    if(temp->getKey() == tobefixed->getItem().first){
      return;
    }
    else if(temp->getKey() > tobefixed->getItem().first){
      if(temp->getLeft() == NULL){
        tobefixed->setParent(temp);
        temp->setLeft(tobefixed);
        temp->getLeft()->setLeft(NULL);
        temp->getLeft()->setRight(NULL);
        return;
      }
      else{
        insert_(tobefixed, temp->getLeft());
      }
    }
    else{
      if(temp->getRight() == NULL){
        tobefixed->setParent(temp);
        temp->setRight(tobefixed);
        temp->getRight()->setRight(NULL);
        temp->getRight()->setLeft(NULL);
        return;
      }
      else{
        insert_(tobefixed, temp->getRight());
      }
    }
  } 
  /**
   * Helper function to find a node_ with given key, k and 
   * return a pointer to it or NULL if no item with that key
   * exists
   */
  Node_<KeyType, ValueType>* internalFind(const KeyType& k) const 
  {
      Node_<KeyType, ValueType> *curr = root;
      Node_<KeyType,ValueType>* last_visited = root;
      while (curr) {
        if (curr->getKey() == k) {
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
  
  /**
   * Helper function to print the tree's contents
   */
  void printRoot (Node_<KeyType, ValueType> *r) const
  {
    if (r != NULL)
      {
	std::cout << "[";
	printRoot (r->getLeft());
	std::cout << " (" << r->getKey() << ", " << r->getValue() << ") ";
	printRoot (r->getRight());
	std::cout << "]";
      }
  }
  
  /**
   * Helper function to delete all the items
   */
  void deleteAll (Node_<KeyType, ValueType> *r)
  {
    if (r != NULL)
      {
	deleteAll (r->getLeft());
	deleteAll (r->getRight());
	delete r;
      }
  }
};

/* Feel free to add member function definitions here if you need */
