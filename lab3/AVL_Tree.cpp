#include "AVL_Tree.h"
#include "Libraries.h"

AVL::AVL()
{
	head = nullptr;
}

AVL::Node* AVL::Search(Node* node, int data)
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

AVL::Node* AVL::TreeMinimum(Node* node)
{
	while (node->leftChild != nullptr)
	{
		node = node->leftChild;
	}
	return node;
}

AVL::Node* AVL::TreeMaximum(Node* node)
{
	while (node->rightChild != nullptr)
	{
		node = node->rightChild;
	}
	return node;
}
AVL::Node* AVL::TreeSuccessor(Node* node)
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

AVL::Node* AVL::TreePredeccessor(Node* node)
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

void AVL::Transport(AVL* redBlackTree, Node* ReplaceWhat, Node* ReplaceWith)
{
	if (ReplaceWhat->parent == nullptr)
	{
		redBlackTree->head = ReplaceWith;
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

void AVL::LeftRotation(AVL* redBlackTree, Node* node)
{
	Node* lowerNode = node->rightChild;
	node->rightChild = lowerNode->leftChild;
	if (lowerNode->leftChild != nullptr)
	{
		lowerNode->leftChild->parent = node;
	}

	lowerNode->parent = node->parent;
	if (node->parent == nullptr) //if our node was the root of tree
	{
		redBlackTree->head == lowerNode;
	}
	else
	{
		//what child was node?
		if (node == node->parent->leftChild)
		{
			node->parent->leftChild = lowerNode;
		}
		else
		{
			node->parent->rightChild = lowerNode;
		}
	}
	lowerNode->leftChild = node;
	node->parent = lowerNode;

}

void AVL::RightRotation(AVL* redBlackTree, Node* node)
{
	Node* lowerNode = node->leftChild;
	node->leftChild = lowerNode->rightChild;
	if (lowerNode->rightChild != nullptr)
	{
		lowerNode->rightChild->parent = node;
	}
	lowerNode->parent = node->parent;

	if (node->parent == nullptr)
	{
		redBlackTree->head = lowerNode;
	}
	else
	{
		if (node == node->parent->leftChild)
		{
			node->parent->leftChild = lowerNode;
		}
		else
		{
			node->parent->rightChild = lowerNode;
		}
	}
	lowerNode->rightChild = node;
	node->parent = lowerNode;
}


void AVL::InOrder(Node* node)
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

void AVL::PostOrder(Node* node)
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
void AVL::PreOrder(Node* node)
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


void AVL::InWidth(Node* node)
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