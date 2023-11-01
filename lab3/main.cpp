#include "Libraries.h"
#include "BinarySearchTree.h"
#include "RedAndBlackTree.h"

int main()
{
	BST* BinSearchTree = new BST;
	BinSearchTree->Insert(BinSearchTree, 13);
	BinSearchTree->Insert(BinSearchTree, 20);
	BinSearchTree->Insert(BinSearchTree, 5);
	BinSearchTree->Insert(BinSearchTree, 52);
	BinSearchTree->Insert(BinSearchTree, 8);
	
	BST::Node* node = BinSearchTree->Search(BinSearchTree->head,13);
	BinSearchTree->Delete(BinSearchTree,node);
	std::cout << BinSearchTree->head->data;

}