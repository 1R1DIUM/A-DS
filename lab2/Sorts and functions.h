#pragma once
//Prototypes of functions

int* SelectionSort(int*, int);
int* InsertionSort(int*, int,int);
void MergeSort(int*, int,int);
int* BubbleSort(int*, int);
void QuickSort(int*, int,int);
void HeapSort(int*, int);
void TimSort(int*, int);



int min(int, int);



void Sift_down(int*, int, int);
void Heapify(int*, int);
int Partition(int*, int, int);
int* Swap(int*, int, int);
std::pair<int, int> MIN(int*, int, int);
void DisplayArray(int*, int);
void Merge(int* ,int,int ,int);



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


void HeapSort(int* arr, int len)
{
	int L = len;
	Heapify(arr, len);
	while (L>0)
	{
		Swap(arr, 0, L - 1);
		L--;
		Sift_down(arr, L, 0);
		
	}
}


void TimSort(int* arr, int len)
{
	int len_copy = len;
	while (len_copy >= 64)
	{
		len_copy /= 2;
	}
	int RUN = len_copy;

	for (int i = 0; i < len; i += RUN)
	{
			 // индекс границ пробега
		InsertionSort(arr, i, min(i+RUN-1,len-1));
	}
	//соединение остортированных массивов
	for (int size = RUN; size < len; size = 2 * size)
	{
		for (int left = 0; left < len; left += 2 * size)
		{
			int mid = left + size - 1;
			int right = min((left + 2 * size - 1), (len - 1));
			
			if (mid < right)
			{
				Merge(arr, left, mid, right);
			}
		}
	}

}





////////////////////////////////////////////¬спомогательные функции////////////////////////////////////////////////////////

int min(int a, int b)
{
	int c = a < b ? a : b;
	return c;
}	

void Heapify(int * arr, int len)
{
	for (int i = len - 1; i >= 0; i--)
	{
		Sift_down(arr, len, i);
	}
}

void Sift_down(int* arr, int len, int index)
{
	
	int biggest = index; //—читаем, что наибольший элемент у родител€
	int left = 2 * index + 1; //¬ычисл€ем левый дочерний элемент 
	int right = 2 * index + 2; //¬ычисл€ем правый дочерний элемент 

	if (left >= len) return;
	if (right >= len) { biggest = left; }
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


	Swap(arr, biggest, index);
	Sift_down(arr, len, biggest);
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

	//копирование оставшихс€ элементов
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



int* Swap(int* arr, int FirstIndex, int SecondIndex)
{
	int temp;
	temp = arr[FirstIndex];
	arr[FirstIndex] = arr[SecondIndex];
	arr[SecondIndex] = temp;
	return arr;
}

//ѕоиск наименьшего значени€ (first) /индекса значени€ (second) в массиве (arr) от (Begin) до (End)
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
	//пусть медиана находитс€ в конце
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
int MedianOfThree(int* arr,int a, int b, int c)
{
	if (arr[a] < arr[b] && arr[b] < arr[c])
		return (b);

	if (arr[a] < arr[c] && arr[c] <= arr[b])
		return (c);

	if (arr[b] <= arr[a] && arr[a] < arr[c])
		return (a);

	if (arr[b] < arr[c] && arr[c] <= arr[a])
		return (c);

	if (arr[c] <= arr[a] && arr[a] < arr[b])
		return (a);

	if (arr[c] <= arr[b] && arr[b] <= arr[a])
		return (b);
}


//////////////////////////////
class Intosort
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



class ShellSortClass
{
public:
	void ShellSortDivision(int* arr, int len)
	{
		for (int step = len / 2; step != 1; step /= 2)
		{
			for (int i = step; i < len; i += 1)
			{
				int temp = arr[i];
				int j;
				for (j = i; j >= step && arr[j - step] > temp; j -= step)
				{
					arr[j] = arr[j - step];
				}
				arr[j] = temp;
			}
		}
	}
	void ShellSortExponencial(int* arr, int len)
	{
		int k = 1;
		for (int step = 1; step <=len; step = pow(2,k++)-1)
		{
			for (int i = step; i < len; i += 1)
			{
				int temp = arr[i];
				int j;
				for (j = i; j >= step && arr[j - step] > temp; j -= step)
				{
					arr[j] = arr[j - step];
				}
				arr[j] = temp;
			}
		}
	}
	void ShellSortSubstact(int* arr, int len)
	{
		for (int step = len / 2; step != 1; step--)
		{
			for (int i = step; i < len; i += 1)
			{
				int temp = arr[i];
				int j;
				for (j = i; j >= step && arr[j - step] > temp; j -= step)
				{
					arr[j] = arr[j - step];
				}
				arr[j] = temp;
			}
		}
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
				/*AppendStack(i, 1);
				i++;*/
			}
			else
			{
				bool increasing = true;
				if (arr[i] < arr[i + 1]) //¬озрастающа€ последовательность
				{
					i++;
					runLen++;
					while (arr[i] < arr[i + 1] and i < len-1)
					{
						i++;
						runLen++;
					}
					//возрастающа€ последовательность закончилась
				}
				else
				{
					//убывающа€ последовательность
					increasing = false;
					i++;
					runLen++;
					while (arr[i] > arr[i + 1] and i < len-1)
					{
						i++;
						runLen++;
					}
					//восхождающа€ последовательность закончилась
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

	//ѕервый элемент должен быть ближе к головному элементу, чем второй
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