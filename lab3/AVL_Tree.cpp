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
//AVL::Node* AVL::TreeSuccessor(Node* node)
//{
//	if (node->rightChild != nullptr)
//	{
//		return TreeMinimum(node->rightChild);
//	}
//	else
//	{
//		Node* curr = node->parent;
//		while (curr != nullptr and node == curr->rightChild)
//		{
//			node = curr;
//			curr = curr->parent;
//		}
//		return curr;
//	}
//}
//
//AVL::Node* AVL::TreePredeccessor(Node* node)
//{
//	if (node->leftChild != nullptr)
//	{
//		return TreeMaximum(node->leftChild);
//	}
//	else
//	{
//		Node* curr = node->parent;
//		while (curr != nullptr and node == curr->leftChild)
//		{
//			node = curr;
//			curr = curr->parent;
//		}
//		return curr;
//	}
//}

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

int AVL::Height(Node* node)
{
	if (node == nullptr)
	{
		return 0;
	}
	return node->height;
}



AVL::Node* AVL::RightRotate(Node* y)
{
	AVL::Node* x = y->leftChild;
	AVL::Node* temp = x->rightChild;
	x->rightChild = y;
	y->leftChild = temp;
	
	y->height = std::max(Height(y->rightChild), Height(y->leftChild)) + 1;
	x->height = std::max(Height(x->rightChild), Height(x->leftChild)) + 1;

	return x;
}

AVL::Node* AVL::LeftRotate(Node* x)
{
	Node* y = x->rightChild;
	Node* temp = y->leftChild;
	y->leftChild = x;
	x->rightChild = temp;

	x->height = std::max(Height(x->rightChild), Height(x->leftChild)) + 1;
	y->height = std::max(Height(y->rightChild), Height(y->leftChild)) + 1;
	

	return y;
}



int AVL::getBalance(Node* node)
{
	if (node != nullptr)
	{
		return Height(node->leftChild) - Height(node->rightChild);
	}
	return 0;
}


AVL::Node* AVL::Insert(Node* root, int key)
{
	if (root == nullptr)
	{
		root = new Node();
		root->data = key;
		root->leftChild = root->rightChild = nullptr;
		//node->parent = prev;
		root->height = 1;
		return (root);
	}

	if (key < root->data)
	{
		root->leftChild = AVL::Insert( root->leftChild, key);
	}
	else if(key > root->data)
	{
		root->rightChild = AVL::Insert(root->rightChild, key);
	}
	else
	{
		std::cout << "Value" << root->data <<" exist in tree\n";
		return root;
	}

	root->height = 1 + std::max(Height(root->rightChild), Height(root->leftChild));
	int balance = getBalance(root);

	if (balance > 1 && key < root->leftChild->data)
	{
		return RightRotate(root);
	}
	if (balance < -1 && key > root->rightChild->data)
	{
		return LeftRotate(root);
	}
	if (balance > 1 && key > root->leftChild->data)
	{
		root->leftChild = LeftRotate(root->leftChild);
		return RightRotate(root);
	}

	if (balance < -1 && key < root->rightChild->data)
	{
		root->rightChild = RightRotate(root->rightChild);
		return LeftRotate(root);
	}


	return root;
}

AVL::Node* AVL::Delete(Node* root, int key)
{
	if (root == nullptr)
	{
		return root;
	}
	if (key < root->data)
	{
		root->leftChild = Delete(root->leftChild, key);
	}
	else if(key > root->data )
	{
		root->rightChild = Delete(root->rightChild, key);
	}
	else
	{
		if (root->leftChild == nullptr or root->rightChild == nullptr)
		{
			Node* temp = root->leftChild ? root->leftChild : root->rightChild;

			if (temp == nullptr)
			{
				temp = root;
				root = nullptr;
			}
			else
			{
				*root = *temp;
			}
			delete temp;
		}
		else
		{
			Node* temp = TreeMinimum(root->rightChild);
			root->data = temp->data;
			root->rightChild = Delete(root->rightChild, root->data);

		}
	}

	if (root == nullptr)
		return root;
	root->height = 1 + std::max(Height(root->leftChild), Height(root->rightChild));

	int balance = getBalance(root);

	if (balance > 1 and getBalance(root->leftChild) >= 0)
	{
		return RightRotate(root);
	}
	if (balance > 1 and getBalance(root->leftChild) < 0)
	{
		root->leftChild = LeftRotate(root->leftChild);
		return RightRotate(root);
	}

	if (balance < -1 and getBalance(root->rightChild) <= 0)
	{
		return LeftRotate(root);
	}

	if (balance < -1 and getBalance(root->rightChild) > 0)
	{
		root->rightChild = RightRotate(root->rightChild);
		return LeftRotate(root);
	}
	return root;
}

