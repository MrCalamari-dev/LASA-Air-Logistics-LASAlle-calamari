#include "slist.h"
#include <iostream>
using namespace std;

/*
Class Library File
*/


// Constructor
  slist::slist(){
    head = new Node();
    head->next = nullptr;
    head->data = NULL;
    current = head;
  }
// Destructor
  slist::~slist(){
   // cout<<"The slist has been destroyed";
  }

  void slist::add(void * a){
    current = head;
    while(current->next!=NULL){
      current = current->next;
    }
    Node* newNode = new Node;
    newNode->data = a;
    newNode->next = NULL;
    current->next = newNode;
  }
// clear()					//Removes all elements from this list.
  void slist::clear(){
    current = head; 
    while(current != NULL){
      Node* temp = current;
      current = current->next;
      delete temp;
    }
  }
// equals(list)				//Returns true if the two lists contain the same elements in the same order.
  bool slist::equals(slist * s){
    if(s->size()!=this->size()){
      return false;
    }
    current = head;
    s->current = s->head;
    while(current != NULL){
      if(current->data != s->current->data){
        return false;
      }
      current = current->next;
      s->current = s->current->next;
    }
    return true;
  }
//get(index)				//Returns the element at the specified index in this list.
  Node* slist::get(int index){
    current = head;
    for(int x = 0; x <= index; x++){
      current = current->next;
      if(current == NULL){
        cout<<"Index too large";
        break;
      }
    }
    return current;
  }
//insert(index, value)		//Inserts the element into this list before the specified index.
  void slist::insert(int index, void * a){
    Node* newNode = new Node;
    Node* temp;
    newNode->data = a;
    
    current = head;
    for(int x = 0; x < index; x++){
      current = current->next;
      
      if(current == NULL)
      {
        cout<<"Index too large";
        break;
      }
      
      if(x==index-2)
        temp = current;
    }
    temp->next = newNode;
    newNode->next = current;
     
  }
//exchg(index1, index2)		//Switches the payload data of specified indexex.
  void slist::exchg(int index1, int index2){
    if(index1==index2)
    {
      cout<<"Indeces are the same"; 
      return;
    }
      
    Node * node1;
    Node * node2;
    Node * temp;

    node1 = get(index1);
    node2 = get(index2);

    temp->data = node1->data;
    node1->data = node2->data;
    node2->data = temp->data;
    
  }
//swap(index1,index2)		//Swaps node located at index1 with node at index2
  void slist::swap(int index1, int index2){
    if(index1==index2)
    {
      cout<<"Indeces are the same"; 
      return;
    }

    Node * node1;
    Node * node2;
    Node * temp;

    node1 = get(index1);
    node2 = get(index2);

    temp = node1;
    node1 = node2;
    node2 = temp;

  }
// isEmpty()				//Returns true if this list contains no elements.
  bool slist::isEmpty(){
    if(head == NULL)
      return true;
    return false;
  }
// remove(index)			//Removes the element at the specified index from this list.
  void slist::remove(int index){
    Node* before = (index-1<0)?head:get(index-1);
    Node* temp = get(index);
    Node* after = temp->next;

    before->next = after;
    delete temp;
  }
// set(index, value)		//Replaces the element at the specified index in this list with a new value.
  void slist::set(int index, void * a){
    get(index)->data = a;
  }
// size()					//Returns the number of elements in this list.
  int slist::size(){
    current = head->next;
    int count = 0;
    while(current != NULL){
      current = current->next;
      count++;
    }
    
    return count;
  }

// subList(start, length)	//Returns a new list containing elements from a sub-range of this list
  slist* slist::subList(int start, int end){
    slist * newList = new slist();
    current = head;
    int count = 0;
    while(count<=start){
      current = current->next;
      count++;
    }
    while(count<=end){
      newList->add(current->data);
      current = current->next;
      count++;
    }
    //cout<<newList->size()<<endl;
    return newList;
  }

  Node* slist::getLast(){
    current = head;
    while(current->next!=NULL){
      current = current->next;
    }
    return current;
  }