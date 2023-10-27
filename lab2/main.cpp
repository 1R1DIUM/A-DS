#include <iostream>
#include <math.h>
#include "Sorts and functions.h"
#include <random>
#include <chrono>




void FillRandom(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = rand();
	}
}

void FillAlmostSorted(int* arr, int len)
{
	for (int i = 0; i < len-1; i++)
	{
		arr[i] = i;
	}
	arr[len - 1] = rand();

}
void FillSorted(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = i;
	}
}
void FillReverseSorted(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = len-i-1;
	}

}


int main()
{
	
	Introsort is;
	int lenArray[] = { 50,100,500,1000,5000,10000,15000,20000,25000,30000,35000,40000,45000,50000,55000,60000,65000,70000,75000,80000,85000,90000,95000,100000};
	ShellSortClass sh;

	for (int i = 0; i < 24; i++)
	{
		srand(0);
		int LENGHT = lenArray[i];
		int* testArr = new int[LENGHT];



		auto begin = std::chrono::steady_clock::now();
		auto end = std::chrono::steady_clock::now();

		FillAlmostSorted(testArr, LENGHT);



		sh.GeneratePrattArray(LENGHT);
		sh.addCiuraSequence(LENGHT);

		//sh.GeneratetDivArray(LENGHT);

		begin = std::chrono::steady_clock::now();
		
		
		//sh.ShellSortDivision(testArr, LENGHT);
		sh.ShellSortPratt(testArr, LENGHT);

		end = std::chrono::steady_clock::now();
		
		//DisplayArray(testArr, LENGHT);
		
		std::cout  << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << ' ';
		delete[] testArr;
	}





}






