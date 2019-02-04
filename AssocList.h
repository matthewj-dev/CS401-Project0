/*	
 * Project 0 -- Part 1: AssocList.h (required for everyone)	
 ****************************************** 
 * 
 * Your task is to complete the following AssocList class so that all
 * methods behave as expected and the class satisfies the IMap interface.  	
 * The class is templated so that it may be used for various key (K) and  	
 * value (V) types. The structure stores keys themselves, and pointers  	
 * to values. This is so the 'lookup' method may return a null pointer  	
 * when a key cannot be found. 'remove' returns true if a key-value is	
 * found and removed and false if no change was made. 'add' replaces 	  
 * an existing value for the input key or adds a new key-value pair. 
 * The ctor sets up an empty association list, the dtor properly cleans up  	
 * the datastructure (freeing used memory) and 'size' reports the # of keys. 
 * (See IMap.h for more details.) There are various correct ways to complete 	  
 * the assignment, ask if you have questions. Search for "TODO" in this file.  	
 * 
 ***************************************
 */ 


#pragma once  	

#include "IMap.h" 
#include <iostream>
using namespace std;


/*************************************** 
 * Honor pledge (please write your name.) 	  
 *
 * I **Matthew Jackson** have completed this code myself, without 	  
 * unauthorized assistance, and have followed the academic honor code. 
 * 
 * Edit the code below to complete your solution.
 *  	
 ****************************************** 
 */ 


template <typename K, typename V> 
class AssocList  	
	: public IMap<K,V>
{	
    // A private struct useful for links of the list
    struct Link  	
	{	
		K k; 
		V* v;
		Link* next;

		Link(const K _k, V* const _v, Link* const _next) 
		    : k(_k), v(_v), next(_next)  	
		{  	
		} 
	};	

private:
	// A counter for the total number of keys in the association list 	  
    unsigned count; 	  

	// A pointer to the root node 
    Link* root; 	  

public: 
    AssocList() 
	    : count(0), root(0) 
	{  	
	} 

	~AssocList()  	
	{ 	  
		 while (root)
		 	remove(root->k);
	}

	// A method for mutably extending the map with a new key-value association 
	void add(const K& key, V* const val) 
	{ 	  
		// TODO: write add method

		// point to the root ptr
		Link** node = &root;

		// check for empty structure
		if(!(*node)){
			
			// make new node
			Link* firstNode = new Link(key, val, nullptr);

			// assign root ptr to newly created node struc
			*node = &(*firstNode);

			// increment size by 1
			count++;

		}
		else {

			// check for next node
			while((*node)->next && ((*node)->next)->k != key){
				// move node ptr from previous link struc to the next
				node = &((*node)->next);

			}

			if((*node)->next && ((*node)->next)->k == key){
				((*node)->next)->v = val;
			}
			else {
				// make a new node
				Link* newNode = new Link(key, val, nullptr);

				//assign new node to the next ptr
				(*node)->next = &(*newNode);

				// increment size by 1
				count++;
			}



		}
	} 	  

	// A method for mutably deleting a key (and its value) from the current map 	  
	bool remove(const K& key) 	  
	{  	
		// TODO: write remove method

		// start at root, else continue
		if(root && root->k == key){

			// if root does not have a next then delete node
			if(!(root->next)){
				delete root;	// delete struc
				root = nullptr; // nullify root
				count--;	// decrement size
				return true;	// confirm deletion
			}
			delete root;	// delete the struc at root
			root = root->next;	// move root ptr to next
			count--;	// decrement size
			return true;	// confirm deletion
		}
		else {

			// make a local var to root
			Link* node = root;

			if(!node){return false;}

			// go through list until key is found in next
			while(node->next && (node->next)->k != key) {
				node = node->next;
			}

			// if key is found then change next field to the next next
			if(node->next && (node->next)->k == key) {

				// copy to be deleted key's next
				Link* temp = (node->next)->next;

				// delete node with key
				delete node->next;

				// change current next field into next's next
				node->next = temp;

				// decrement size
				count--;

				// confirm deletion
				return true;
			}

		}


		return false;
	}	
  	
	// A method for looking up the value associated with a given key 	  
	V* lookup(const K& key) const 
	{ 	  
		// Start at the root
		Link* node = root;
 
		// Follow the linked list until reaching null 	  
		// or a node where the key matches  	
        while (node && node->k != key) {
			node = node->next;  
		}
				
		// Return the associated value, or null  	
		if (node)  	
			return node->v;
		else 	  
			return 0; 	  
	}

	// A method for reporting the current number of keys in the map 	  
	unsigned size() const
	{ 
        // TODO: write size method 
		return count;
	} 	  
}; 	  

 	  


