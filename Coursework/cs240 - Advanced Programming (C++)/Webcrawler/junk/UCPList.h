#ifndef CS240_UCP_LIST_H
#define CS240_UCP_LIST_H
#include "URLCountPair.h"

//! LLNode implements a doubly-linked list node
class LLNode {
		friend class UCPList;  //!< MyList can access private members of LLNode
	public:
	
		//!  Constructor
		LLNode(URLCountPair* const v, LLNode * p, LLNode * n) :
		  value(v), prev(p), next(n)
		{
		}
	
		//!  Read-only public methods for use by clients of the LinkedList class
		URLCountPair* const GetValue() const
		{
		  return value;
		}
	
		//! Self-explanatory
		LLNode * GetPrevious()const
		{
		  return prev;
		}
	
		//! Self-explanatory
		LLNode * GetNext()const
		{
		  return next;
		}
		
	private:
		URLCountPair* value;        //!< value stored in the node in a void pointer
		LLNode * prev;            //!< pointer to previous node in the list
		LLNode * next; 			//!< pointer to next node in the list
};


//! LinkedList implements a doubly-linked list
class UCPList
{
	public:
	
		//!  No-arg constructor.  Initializes an empty linked list
		UCPList();	
	
		//!  Destructor
		~UCPList();
	
		//!  @return true if the list is empty, or false if the list is not empty
		bool IsEmpty() const;
	
	
		//!  Removes all values from the list
		void Clear();
	
	
		//!  @return the number of values in the list
		int GetSize() const;
	
	
	
		//!  @return a pointer to the first node in the list, or NULL if the list is empty
		LLNode * GetFirst()const;
	
	
	
		//!  @returns a pointer to the last node in the list, or NULL if the list is empty
		LLNode * GetLast()const;
	
	
		//!  Inserts value v into the list after node n
		//!  
		//!  @param v The new value being inserted
		//!  @param n A node that is already in the list after which the new node should 
		//!      be inserted.
		//!      If n is NULL, the new node should be inserted at the beginning of the list.
		//!
		//!  @return a pointer to the newly inserted node
		LLNode * Insert(URLCountPair* const v, LLNode * n);
	
	
		//! Searches for the first occurrence of value v that appears in the list 
		//!   after node n
		//!   
		//!  @param v The value being searched for
		//!  @param n The node in the list after which the search should begin.
		//!      If n is NULL, the list should be searched from the beginning.
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not found
		LLNode * Find(URLCountPair* const v, LLNode * n) const;
	
	
		//!  Removes node n from the list
		//!  
		//!  @param n The node being removed from the list
		void Remove(LLNode * n);
	
	private:
		int size; //the size of the list
		LLNode* first; // a pointer to the first element
		LLNode* last; // a pointer to the last element
		//! Deallocates all memory
		void Free();
};


#endif

