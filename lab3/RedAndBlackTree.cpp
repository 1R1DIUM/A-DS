#include "Libraries.h"
#include "RedAndBlackTree.h"

RB::RB()
{
	head = nullptr;
}

RB::Node* RB::Search(Node* node, int data)
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

RB::Node* RB::TreeMinimum(Node* node)
{
	while (node->leftChild != nullptr)
	{
		node = node->leftChild;
	}
	return node;
}

RB::Node* RB::TreeMaximum(Node* node)
{
	while (node->rightChild != nullptr)
	{
		node = node->rightChild;
	}
	return node;
}
RB::Node* RB::TreeSuccessor(Node* node)
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

RB::Node* RB::TreePredeccessor(Node* node)
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

void RB::Transport(RB* redBlackTree, Node* ReplaceWhat, Node* ReplaceWith)
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

void RB::LeftRotation(RB* redBlackTree, Node* node)
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

void RB::RightRotation(RB* redBlackTree, Node* node)
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

void RB::FixupInsert(RB* redBlackTree, Node* node)
{
	while (node->parent != nullptr and node->parent->color == RED)
	{
		if (node->parent == node->parent->parent->leftChild)
		{
			Node* brother = node->parent->parent->rightChild;
			if (brother!=nullptr and brother->color == RED)
			{
				//Case 1
				node->parent->color = BLACK;
				brother->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent; //subtree`s color restored
			}
			else
			{
				//Case 2
				if (node == node->parent->rightChild)
				{
					node = node->parent;
					LeftRotation(redBlackTree, node);
				}
				//Case3
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				RightRotation(redBlackTree, node->parent->parent);
			}
		}
		else
		{
			Node* brother = node->parent->parent->leftChild;
			if (brother!=nullptr and brother->color == RED)
			{
				//Case 1
				node->parent->color = BLACK;
				brother->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent; //subtree`s color restored
			}
			else
			{
				//Case 2
				if (node == node->parent->leftChild)
				{
					node = node->parent;
					RightRotation(redBlackTree, node);
				}
				//Case3
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				LeftRotation(redBlackTree, node->parent->parent);
			}
		}
	}
	redBlackTree->head->color = BLACK;
}



void RB::Insert(RB* redBlackTree, Node* node)
{
	Node* temp = redBlackTree->head;
	Node* tempParent = nullptr;
	//Finding proper location to insert a new node
	while (temp != nullptr)
	{
		tempParent = temp;
		if (node->data < temp->data)
			temp = temp->leftChild;
		else
			temp = temp->rightChild;
	}
	node->parent = tempParent;
	if (tempParent == nullptr) //if tree was empty
	{
		redBlackTree->head = node;
	}
	else
	{
		if (node->data < tempParent->data)
		{
			tempParent->leftChild = node;
		}
		else
		{
			tempParent->rightChild = node;
		}
	}
	node->leftChild = node->rightChild = nullptr;
	node->color = RED;
	RB::FixupInsert(redBlackTree, node);
}

void RB::Insert(RB* redBlackTree, int key)
{
	Node* node = new Node;
	node->color = RED;
	node->data = key;
	Insert(redBlackTree, node);

}


void RB::FixupDelete(RB* redBlackTree, Node* node)
{
	while (node != redBlackTree->head and node->color == BLACK)
	{
		if (node = node->parent->leftChild)
		{
			Node* brother = node->parent->rightChild;
			if (brother->color == RED)
			{
				//Case 1
				brother->color = BLACK;
				node->parent->color = RED;
				LeftRotation(redBlackTree, node->parent);
				brother = node->parent->rightChild;
			}
			if (brother->leftChild->color == BLACK and brother->rightChild->color == BLACK)
			{
				//Case 2
				brother->color = RED;
				node = node->parent;
			}
			else
			{
				if (brother->rightChild->color == BLACK)
				{
					//Case 3
					brother->leftChild->color = BLACK;
					brother->color = RED;
					RightRotation(redBlackTree, brother);
					brother = node->parent->rightChild;
				}
				//Case4
				brother->color = node->parent->color;
				node->parent->color = BLACK;
				brother->rightChild->color = BLACK;
				LeftRotation(redBlackTree, node->parent);
				node = redBlackTree->head;
			}
		}
		else
		{
			Node* brother = node->parent->leftChild;
			if (brother->color == RED)
			{
				//Case 1
				brother->color = BLACK;
				node->parent->color = RED;
				RightRotation(redBlackTree, node->parent);
				brother = node->parent->leftChild;
			}
			if (brother->rightChild->color == BLACK and brother->leftChild->color == BLACK)
			{
				//Case 2
				brother->color = RED;
				node = node->parent;
			}
			else
			{
				if (brother->leftChild->color == BLACK)
				{
					//Case 3
					brother->rightChild->color = BLACK;
					brother->color = RED;
					LeftRotation(redBlackTree, brother);
					brother = node->parent->leftChild;
				}
				//Case4
				brother->color = node->parent->color;
				node->parent->color = BLACK;
				brother->leftChild->color = BLACK;
				RightRotation(redBlackTree, node->parent);
				node = redBlackTree->head;
			}
		}
		
	}
	node->color = BLACK;
}


void RB::Delete(RB* redBlacktree, Node* node)
{
	Node* temp = node; Node* curr = nullptr; Node* nullLeaf = new Node;
	bool tempColor = temp->color;
	if (node->leftChild == nullptr)
	{
		curr = node->rightChild;
		Transport(redBlacktree, node, node->rightChild);
	}
	else
	{
		if (node->rightChild == nullptr)
		{
			curr = node->leftChild;
			Transport(redBlacktree, node, node->leftChild);
		}
		else
		{
			temp = TreeMinimum(node->rightChild);
			tempColor = temp->color;
			curr = temp->rightChild;
			if (temp != node->rightChild)
			{
				Transport(redBlacktree, temp, temp->rightChild);
				temp->rightChild = node->rightChild;
				temp->rightChild->parent = temp;
			}
			else 
			{
				if (curr != nullptr)
				{
					curr->parent = temp;
				}
				else
				{
					nullLeaf->parent = temp;
				}
			}
			Transport(redBlacktree, node, temp);
			temp->leftChild = node->leftChild;
			temp->leftChild->parent = temp;
			temp->color = node->color;
		}
	}
	if (tempColor == BLACK)
	{
		if (curr != nullptr)
		{
			FixupDelete(redBlacktree, curr);
		}
		else
		{
			FixupDelete(redBlacktree, nullLeaf);
		}
	}
}



void RB::InOrder(Node* node)
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

void RB::PostOrder(Node* node)
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
void RB::PreOrder(Node* node)
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


void RB::InWidth(Node* node)
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