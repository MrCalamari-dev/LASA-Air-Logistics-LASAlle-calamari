#include "string"
using namespace std;
/*
Class Library File
*/

struct Node{
  void * data;
  Node * next; 
};

class slist{
public:
  Node * head;
  Node * current;
// Constructor
  slist();
// Destructor
  ~slist();
// add(value)				//Adds a new value to the end of this list.
  void add(void * a);
// clear()					//Removes all elements from this list.
  void clear();
// equals(list)				//Returns true if the two lists contain the same elements in the same order.
  bool equals(slist * s);
//get(index)				//Returns the element at the specified index in this list.
  Node* get(int index);
//insert(index, value)		//Inserts the element into this list before the specified index.
  void insert(int index, void * a);
//exchg(index1, index2)		//Switches the payload data of specified indexex.
  void exchg(int index1, int index2);
//swap(index1,index2)		//Swaps node located at index1 with node at index2
  void swap(int index1, int index2);
// isEmpty()				//Returns true if this list contains no elements.
  bool isEmpty();
// remove(index)			//Removes the element at the specified index from this list.
  void remove(int index);
// set(index, value)		//Replaces the element at the specified index in this list with a new value.
  void set(int index, void * a);
// size()					//Returns the number of elements in this list.
  int size();
// DO NOT IMPLEMENT >>> subList(start, length)	//Returns a new list containing elements from a sub-range of this list.
  slist* subList(int start, int length);
// DO NOT IMPLEMENT >>> toString()				//Converts the list to a printable string representation.
  string toString();

  Node* getLast();
};
