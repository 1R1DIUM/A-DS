#pragma once
#include "BinarySearchTree.h"
class RB
{
	enum COLORS {RED,BLACK};
public:
	struct Node
	{
		Node* parent;
		Node* leftChild;
		Node* rightChild;
		int data;
		int color;
	};
	
	Node* head;
	//functions
private:
	//Replace one subtree as a child of its parent with another subtree
	void Transport(RB*, Node*, Node*);
	
	void LeftRotation(RB*, Node*);
	void RightRotation(RB*, Node*);
	//Functions to restore color properties of tree
	void FixupInsert(RB*,Node*);
	void FixupDelete(RB*,Node*);

public:
	RB();
	//Search for an node in subtree by a key. 
	//Returns found Node or nullpointer of Node wasnt found
	Node* Search(Node*, int);

	//Search maximum key of subtree.
	//Returns found Node
	Node* TreeMinimum(Node*);

	//Search minimum key of subtree.
	//Returns Node
	Node* TreeMaximum(Node*);

	//Gets Node`s successor. 
	//Returns Node or nullptr if Node has no successor
	Node* TreeSuccessor(Node*);

	//Gets Node`s predecessor
	//Returns Node
	Node* TreePredeccessor(Node*);

	//Insert a new Node into the tree
	void Insert(RB*, Node*);

	//Create new Node by key and insert a new Node into the tree
	void Insert(RB*, int);

	//Delete Node from the tree
	void Delete(RB*, Node*);

	//Walkthroughs
	void PreOrder(Node*);
	void PostOrder(Node*);
	void InOrder(Node*);
	void InWidth(Node*);
};

