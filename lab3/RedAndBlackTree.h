#pragma once
#include "BinarySearchTree.h"
class RB : public BST
{
	struct Node
	{
		Node* parent;
		Node* leftChild;
		Node* righChild;
		int data;
		int color;
	};
	
public:
	void Search();
};

