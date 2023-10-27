#pragma once
//Prototypes of functions

int* SelectionSort(int*, int);
int* InsertionSort(int*, int,int);
void MergeSort(int*, int,int);
int* BubbleSort(int*, int);
void QuickSort(int*, int,int);
void QuickSortMedianPivot(int*, int, int);
void HeapSort(int*, int);



int min(int, int);
bool checkIfSame(int*, int*, int);

void Sift_down(int*, int, int);
void Heapify(int*, int);
int Partition(int*, int, int);
int PartitionMedianPivot(int*, int, int); 
void Swap(int*, int, int);
std::pair<int, int> MIN(int*, int, int);
void DisplayArray(int*, int);
void Merge(int* ,int,int ,int);
void PivotMedian(int*, int, int, int);


//Алгоритмы сортировки

int* SelectionSort(int* arr, int len)
{
	for (int i = 0; i < len-1; i++)
	{
		int minIndex = MIN(arr, i, len).second; //поиска наименьшего значения
		Swap(arr, minIndex,i); //смена наименьшего на определенную позицию
	}
	return arr;
}


int* InsertionSort(int* arr, int left, int right)
{
	for (int i = left+1; i <= right; i++)
	{
		for (int j = i; j > left; j--)
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
void QuickSortMedianPivot(int* arr, int begin, int end)
{
	if (begin >= end) return;

	int baseElem = PartitionMedianPivot(arr, begin, end);
	QuickSortMedianPivot(arr, begin, baseElem - 1);
	QuickSortMedianPivot(arr, baseElem + 1, end);
}



void HeapSort(int *arr, int len)
{

	int L = len;
	Heapify(arr, len);
	while (L > 0)
	{
		Swap(arr, 0, L - 1);
		L--;
		Sift_down(arr, L, 0);

	}
}

////////////////////////////////////////////Вспомогательные функции////////////////////////////////////////////////////////

bool checkIfSame(int* arr,int* arr2, int len )
{
	bool Sorted = true;
	for (int i = 0; i < len; i++)
	{
		if (arr[i] != arr2[i])
		{
			Sorted = false;
			i = len; //выход из цикла
		}
	}
	return Sorted;
}


int min(int a, int b)
{
	int c = a < b ? a : b;
	return c;
}	

void Heapify(int* arr, int len)
{
	for (int i = len - 1; i >= 0; i--)
	{
		Sift_down(arr, len, i);
	}
}
void Sift_down(int* arr, int len, int index)
{
	
	int biggest = index; 
	int left = 2 * index + 1;
	int right = 2 * index + 2; 

	if (left >= len) return;
	if (right >= len) { arr[index] > arr[left] ? biggest = index : biggest = left; }
	else
	{
		if (arr[left] >= arr[right])
		{
			biggest = left;
		}
		else
		{
			biggest = right;
		}
	}

	if (biggest != index) 
	{
		Swap(arr, biggest, index);
		Sift_down(arr, len, biggest);
	}
	
}


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

int PartitionMedianPivot(int* arr, int begin, int end)
{
	PivotMedian(arr, begin, begin + (end - begin) / 2, end);

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

	//индексы для вспомогательных и и основного массива
	int a, b, c;
	a = b = 0;
	c = begin;

	while (a < leftArrayLen && b < rightArrayLen)
	{
		if (leftArray[a] <= rightArray[b])
		{
			arr[c] = leftArray[a];
			a++;
		}
		else
		{
			arr[c] = rightArray[b];
			b++;
		}
		c++;
	}

	//копирование оставшихся элементов
	while (a < leftArrayLen)
	{
		arr[c] = leftArray[a];
		a++;
		c++;
	}
	while (b < rightArrayLen)
	{
		arr[c] = rightArray[b];
		c++;
		b++;
	}

	delete[] leftArray;
	delete[] rightArray;
}



void Swap(int* arr, int FirstIndex, int SecondIndex)
{
	int temp;
	temp = arr[FirstIndex];
	arr[FirstIndex] = arr[SecondIndex];
	arr[SecondIndex] = temp;
}

//Поиск наименьшего значения (first) /индекса значения (second) в массиве (arr) от (Begin) до (End)
std::pair<int, int> MIN(int* arr, int Begin, int End)
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


void PivotMedian(int* arr, int a, int b, int c)
{
	//пусть медиана находится в конце
	if (arr[c] < arr[a])
	{
		Swap(arr, a, c);
	}
	if (arr[c] < arr[b])
	{
		Swap(arr, b, c);
	}
	if (arr[a] < arr[b])
	{
		Swap(arr, b, c);
	}
}
//////////////////////////////
class Introsort
{
	void IntroSortRec(int *arr, int begin, int end, int depth)
	{
		int size = end - begin;

		if (size < 16)
		{
			InsertionSort(arr, begin, end);
			return;
		}

		if (depth == 0)
		{
			HeapSort(arr, end - begin+1);
			return;
		}

		//PivotMedian(arr, begin, begin + (end - begin) /2 , end);
		/*int medianIndex = MedianOfThree(arr, begin, begin + (end - begin) / 2, end);
		Swap(arr, end, medianIndex);*/
		PivotMedian(arr, begin, begin + (end - begin) / 2, end);

		int partitionIndex = Partition(arr, begin, end);
		IntroSortRec(arr, begin, partitionIndex-1, depth - 1);
		IntroSortRec(arr, partitionIndex + 1, end, depth-1);

		return;
	}
public:
	void IntroSort(int* arr, int begin, int end)
	{
		int depth = 2 * log(end - begin);
		IntroSortRec(arr, begin, end, depth);

	}

};


#include <vector>
class ShellSortClass
{
public:
	int PrattArrSize;
	std::vector<int> Pratt_vector;
	int* PrattArr;

	std::vector<int> Div_vector;
	int* DivArr;
	int DivArrSize;
	void ShellSortDivision(int* arr, int len)
	{
		int* step = DivArr + DivArrSize - 1;
		int i = 0;


		while (step != DivArr-1)
		{
			i = 0;
			while (i < len - *step)
			{
				int j = i;
				while (j >= 0)
				{
					if (arr[j] >= arr[j + *step])
					{
						Swap(arr, j, j + *step);
					}
					else
					{
						break;
					}
					j -= *step;
				}
				i += *step;
			}
			step--;
		}

		delete[] DivArr;
	}
	void GeneratetDivArray(int len)
	{
		
		for (int i = len / 2; i > 0; i /= 2)
		{
			Div_vector.push_back(i);
		}
		DivArrSize = Div_vector.size();
		DivArr = new int[DivArrSize];
		for (int i = 0; i < DivArrSize; i++)
		{
			DivArr[i] = Div_vector[i];
		}

		Div_vector.clear();

	}

	void addCiuraSequence(int len)
	{
		int i = 0;
		bool bigger = false;
		for (; i < PrattArrSize; i++)
		{
			if (PrattArr[i] > 701)
			{
				bigger = true;
				break;
			}
		}

		if (bigger)
		{
			Pratt_vector = { 1, 4, 10, 23, 57, 132, 301, 701 };
			for (; i < PrattArrSize; i++)
			{
				Pratt_vector.push_back(PrattArr[i]);
			}
			PrattArrSize = PrattArrSize - i + 8;

			for (int k = 0; k < PrattArrSize; k++)
			{
				PrattArr[k] = Pratt_vector[k];
			}
			Pratt_vector.clear();
		}


	}


	void GeneratePrattArray(int len)
	{
		int pow3 = 1;
		while (pow3 <= len)
		{
			int pow2 = pow3;
			while (pow2<= len)
			{
				Pratt_vector.push_back(pow2);
				pow2 *= 2;
			}
			pow3 *= 3;
		}
	
		PrattArrSize = Pratt_vector.size();
		PrattArr = new int[PrattArrSize];
		for (int i = 0; i < PrattArrSize; i++)
		{
			PrattArr[i] = Pratt_vector[i];
		}
		HeapSort(PrattArr, PrattArrSize);
		Pratt_vector.clear();
	}

	void ShellSortPratt(int* arr, int len)
	{

		int* step = PrattArr + PrattArrSize - 1;
		int i = 0;


		while(step != PrattArr)
		{
			i = 0;
			while (i < len - *step)
			{
				int j = i;
				while (j >= 0)
				{
					if (arr[j] >= arr[j + *step])
					{
						Swap(arr, j, j + *step);
					}
					else
					{
						break;
					}
					j -= *step;
				}
				i += *step;
			}
			step--;
		}




		delete[] PrattArr;
	}
};



class TimSortClass
{
	int minrun;



	struct Stack
	{
		int Start;
		int Lenght;
		Stack* next;
	};
	Stack* StackHead = nullptr;
	int RunNum = 0;


	void findMinRun(int len)
	{
		while (len >= 64)
		{
			len /= 2;
		}
		minrun = len;

	}


	void AppendStack(int start, int lenght)
	{
		Stack* elem = new Stack;
		elem->Lenght = lenght;
		elem->Start = start;

		if (StackHead == nullptr)
		{
			elem->next = nullptr;
		}
		else
		{
			elem->next = StackHead;

		}
		StackHead = elem;
		RunNum++;
	}

	Stack* GetElemByIndex(int index)
	{
		Stack* curr = StackHead;
		for (int i = 0; i < index; i++)
		{
			curr = curr->next;
		}
		return curr;

	}

	void DisplayStack()
	{
		Stack* curr = StackHead;
		while (curr != nullptr)
		{
			std::cout << curr->Start << ' ' << curr->Lenght << '\n';
			curr = curr->next;
		}
	}

	void ReverseRun(int*arr,int start, int end)
	{
		for(int i=start; i < start+(end-start)/2+1;i++)
		{
			Swap(arr, i, end - i);
		}
	}


	void findRuns(int* arr, int len)
	{

		int i = 0;
		int startRun = 0;
		int runLen = 1;

		while (i < len)
		{
			//проверка последнего элемента
			if (i == len - 1)
			{
				AppendStack(i, 1);
				i++;
			}
			else
			{
				bool increasing = true;
				if (arr[i] < arr[i + 1]) //Возрастающая последовательность
				{
					i++;
					runLen++;
					while (arr[i] < arr[i + 1] and i < len-1)
					{
						i++;
						runLen++;
					}
					//возрастающая последовательность закончилась
				}
				else
				{
					//убывающая последовательность
					increasing = false;
					i++;
					runLen++;
					while (arr[i] > arr[i + 1] and i < len-1)
					{
						i++;
						runLen++;
					}
					//восхождающая последовательность закончилась
				}

				//заканчиваем пробег и
				if (runLen < minrun)
				{
					if (startRun + minrun <= len)
					{
						InsertionSort(arr, startRun, startRun + minrun - 1);
						AppendStack(startRun, minrun);
						i = startRun + minrun;
					}
					else
					{
						InsertionSort(arr, startRun, len - 1);
						AppendStack(startRun, len - 1 - startRun);
						break;
					}
				}
				else
				{
					if (!increasing)
					{
						ReverseRun(arr, startRun, startRun + runLen - 1);
					}
					AppendStack(startRun, runLen);
					i += runLen;
				}
				Merging(arr);
				//переходим к следующему элементу

				startRun = i;
				runLen = 1;
			}
		}

	}

	//Первый элемент должен быть ближе к головному элементу, чем второй
	void StackMerge(Stack* firstElem, Stack* secondElem)
	{
		Stack* prev = StackHead;
		while (prev->next != firstElem and prev != firstElem)
		{
			prev = prev->next;
		}
		prev->next = secondElem;
		secondElem->Lenght += firstElem->Lenght;
		if (prev == firstElem)
		{
			StackHead = secondElem;
		}
		delete firstElem;
	}
	void ForceMerge(int* arr)
	{
		while (RunNum > 1)
		{
			if (RunNum >= 3)
			{
				if (GetElemByIndex(0)->Lenght > GetElemByIndex(2)->Lenght)
				{
					int begin = GetElemByIndex(2)->Start;
					int end = GetElemByIndex(1)->Lenght + GetElemByIndex(1)->Start - 1;
					int mid = begin + GetElemByIndex(2)->Lenght - 1;
					StackMerge(GetElemByIndex(1), GetElemByIndex(2));
					Merge(arr, begin, mid, end);
					RunNum--;
				}
				else
				{
					int begin = GetElemByIndex(1)->Start;
					int end = GetElemByIndex(0)->Lenght + GetElemByIndex(0)->Start - 1;
					int mid = begin + GetElemByIndex(1)->Lenght - 1;
					StackMerge(GetElemByIndex(0), GetElemByIndex(1));
					Merge(arr, begin, mid, end);
					RunNum--;
				}
			}
			if (RunNum == 2)
			{
				int begin = GetElemByIndex(1)->Start;
				int end = GetElemByIndex(0)->Lenght + GetElemByIndex(0)->Start - 1;
				int mid = begin + GetElemByIndex(1)->Lenght - 1;
				StackMerge(GetElemByIndex(0), GetElemByIndex(1));
				Merge(arr, begin, mid, end);
				RunNum--;


			}
		}
		StackHead->next = nullptr;
		StackHead->Lenght = NULL;
		StackHead->Start = NULL;
		delete StackHead;
	}

	void Merging(int* arr)
	{
		while (true)
		{
			bool three = true; bool two = true;
			if (RunNum >= 3)
			{

				if (GetElemByIndex(0)->Lenght + GetElemByIndex(1)->Lenght > GetElemByIndex(2)->Lenght)
				{
					three = false;
					if (GetElemByIndex(0)->Lenght > GetElemByIndex(2)->Lenght)
					{

						int begin = GetElemByIndex(2)->Start;
						int end = GetElemByIndex(1)->Lenght + GetElemByIndex(1)->Start - 1;
						int mid = begin + GetElemByIndex(2)->Lenght - 1;
						StackMerge(GetElemByIndex(1), GetElemByIndex(2));
						Merge(arr, begin, mid, end);
						RunNum--;
					}
					else
					{
						int begin = GetElemByIndex(1)->Start;
						int end = GetElemByIndex(0)->Lenght + GetElemByIndex(0)->Start - 1;
						int mid = begin + GetElemByIndex(1)->Lenght - 1;
						StackMerge(GetElemByIndex(0), GetElemByIndex(1));
						Merge(arr, begin, mid, end);
						RunNum--;
					}
				}
			}
			if (RunNum >= 2)
			{

				if (GetElemByIndex(0)->Lenght > GetElemByIndex(1)->Lenght)
				{
					two = false;

					int begin = GetElemByIndex(1)->Start;
					int end = GetElemByIndex(0)->Lenght + GetElemByIndex(0)->Start - 1;
					int mid = begin + GetElemByIndex(1)->Lenght - 1;
					StackMerge(GetElemByIndex(0), GetElemByIndex(1));
					Merge(arr, begin, mid, end);
					RunNum--;
				}

			}
			if (two and three || RunNum == 1)
			{
				break;
			}
		}
	}

public:
	void TimSort(int* arr, int len)
	{
		findMinRun(len);
		findRuns(arr, len);

		ForceMerge(arr);
		RunNum = 0;

	}
};