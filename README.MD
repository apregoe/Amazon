# Homework 8.. DO NOT DO $ qmake -project, hw8.pro was edited

- **Name**: Albert Daniel Prego
- **USC ID**: 5844165389
- **Email**: prego@usc.edu
 

**DO NOT DO $ qmake -project, hw8.pro was edited**

- **Note:** the hash function is in **hash.h**

## Compiling instructions for **trojanshop.cpp**
- $ qmake
- $ make
- $ ./hw8 input.txt

## Bells and whistles **Go to for test files: $ cd bells/**

### 1. (2 bells and whistles) Hash Tables: Create a map to store your user information...

- The implemantation is **hashtable.h**, the test file is **hashtest.cpp**
compile: $ make hashtest
run: $ ./hashtest

I created a generic HashTable that uses chaining to store the user information. Please notice it has its own iterator class since I have to iterate to get the User* to create the graph for the similarities. I used the hash function providede in the assignment, I just mod it by the size.

####public functions:
- void print();// prints all keys and values...each "///////"means a new column.
- unsigned getSize();
- void remove(KeyType name);
- ValueType find(KeyType name);
- ValueType operator[](KeyType key);
- void insert(std::pair<KeyType, ValueType> t);
- HashTable();//default constructor

####private functions:
- int hash_(KeyType c);
- void resize();//resizes and rehashes when p>0.5

### 4. (5 bells and whistles) Splay Tree: Implement your keyword search with a map that allows lookup by strings ...

- The implementation is in **splaytree.h**, the test file is **splaytest.cpp**
compile: $ make splaytest
run: $ ./splaytest

I created a generic SplayTree class that inherits from the BynarySearchTree provided by homework7.

#### public functions:
-typename BinarySearchTree<KeyType,ValueType>::iterator find(const KeyType& k);
-void insert(const std::pair<const KeyType, ValueType>& new_item);

####private functions:
- **Note:** I did not implement remove(KeyType&); since I never use it.
- void climb(Node_<KeyType,ValueType>* current_node_);//splays current_node until it is the root
- Node_<KeyType, ValueType>* internalFind(const KeyType& k, bool& found) const;
- bool AmIleftzigzig(Node_<KeyType,ValueType>* node_);
- bool AmIrightzigzig(Node_<KeyType,ValueType>* node_);
- bool AmIleftzigzag(Node_<KeyType,ValueType>* node_);
- bool AmIrightzigzag(Node_<KeyType,ValueType>* node_);
- void rotateRight(Node_<KeyType, ValueType>* node_);
- void rotateLeft(Node_<KeyType, ValueType>* node_);
- bool AmIaRightChild(const Node_<KeyType, ValueType>* new_item);
- bool AmIaLeftChild(const Node_<KeyType, ValueType>* new_item);