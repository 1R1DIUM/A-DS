#pragma once
class AVL
{
public:
	struct Node
	{
		int data;
		int height;
		Node* parent;
		Node* leftChild;
		Node* rightChild;
	};

	Node* head;
	//functions
private:
	//Replace one subtree as a child of its parent with¸ another subtree
	void Transport(AVL*, Node*, Node*);

	void LeftRotation(AVL*, Node*);
	void RightRotation(AVL*, Node*);
	//Functions to restore color properties of tree
	void FixupInsert(AVL*, Node*);
	void FixupDelete(AVL*, Node*);

public:
	AVL();
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
	void Insert(AVL*, Node*);

	//Create new Node by key and insert a new Node into the tree
	void Insert(AVL*, int);

	//Delete Node from the tree
	void Delete(AVL*, Node*);

	//Walkthroughs
	void PreOrder(Node*);
	void PostOrder(Node*);
	void InOrder(Node*);
	void InWidth(Node*);
};

