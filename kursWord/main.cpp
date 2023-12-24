#include "FileUtil.h"
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

enum TypeOfOperations {ДелениеНа2,Вычитание,ДелениеНа3};


std::list<std::vector<int>> getBasisVectors(int size) //получение базисных векторов размерности простанства (обратные) т.е. первый (0,0,1)
{
	std::list<std::vector<int>> basisVectors;
	int coefIter = size-1; //
	for (int vectorIter = 0; vectorIter < size; vectorIter++,coefIter--)
	{
		std::vector<int>* newBasisVector = new std::vector<int>;
		//заполенение базисного вектора
		for (int i = 0; i < size; i++)
		{
			if (i != coefIter)
			{
				newBasisVector->push_back(0);
			}
			else
			{
				newBasisVector->push_back(1);
			}
		}
		basisVectors.push_back(*newBasisVector);

	}
	return basisVectors;
}

std::vector<int> getDevidedBy2Vector(std::vector<int> vector) //получение вектора, коэф. которого в два раза меньше данного(vector)
{
	std::vector <int> newVector = vector;
	for (int i = 0; i < vector.size(); i++)
	{
		newVector[i] /= 2;
	}

	return newVector;
}
 

std::pair<std::vector <int>,std::vector<int>> getEvenVector(std::vector<int> vector) //два вектора: первый - четный вектор, второй - который нужно добавить, чтобы получить искомый, например (1,0,1)
{
	std::pair<std::vector <int>, std::vector<int>> returnVectors; //возвращаемые вектора
	std::vector<int> evenVector; //вектор, содержащий все четные коэф.
	std::vector<int> addedVector; //вектор, который в сумме с четным(evenVector) дает искомый(vector) вектор

	for (int coef : vector)
	{
		if (coef % 2 == 0) //если коэф. четный
		{
			addedVector.push_back(0);
			evenVector.push_back(coef);
		}
		else //коэф. нечетный
		{
			addedVector.push_back(1);
			evenVector.push_back(coef - 1);
		}
	}
	returnVectors.first = evenVector;
	returnVectors.second = addedVector;

	return returnVectors;
}

bool VectorOneOrZero(std::vector<int> vector) //вектор состоит только из нулей или единиц
{
	bool isOneAndZero = true;
	for (int coef : vector) //foreach coef in vector
	{
		if(coef != 1 and coef != 0)
		{
			isOneAndZero = false;
		}
	}
	return isOneAndZero;
}

bool VectorIsEven(std::vector<int> vector) //вектор состоит только из четных чисел
{
	bool isEven = true;
	for (int coef : vector)
	{
		if (coef % 2 != 0)
		{
			isEven = false;
		}
	}
	return isEven;
}


bool NotInVecAddChain(std::list<std::vector<int>> vectorialAdditionChain, std::vector<int> vector)
{
	bool notInVecAddChain = true; //Нахождение в векторной аддитивной цепочке
	for (auto vec : vectorialAdditionChain)
	{
		if (vector == vec)
		{
			notInVecAddChain = false;
			break;
		}
	}
	return notInVecAddChain;
}

int getOnesInVectorAmount(std::vector<int> vector) //подсчёт количества единиц в вектора
{
	int amount = 0;
	for (int koef : vector)
	{
		amount += koef;
	}
	return amount;
}

std::vector<int> subTwoVectors(std::vector<int> firstVect, std::vector<int> secondVect)
{
	std::vector<int> subVector;
	for (int i = 0; i < firstVect.size(); i++)
	{
		subVector.push_back(firstVect[i] - secondVect[i]);
	}
	return subVector;
}


int checkSimularity(std::vector<int> firstVect, std::vector<int> secondVect)
{
	if (firstVect == secondVect) return 0;

	int simularity = 0;
	for (int i = 0; i < firstVect.size(); i++)
	{
		
		if (firstVect[i] and secondVect[i])
		{
			simularity++;
		}

		if (secondVect[i] && !firstVect[i]) //если не соблюдается импликация второго коэф. из первого. (1->0 - f, остальные t)
		{
			simularity = 0;
			break;
		}
	}
	return simularity;
}



void formNewFormedByBasisVector(std::list<std::vector<int>> lst, std::vector<int> vector, std::list<std::vector<int>>* addingList) 
{
	
	std::list<std::vector<int>> basisVectors = getBasisVectors(vector.size()); 
	if (NotInVecAddChain(lst, vector) and NotInVecAddChain(basisVectors, vector))
	{
		lst.push_back(vector);
		addingList->push_back(vector);
	}
	
	
	if (getOnesInVectorAmount(vector) < 3) //если очердной вектор можно сформировать из базисных
	{
		return;
	}
	//выбрать какой нибудь с наибольшим сходством (наибольшое количество единиц на одинаковых местах)
	std::vector<int> maxSimularVector = lst.front();
	int maxSimularity = checkSimularity(vector, maxSimularVector);
	for (auto vect : lst)
	{
		int simularity = checkSimularity(vector, vect);
		if (simularity > maxSimularity)
		{
			maxSimularVector = vect;
			maxSimularity = simularity;
		}
	}



	if (maxSimularity == 0) //если не был найден похожий вектор
	{
		//вычесть какой либо базисный вектор
		std::list<std::vector<int>> basisVectorsList = getBasisVectors(vector.size());
		std::vector<int> maxSimularBasisVector = basisVectorsList.front();
		int maxSimularity = checkSimularity(vector, maxSimularBasisVector);

		for (auto vect : basisVectorsList)
		{
			int simularity = checkSimularity(vector, vect);
			if (simularity > maxSimularity)
			{
				maxSimularBasisVector = vect;
				maxSimularity = simularity;
			}
		}
		formNewFormedByBasisVector(lst, subTwoVectors(vector, maxSimularBasisVector),addingList);
		return; 
	}

	formNewFormedByBasisVector(lst, subTwoVectors(vector, maxSimularVector),addingList);
	return;
}



void checkFormedByBasisVectorsList(std::list<std::vector<int>>* lst) //проверка на аддитивность цепочки векторов, сформированных из базисных
{
	for (auto vect : *lst)
	{
		if (getOnesInVectorAmount(vect) > 2)
		{
			std::list<std::vector<int>> addingList;
			formNewFormedByBasisVector(*lst, vect,&addingList);
			for (auto elem : addingList)
			{
				lst->push_front(elem);
			}
		}
	}
}

std::list<std::vector<int>> sortByOnesAmount(std::list<std::vector<int>> lst)
{

	std::list<std::vector<int>> returnList;

	//std::list -> std::vector
	std::vector<std::vector<int>> listVect;
	for (auto vector : lst)
	{
		listVect.push_back(vector);
	}
	//insertion Sort
	for (int i = 1; i < lst.size(); i++)
	{
		for (int j = i; j > 1; j--)
		{
			if (getOnesInVectorAmount(listVect[j]) < getOnesInVectorAmount(listVect[j - 1]))
			{
				auto temp = listVect[j];
				listVect[j] = listVect[j - 1];
				listVect[j - 1] = temp;
			}
			else
			{
				break;
			}
		}
	}


	for (auto vect : listVect)
	{
		returnList.push_front(vect);
	}


	return returnList;
}


int typeOfOperation(std::vector<int> vector)
{
	bool divBy3 = true; bool divBy2 = true;
	for (int coef : vector)
	{
		if (coef % 3 != 0)
		{
			divBy3 = false;
		}
		if (coef % 2 != 0)
		{
			divBy2 = false;
		}
	}
	if (divBy3) return ДелениеНа3;
	if (divBy2) return ДелениеНа2;
	return Вычитание;
}


std::pair<std::vector<int>,std::vector <int>> getDevidedBy3Vector(std::vector<int> vector)
{
	std::pair<std::vector<int>, std::vector <int>>returnPair;
	for (int koef : vector)
	{
		returnPair.first.push_back(koef / 3);
		returnPair.second.push_back(koef / 3 * 2);
	}
	return returnPair;
}



std::list<std::vector<int>> getVectorialAdditionChain(std::vector<int> findingVector)
{
	std::list<std::vector<int>> vectorialAdditionChain; //векторная аддитивная цепочка
	std::list<std::vector<int>> basisVectors = getBasisVectors(findingVector.size()); //получение базовых векторов простанства
	std::list<std::vector<int>> formedByBasisVectorsList; //вектора, содержащие 1 или 0 


	std::vector<int> currVector = findingVector; //очередной вектор в цепочке 

	//основной алгоритм 
	while (!VectorOneOrZero(currVector))
	{
		if (NotInVecAddChain(vectorialAdditionChain, currVector))
		{
			vectorialAdditionChain.push_front(currVector);
		}

		std::pair<std::vector<int>, std::vector<int>> addingVectors; //векторы, которые нужно будет добавить к векторной аддитивной цепочке
		switch (typeOfOperation(currVector))
		{
		case Вычитание:
			addingVectors = getEvenVector(currVector);
			if (NotInVecAddChain(vectorialAdditionChain, addingVectors.first))
			{
				vectorialAdditionChain.push_front(addingVectors.first); //добавляем четный вектор
			}
			if (NotInVecAddChain(formedByBasisVectorsList, addingVectors.second) and NotInVecAddChain(basisVectors, addingVectors.second)) //если не в базисных или не в списке векторов 1 и 0
			{
				formedByBasisVectorsList.push_front(addingVectors.second); //добавляем вектор, чтобы четный стал искомым
			}
			currVector = addingVectors.first;

			break;
		case ДелениеНа2:
			currVector = getDevidedBy2Vector(currVector);

			if (NotInVecAddChain(vectorialAdditionChain, currVector) and NotInVecAddChain(basisVectors, currVector) and NotInVecAddChain(formedByBasisVectorsList, currVector))
			{
				vectorialAdditionChain.push_front(currVector);
			}
			break;
		case ДелениеНа3:
			addingVectors = getDevidedBy3Vector(currVector);
			if (NotInVecAddChain(vectorialAdditionChain, addingVectors.second))
			{
				vectorialAdditionChain.push_front(addingVectors.second);
			}
			if (NotInVecAddChain(vectorialAdditionChain, addingVectors.first) and NotInVecAddChain(basisVectors, addingVectors.first) and NotInVecAddChain(formedByBasisVectorsList, addingVectors.first))
			{
				vectorialAdditionChain.push_front(addingVectors.first);
			}
			currVector = addingVectors.first;
			break;
		}


	}


	if (NotInVecAddChain(formedByBasisVectorsList, currVector) and NotInVecAddChain(basisVectors,currVector))
	{
		vectorialAdditionChain.remove(currVector);
		formedByBasisVectorsList.push_front(currVector);
	}



	//решение проблемы с тремя и более единицами
	checkFormedByBasisVectorsList(&formedByBasisVectorsList);
	
	formedByBasisVectorsList = sortByOnesAmount(formedByBasisVectorsList);

	for (auto vec : formedByBasisVectorsList)
	{
		vectorialAdditionChain.push_front(vec);
	}
	//добавление базисных векторов в начало цепочки
	for (auto vec : basisVectors)
	{
		vectorialAdditionChain.push_front(vec);
	}

	return vectorialAdditionChain;
}

void printVector(std::vector<int> vector)
{
	for (int i = 0; i < vector.size()-1; i++)
	{
		std::cout << vector[i] << ',';
	}
	std::cout << vector[vector.size() - 1];
	std::cout << '\n';
}

std::list<std::vector<int>> getVectorialAdditionChainBinary(std::vector<int> findingVector)
{
	std::list<std::vector<int>> vectorialAdditionChain; //векторная аддитивная цепочка
	std::list<std::vector<int>> basisVectors = getBasisVectors(findingVector.size()); //получение базовых векторов простанства
	std::list<std::vector<int>> formedByBasisVectorsList; //вектора, содержащие 1 или 0 


	std::vector<int> currVector = findingVector; //очередной вектор в цепочке 

	//основной алгоритм 
	while (!VectorOneOrZero(currVector))
	{
		if (NotInVecAddChain(vectorialAdditionChain, currVector))
		{
			vectorialAdditionChain.push_front(currVector);
		}

		std::pair<std::vector<int>, std::vector<int>> addingVectors; //векторы, которые нужно будет добавить к векторной аддитивной цепочке
		if (!VectorIsEven(currVector))
		{
			addingVectors = getEvenVector(currVector);
			if (NotInVecAddChain(vectorialAdditionChain, addingVectors.first))
			{
				vectorialAdditionChain.push_front(addingVectors.first); //добавляем четный вектор
			}
			if (NotInVecAddChain(formedByBasisVectorsList, addingVectors.second) and NotInVecAddChain(basisVectors, addingVectors.second)) //если не в базисных или не в списке векторов 1 и 0
			{
				formedByBasisVectorsList.push_front(addingVectors.second); //добавляем вектор, чтобы четный стал искомым
			}
			currVector = addingVectors.first;
		}
		else
		{
			currVector = getDevidedBy2Vector(currVector);

			if (NotInVecAddChain(vectorialAdditionChain, currVector) and NotInVecAddChain(basisVectors, currVector) and NotInVecAddChain(formedByBasisVectorsList, currVector))
			{
				vectorialAdditionChain.push_front(currVector);
			}
		}

		


	}


	if (NotInVecAddChain(formedByBasisVectorsList, currVector) and NotInVecAddChain(basisVectors, currVector))
	{
		vectorialAdditionChain.remove(currVector);
		formedByBasisVectorsList.push_front(currVector);
	}

	//решение проблемы с тремя и более единицами
	checkFormedByBasisVectorsList(&formedByBasisVectorsList);

	formedByBasisVectorsList = sortByOnesAmount(formedByBasisVectorsList);

	for (auto vec : formedByBasisVectorsList)
	{
		vectorialAdditionChain.push_front(vec);
	}
	//добавление базисных векторов в начало цепочки
	for (auto vec : basisVectors)
	{
		vectorialAdditionChain.push_front(vec);
	}

	return vectorialAdditionChain;
}



#include <random>
int main()
{
	//FileUtil* fu = new FileUtil("1.txt");

	srand(time(NULL));
	
	int size = 7;
	std::vector<int> vec;
	for (int i = 0; i < size; i++)
	{
		vec.push_back(rand() % 3001 );
	}


	
	
	auto lst = getVectorialAdditionChain(vec);
	auto lst2 = getVectorialAdditionChainBinary(vec);

	/*for (auto var : lst)
	{
		printVector(var);
	}
	std::cout << "\n";
	for (auto var : lst2)
	{
		printVector(var);
	}
	std::cout << "\n";*/
	std::cout << lst2.size() << '\n' << lst.size();



}