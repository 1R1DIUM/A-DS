#include "FileUtil.h"
#include <iostream>
#include <list>
#include <vector>

std::list<std::vector<int>*> allocatedVectorsList;



std::list<std::vector<int>> getBasisVectors(int size) //получение базисных векторов размерности простанства (обратные) т.е. первый (0,0,1)
{
	std::list<std::vector<int>> basisVectors;
	int coefIter = size-1; //
	for (int vectorIter = 0; vectorIter < size; vectorIter++,coefIter--)
	{
		std::vector<int>* newBasisVector = new std::vector<int>;
		allocatedVectorsList.push_back(newBasisVector); //нужно потом для удаления
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



std::list<std::vector<int>> formNewFormedByBasisVector(std::list<std::vector<int>> lst, std::vector<int> vector)
{
	std::list<std::vector<int>> addingList; //список векторов, которые нужно дополнить, чтобы цепочка стала аддитивной
	if (NotInVecAddChain(lst, vector))
	{
		lst.push_back(vector);
		addingList.push_back(vector);
	}
	
	
	if (getOnesInVectorAmount(vector) < 3) //если очердной вектор можно сформировать из базисных
	{
		return addingList;
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
				maxSimularVector = vect;
				maxSimularity = simularity;
			}
		}

		return formNewFormedByBasisVector(lst, subTwoVectors(vector, maxSimularBasisVector));
	}


	return formNewFormedByBasisVector(lst, subTwoVectors(vector, maxSimularVector));
}



void checkFormedByBasisVectorsList(std::list<std::vector<int>>* lst) //проверка на аддитивность цепочки векторов, сформированных из базисных
{
	for (auto vect : *lst)
	{
		if (getOnesInVectorAmount(vect) > 2)
		{
			std::list<std::vector<int>> addingList = formNewFormedByBasisVector(*lst, vect);
			for (auto elem : addingList)
			{
				lst->push_front(elem);
			}
		}
	}


}


#include <algorithm>


std::list<std::vector<int>> sortByOnesAmount(std::list<std::vector<int>> lst)
{

	std::list<std::vector<int>> returnList;

	//std::list -> std::vector
	std::vector<std::vector<int>> listVect;
	for (auto vector : lst)
	{
		listVect.push_back(vector);
	}



	//insertionSort
	/*auto iter1 = ++returnList.begin();
	for (int i = 1; i < returnList.size(); i++, iter1++)
	{
		auto iter2 = iter1;
		for (int j = i; j > 1; j--, iter2--)
		{
			if (getOnesInVectorAmount(listVect[j]) < getOnesInVectorAmount(listVect[j - 1]))
			{
				std::iter_swap(iter2, --iter2);
				auto temp = listVect[j];
				listVect[j] = listVect[j - 1];
				listVect[j - 1] = temp;
			}
			else
			{
				break;
			}
		}
	}*/

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

		if (VectorIsEven(currVector)) //если вектор состоит только из четных чисел
		{
			currVector = getDevidedBy2Vector(currVector);

			if (NotInVecAddChain(vectorialAdditionChain, currVector) and NotInVecAddChain(basisVectors,currVector) and NotInVecAddChain(formedByBasisVectorsList,currVector))
			{
				vectorialAdditionChain.push_front(currVector);
			}
		}
		else
		{	
			std::pair<std::vector<int>, std::vector<int>> addingVectors = getEvenVector(currVector);
			if (NotInVecAddChain(vectorialAdditionChain, addingVectors.first))
			{
				vectorialAdditionChain.push_front(addingVectors.first); //добавляем четный вектор
			}
			if (NotInVecAddChain(formedByBasisVectorsList, addingVectors.second) and NotInVecAddChain(basisVectors,addingVectors.second)) //если не в базисных или не в списке векторов 1 и 0
			{
				formedByBasisVectorsList.push_front(addingVectors.second); //добавляем вектор, чтобы четный стал искомым
			}
			currVector = addingVectors.first;
		}
	}


	if (NotInVecAddChain(formedByBasisVectorsList, currVector))
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


int main()
{
	FileUtil* fu = new FileUtil("1.txt");
	std::list<std::vector<int>> lst = getVectorialAdditionChain(fu->getVectorsFromFile().vectors.back());
	/*std::list<std::vector<int>> lst = getVectorialAdditionChain({ 177,205,131,201,475});*/  
	


	for (auto var : lst)
	{
		printVector(var);
	}

}