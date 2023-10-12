#pragma once
//Prototypes of functions

int* SelectionSort(int*, int);
int* InsertionSort(int*, int);
void MergeSort(int*, int,int);
int* BubbleSort(int*, int);
void QuickSort(int*, int,int);


int Partition(int*, int, int);
int* Swap(int*, int, int);
std::pair<int, int> MIN(int*, int, int);
void DisplayArray(int*, int);
void Merge(int* ,int,int , int);



//јлгоритмы сортировки

int* SelectionSort(int* arr, int len)
{
	for (int i = 0; i < len-1; i++)
	{
		int minIndex = MIN(arr, i, len).second; //поиска наименьшего значени€
		Swap(arr, minIndex,i); //смена наименьшего на определенную позицию
	}
	return arr;
}

int* InsertionSort(int* arr, int len)
{
	for (int i = 1; i < len; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (arr[j] < arr[j - 1])
			{
				Swap(arr, j, j - 1);
			}
			else
			{
				break;
			}
		}
	}
	return arr;
}

int* BubbleSort(int* arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(arr, j, j + 1);
			}
		}
	}
	return arr;
}



void MergeSort(int* arr,int begin, int end)
{
	if (begin >=end)
	{
		return;
	}
	int mid = begin + (end - begin) / 2;
	MergeSort(arr, begin, mid);
	MergeSort(arr, mid + 1, end);
	Merge(arr,begin,mid,end);


}


void QuickSort(int *arr, int begin,int end)
{
	if (begin >= end) return;
	
	int baseElem = Partition(arr, begin, end);
	QuickSort(arr, begin, baseElem - 1);
	QuickSort(arr, baseElem+1, end);
	
}





////////////////////////////////////////////¬спомогательные функции////////////////////////////////////////////////////////


int Partition(int* arr, int begin, int end)
{
	int baseElem = arr[end]; //опорный элемент 
	int PartIndex = begin; 

	
	for (int i = begin; i < end; i++)
	{
		if (arr[i] < baseElem)
		{
			Swap(arr, i, PartIndex); //перенос в левый "массив" элементов, меньших опорного
			PartIndex++;
		}
	}
	Swap(arr, end, PartIndex);//разграничение двух "массивов" 
	
	return PartIndex;
}



void Merge(int * arr, int begin, int mid , int end)
{
	//длина впомоательных массивов
	int const leftArrayLen = mid - begin + 1;
	int const rightArrayLen = end - mid;

	//создание вспомогательных массивов
	int* leftArray = new int[leftArrayLen];
	int* rightArray = new int[rightArrayLen];

	//заполнение массивов

	for (int i = 0; i < leftArrayLen; i++)
	{
		leftArray[i] = arr[begin + i];
	}
	for (int i = 0; i < rightArrayLen; i++)
	{
		rightArray[i] = arr[mid + 1 + i];
	}

	//индексы дл€ вспомогательных и и основного массива
	int a, b, c;
	a = b = 0;
	c = begin;

	while (a < leftArrayLen && b < rightArrayLen)
	{
		if (leftArray[a] <= rightArray[b])
		{
			arr[c++] = leftArray[a++];
		}
		else
		{
			arr[c++] = rightArray[b++];
		}
	}

	//копирование оставшихс€ элементов
	while (a<leftArrayLen)
	{
		arr[c++] = leftArray[a++];
	}
	while (b<rightArrayLen)
	{
		arr[c++] = rightArray[b++];
	}

	delete[] leftArray;
	delete[] rightArray;
}



int* Swap(int* arr, int FirstIndex, int SecondIndex)
{
	int temp;
	temp = arr[FirstIndex];
	arr[FirstIndex] = arr[SecondIndex];
	arr[SecondIndex] = temp;
	return arr;
}

//ѕоиск наименьшего значени€ (first) /индекса значени€ (second) в массиве (arr) от (Begin) до (End)
std::pair<int,int> MIN(int* arr, int Begin, int End)
{
	int min = arr[Begin];
	int minIndex = Begin;
	for (int i = Begin; i < End; i++)
	{
		if (arr[i] < min) { minIndex = i; min = arr[i]; }
	}

	return std::make_pair(min, minIndex);
}

void DisplayArray(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << '\n';
}


//////////////////////////////
#include <vector>
class ShellSortClass
{
	struct Steps
	{
		std::vector<int> Step1;
		std::vector<int> Step2;
		std::vector<int> Step3;
	} StepStruct;
	void InitFirstStep(int len)
	{
		int i = 0;
		while (int(len / (1 << (i + 1)) != 0))
		{
			StepStruct.Step1.push_back(len / (1 << (i + 1)));
			i++;
		}
	}
	void InitSecondStep()
	{
		//In process
	}

	void InitThirdStep()
	{
		//In process
	}


public:

	void FirstStepSort(int* arr, int len)
	{
		InitFirstStep(len);
		int * TempArray = new int [StepStruct.Step1.size()];

		for (int i = 0; i < StepStruct.Step1.size(); i++)
		{
			TempArray[i] = StepStruct.Step1[i];
		}

		ShellSort(TempArray, StepStruct.Step1.size(), arr, len);
		delete[] TempArray;
	}



	void ShellSort(int* Steps, int SLen, int* arr, int len)
	{
		for (int h = 0; h < SLen; h++)
		{
			for (int i = 0; i < len - Steps[h]; i += Steps[h])
			{
				int j = i;
				while (j >= 0)
				{
					if (arr[j] >= arr[j + Steps[h]])
					{
						Swap(arr, j, j + Steps[h]);
					}
					j -= Steps[h];
				}
			}
		}
	}


};