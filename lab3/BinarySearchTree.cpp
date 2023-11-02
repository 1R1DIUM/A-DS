#include "Libraries.h"
#include "BinarySearchTree.h"


BST::BST()
{
	head = nullptr;
}

BST::Node* BST::Search(Node * node, int data)
{
	while (node != nullptr and node->data != data)
	{
		if (data < node->data)
		{
			node = node->leftChild;
		}
		else
		{
			node = node->rightChild;
		}
	}
	return node;
}

BST::Node* BST::TreeMinimum(Node* node)
{
	while (node->leftChild != nullptr)
	{
		node = node->leftChild;
	}
	return node;
}

BST::Node* BST::TreeMaximum(Node* node)
{
	while (node->rightChild != nullptr)
	{
		node = node->rightChild;
	}
	return node;
}
BST::Node* BST::TreeSuccessor(Node* node)
{
	if (node->rightChild != nullptr)
	{
		return TreeMinimum(node->rightChild);
	}
	else
	{
		Node* curr = node->parent;
		while (curr != nullptr and node == curr->rightChild)
		{
			node = curr;
			curr = curr->parent;
		}
		return curr;
	}
}

BST::Node* BST::TreePredeccessor(Node* node)
{
	if (node->leftChild != nullptr)
	{
		return TreeMaximum(node->leftChild);
	}
	else
	{
		Node* curr = node->parent;
		while (curr != nullptr and node == curr->leftChild)
		{
			node = curr;
			curr = curr->parent;
		}
		return curr;
	}
}

void BST::Insert(BST* binsearchTree, Node* node)
{
	Node* curr = binsearchTree->head; //iterative node
	Node* currParent = nullptr; //parent to iterative, not to lose it while searching a space
	//Searching for a proper space to insert a new node
	while (curr != nullptr)
	{
		currParent = curr;
		if (node->data < curr->data)
		{
			curr = curr->leftChild;
		}
		else
		{
			curr = curr->rightChild;
		}
	}

	node->parent = currParent;
	if (currParent == nullptr) //if tree was empty
	{
		binsearchTree->head = node;
	}
	else
	{
		//identify which child our new Node should be
		if (node->data < currParent->data)
		{
			currParent->leftChild = node;
		}
		else
		{
			currParent->rightChild = node;
		}
	}
}
void BST::Insert(BST* binsearchTree, int data)
{
	//Creating a new Node
	Node* newNode = new Node;
	newNode->parent = newNode->leftChild = newNode->rightChild = nullptr;
	newNode->data = data;
	//Inserting a new Node into the tree
	Insert(binsearchTree, newNode);
}

void BST::Delete(BST* binsearchtree, Node* node)
{
	if (node != nullptr)
	{
		if (node->leftChild == nullptr)
		{
			Transport(binsearchtree, node, node->rightChild);
		}
		else
		{
			if (node->rightChild == nullptr)
			{
				Transport(binsearchtree, node, node->leftChild);
			}
			else
			{
				Node* curr = TreeMinimum(node->rightChild);
				if (curr != node->rightChild) // if right child isnt the smallest in subtree of node right child
				{
					Transport(binsearchtree, curr, curr->rightChild);
					curr->rightChild = node->rightChild;
					curr->rightChild->parent = curr;
				}
				Transport(binsearchtree, node, curr);
				curr->leftChild = node->leftChild;
				curr->leftChild->parent = curr;
			}
		}
		delete node;
	}
	else
	{
		std::cout << "Deleting an empty node!\n";
	}
}

void BST::Transport(BST* binsearchtree, Node* ReplaceWhat, Node* ReplaceWith)
{
	if (ReplaceWhat->parent == nullptr)
	{
		binsearchtree->head = ReplaceWith;
	}
	else
	{
		if (ReplaceWhat == ReplaceWhat->parent->leftChild)
		{
			ReplaceWhat->parent->leftChild = ReplaceWith;
		}
		else
		{
			ReplaceWhat->parent->rightChild = ReplaceWith;
		}
	}
	if (ReplaceWith != nullptr)
	{
		ReplaceWith->parent = ReplaceWhat->parent;
	}
}

void BST::InOrder(Node* node)
{
	if (node == nullptr)
	{
		return;
	}
	else
	{
		InOrder(node->leftChild);
		std::cout << (node->data) << ' ';
		InOrder(node->rightChild);
	}
}

void BST::PostOrder(Node* node)
{
	if (node == nullptr)
	{
		return;
	}
	else
	{
		InOrder(node->leftChild);
		InOrder(node->rightChild);
		std::cout << (node->data) << ' ';
	}
}
void BST::PreOrder(Node* node)
{
	if (node == nullptr)
	{
		return;
	}
	else
	{
		std::cout << (node->data) << ' ';
		InOrder(node->leftChild);
		InOrder(node->rightChild);
	}
}


void BST::InWidth(Node* node)
{
	if (node == NULL)
	{
		return;
	}

	std::queue<Node*> q;
	q.push(node);

	while (!q.empty())
	{
		Node* temp = q.front();
		q.pop();
		std::cout << (temp->data) << ' ';

		if (temp->leftChild != nullptr)
		{
			q.push(temp->leftChild);
		}
		if (temp->rightChild != nullptr)
		{
			q.push(temp->rightChild);
		}
	}
}
