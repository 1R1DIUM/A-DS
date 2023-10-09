#pragma once
//Prototypes of functions
int* SelectionSort(int*, int);
int* InsertionSort(int*, int);
void MergeSort(int*, int,int);
int* BubbleSort(int*, int);


int* Swap(int*, int, int);
std::pair<int, int> MIN(int*, int, int);
void DisplayArray(int*, int);
void Merge(int* ,int,int , int);
void merge(int*, int, int, int);



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

	//DisplayArray(arr,sizeof(arr)/sizeof(int));
	//std::cout << '\n';

}





////////////////////////////////////////////¬спомогательные функции////////////////////////////////////////////////////////



void Merge(int * arr, int begin, int mid , int end)
{
	//длина впомоательных массивов
	int const leftArrayLen = mid - begin + 1;
	int const rightArrayLen = end - mid;

	//создание вспомогательных массивов
	int* leftArray = new int[leftArrayLen];
	int* rightArray = new int[rightArrayLen];


	
	
	//

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




	//copy remaining elems
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