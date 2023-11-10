#pragma once

//Binary search tree class
class BST
{
	//data &structures
public:

	struct Node
	{
		Node* parent;
		Node* leftChild;
		Node* rightChild;
		int data;
	};
	Node* head;

//functions
private:
	//Replace one subtree as a child of its parent with another subtree
	void Transport(BST*, Node*, Node*);

public:
	BST();
	//Search for an node in subtree by a key. 
	//Returns found Node or nullpointer of Node wasnt found
	Node* Search(Node*, int );
	
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
	void Insert(BST*, Node*);
	
	//Create new Node by key and insert a new Node into the tree
	void Insert(BST*, int);
	
	//Delete Node from the tree
	void Delete(BST*, Node*);

	//Traversals
	void PreOrder(Node*);
	void PostOrder(Node*);
	void InOrder(Node*);
	void InWidth(Node*);
};
