#include "Libraries.h"
#include "BinarySearchTree.h"
#include "RedAndBlackTree.h"

int main()
{
	/*BST* BinSearchTree = new BST;
	BinSearchTree->Insert(BinSearchTree, 10);
	BinSearchTree->Insert(BinSearchTree, 15);
	BinSearchTree->Insert(BinSearchTree, 9);
	BinSearchTree->Insert(BinSearchTree, 0);
	BinSearchTree->Insert(BinSearchTree, 20);
	
	BST::Node* node = BinSearchTree->Search(BinSearchTree->head,15);
	BinSearchTree->Delete(BinSearchTree,node);
	BinSearchTree->InWidth(BinSearchTree->head);*/

	RB* rb = new RB;
	rb->Insert(rb, 10);
	rb->Insert(rb, 15);
	rb->Insert(rb, 9);
	rb->Insert(rb, 0);
	rb->Insert(rb, 20);

	rb->Insert(rb, 5);
	rb->Insert(rb, 3);
	rb->Insert(rb, 13);
	rb->Insert(rb, 8);
	rb->Insert(rb, 7);


	rb->Delete(rb, rb->head->leftChild);
	

	rb->InWidth(rb->head);

	/*rb->InWidth(rb->head);
	rb->Delete(rb, rb->head->rightChild);
	std::cout << '\n';
	rb->InWidth(rb->head);*/

}