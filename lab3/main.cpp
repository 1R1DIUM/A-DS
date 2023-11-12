#include "Libraries.h"
#include "BinarySearchTree.h"
#include "RedAndBlackTree.h"
#include "AVL_Tree.h"


int sizes[] = { 50, 100, 500, 1000, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 55000, 60000, 65000, 70000, 75000, 80000, 85000, 90000, 95000, 100000 };
enum Operation { Insertion, Deletion, Height };

void BST_height_measurements()
{
	std::vector<int> valVector;


	for (int i = 0; i < 24; i++)
	{

		BST* bst = new BST;


		auto begin = std::chrono::steady_clock::now();
		auto end = std::chrono::steady_clock::now();

		std::ifstream valFile("1.txt");
		valFile.unsetf(std::ios::skipws);


		if (!valFile.good())
		{
			std::cout << "File not found!\n";
			return;
		}



		std::string s;
		std::istringstream is(s);
		for (int lin = 0; lin < sizes[i]; lin++)
		{

			std::getline(valFile, s, '\n');
			try
			{
				valVector.push_back(stoi(s));
			}
			catch (...)
			{
				std::cout << "erorr at " << s << '\n';
			}
		}






		for (int j = 0; j < sizes[i]; j++)
		{
			bst->Insert(bst, valVector[j]);

		}

		std::cout << bst->getTreeHeight(bst->head) << ' ';






		delete bst;
		valVector.clear();
		valFile.close();

		is.clear();
	}
}


void RB_measurements(int operation)
{
	std::vector<int> valVector;


	for (int i = 0; i < 24; i++)
	{

		RB* rb = new RB;


		auto begin = std::chrono::steady_clock::now();
		auto end = std::chrono::steady_clock::now();

		std::ifstream valFile("1.txt");
		valFile.unsetf(std::ios::skipws);


		if (!valFile.good())
		{
			std::cout << "File not found!\n";
			return;
		}



		std::string s;
		std::istringstream is(s);
		for (int lin = 0; lin < sizes[i]+1; lin++)
		{

			std::getline(valFile, s, '\n');
			try
			{
				valVector.push_back(stoi(s));
			}
			catch (...)
			{
				std::cout << "erorr at " << s << '\n';
			}
		}






		for (int j = 0; j < sizes[i]; j++)
		{
			rb->Insert(rb, valVector[j]);
			
		}

		int ValueToInsert = valVector[sizes[i]];
		RB::Node* ValueToDelete = rb->Search(rb->head, valVector[sizes[i] - 1]);
		switch (operation)
		{
		case Insertion:

			



			begin = std::chrono::steady_clock::now();

			rb->Insert(rb, ValueToInsert);


			end = std::chrono::steady_clock::now();

			std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << ' ';
			break;
		case Deletion:

			


			begin = std::chrono::steady_clock::now();

			rb->Delete(rb, ValueToDelete);
			end = std::chrono::steady_clock::now();

			std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << ' ';

			break;

		case Height:
			std::cout << rb->getTreeHeight(rb->head) << ' ';
			break;
		}

		

		

		delete rb;
		valVector.clear();
		valFile.close();

		is.clear();
	}
}



void AVL_measurements(int operation)
{
	std::vector<int> valVector;


	for (int i = 0; i < 24; i++)
	{

		AVL* avl = new AVL;


		auto begin = std::chrono::steady_clock::now();
		auto end = std::chrono::steady_clock::now();

		std::ifstream valFile("1.txt");
		valFile.unsetf(std::ios::skipws);


		if (!valFile.good())
		{
			std::cout << "File not found!\n";
			return;
		}



		std::string s;
		std::istringstream is(s);
		for (int lin = 0; lin < sizes[i]+1; lin++)
		{

			std::getline(valFile, s, '\n');
			try
			{
				valVector.push_back(stoi(s));
			}
			catch (...)
			{
				std::cout << "erorr at " << s;
			}
		}





		avl->head = avl->Insert(nullptr, avl->head, valVector[0]);

		for (int j = 1; j < sizes[i] - 1; j++)
		{
			avl->head = avl->Insert(avl->head->parent, avl->head, valVector[j]);
		}



		int ValueToInsert = valVector[sizes[i]];
		int ValueToDelete = valVector[sizes[i] - 1];

		switch (operation)
		{
		case Insertion:
			begin = std::chrono::steady_clock::now();

			avl->head = avl->Insert(avl->head->parent, avl->head, ValueToInsert);

			end = std::chrono::steady_clock::now();
			std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << ' ';
			break;
		case Deletion:
			begin = std::chrono::steady_clock::now();

			avl->head = avl->Delete(avl->head, ValueToDelete);

			end = std::chrono::steady_clock::now();
			std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << ' ';
			break;
		case Height:
			std::cout<< avl->getTreeHeight(avl->head) << ' ';
		}

		

		

		delete avl;
		valVector.clear();
		valFile.close();

		is.clear();
	}
}


int main()
{
	///Binary Search Tree
	
	/*BST* BinSearchTree = new BST;
	BinSearchTree->Insert(BinSearchTree, 10);
	BinSearchTree->Insert(BinSearchTree, 15);
	BinSearchTree->Insert(BinSearchTree, 9);
	BinSearchTree->Insert(BinSearchTree, 0);
	BinSearchTree->Insert(BinSearchTree, 20);

	BinSearchTree->Insert(BinSearchTree, -5);


	BST::Node* node = BinSearchTree->Search(BinSearchTree->head,15);
	BinSearchTree->Delete(BinSearchTree,node);
	BinSearchTree->InWidth(BinSearchTree->head);

	std::cout << BinSearchTree->getTreeHeight(BinSearchTree->head) << '\n';*/

	///Red-Black Tree
	/*RB* rb = new RB;
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

	rb->InWidth(rb->head);
	rb->Delete(rb, rb->head->rightChild);
	std::cout << '\n';
	rb->InWidth(rb->head);*/

	///AVL Tree
	/*AVL* avl = new AVL;


	avl->head = avl->Insert(nullptr, avl->head, 33);
	avl->head = avl->Insert(avl->head->parent, avl->head, 13);
	avl->head = avl->Insert(avl->head->parent, avl->head, 53);
	avl->head = avl->Insert(avl->head->parent, avl->head, 11);
	avl->head = avl->Insert(avl->head->parent, avl->head, 21);
	avl->head = avl->Insert(avl->head->parent, avl->head, 61);
	avl->head = avl->Insert(avl->head->parent, avl->head, 8);
	avl->head = avl->Insert(avl->head->parent, avl->head, 9);

	avl->head = avl->Delete(avl->head, 13);
	avl->InWidth(avl->head);*/




	///timeTesting 
	
	
	RB_measurements(Height);
	std::cout << '\n';
	AVL_measurements(Height);
	std::cout << '\n';
	BST_height_measurements();

	


}



