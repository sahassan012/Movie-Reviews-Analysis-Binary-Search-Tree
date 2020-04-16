/*bst.h*/

//
// Binary search tree
//
#pragma once
#include <iostream>
#include <algorithm>  // std::max

using namespace std;

template<typename TKey, typename TValue>
class binarysearchtree
{
	
private:
  //NODE struct that holds the key, value, and Left/Right pointer members. 
  struct NODE
  {
    TKey  Key;
	TValue Value;
    NODE* Left;
    NODE* Right;
  };
  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)

  // 
  // _inorder:
  //  _inorder does the actual inorder traversal and output 
  //  to console.  Each key is output to the console followed
  //  by " ", including the last key.
  //
  void _inorder(NODE* cur)
  {
     if (cur == nullptr)
       return;
     else
     {
        _inorder(cur->Left);
        cout << "Key: " << cur->Key << " " << "Value: " << cur->Value.PubYear << endl;
        _inorder(cur->Right);
     }
  }

public:
  //
  // default constructor:
  //
  //  Creates an empty tree.
  //
  binarysearchtree()
  {
    Root = nullptr;
    Size = 0;
  }
  
  //
  //
  // Copy constructor:
  //
  //  Creates copy of the "other" binarysearchtree 
  //  and stores each of the NODE into this tree
  //  by calling the helper function copyTree
  // 
  binarysearchtree(const binarysearchtree& other)
  {
	NODE* tmp = new NODE;
	tmp = other.Root;
	Root = nullptr;
	Size = 0;
	copyTree(tmp);
  }

  //
  //
  // copyTree:
  // 
  //  Helper function for the copy constructor that recursively calls itself
  //  Copying NODES from the other tree into this tree using pre-order traversal
  //
  void copyTree(NODE* cur)
  {  
	//Base case, if cur is nullptr
	if (cur == nullptr)
	{
		return;
	}
	//Otherwise insert key and perform preorder traversal
	else
	{
		insert(cur->Key, cur->Value);
		copyTree(cur->Left);
		copyTree(cur->Right);
		
	}
  }
  
  //
  //  
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  int size()
  {
    return Size;
  }
  
  //
  //
  // getheight:
  //
  //  Helper function that computes and returns height of tree; height of an empty tree is
  //  defined as -1
  //
  int getHeight(NODE* curr)
  {  
    //Base case for the recursive functionality
    if (curr == nullptr) {
     return -1;  
    }
     
     //Traverse the list to the Left and then the Right to add height
     //visiting each node
     int leftHeight = getHeight(curr->Left);
     int rightHeight = getHeight(curr->Right);
     
     //Return the higher of Left and Right height
     return 1 + max(leftHeight, rightHeight);
  }
  
  //
  // height:
  //
  //  Computes and returns height of tree; height of an empty tree is
  //  defined as -1.
  //
  int height()
  {
   return getHeight(Root);
  }
  

  // 
  // 
  // search:
  //
  //  Searches the tree for the given key, returning true if found
  //  and false if not.
  //
  //
  TValue* search(TKey key)
  {
    //Store Root as temporary pointer cur and traverse the list
    NODE* cur = Root;
    while (cur != nullptr)
    { 
      //If there is a match
      if (key == cur->Key)  // already in tree
        return &cur->Value;
      
      //If the key passed in is less than current key
      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }  
      
      //Otherwise, search left
      else
      {
        cur = cur->Right;
      }
    }
    // If it gets here, not found
    return nullptr;
  }

  //
  // insert:
  //
  //  Inserts the given key into the tree; if the key has already been insert then
  //  the function returns without changing the tree.
  //
  void insert(TKey key, TValue value)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;
      }
      else
      {
        prev = cur;
        cur = cur->Right;
      }
    }

    //
    // If we get here, key is not in tree, so allocate
    // a new node to insert. Allocating a new node, store key, initializing
    // pointer fields
    // 
    NODE* newNode = new NODE;
    newNode->Key = key;
	newNode->Value = value;
    newNode->Right = nullptr;
    newNode->Left = nullptr;

    //
    // Linking in the new node, updating Root 
    // pointer as appropriate
    //
    if (prev == nullptr){
       Root = newNode;
    }
    else{
      if (key < prev->Key){
         prev->Left = newNode;
      }
      else{
         prev->Right = newNode;
      }
    }
    //Updating size as a Node as been inserted
    Size++;
  }

  //
  // inorder:
  //
  //  Performs an inorder traversal of the tree, outputting
  //  the keys to the console.
  //
  void inorder()
  {
     cout << "Inorder: \n";
     _inorder(Root);
     cout << endl;
  }
};


