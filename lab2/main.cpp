#include <iostream>



#include "Sorts and functions.h"


int main()
{
	int testArr[] = { 3,2,4,1 ,12,32 ,-5, 45,0};
	int len = sizeof(testArr) / sizeof(testArr[0]);
	


	DisplayArray(testArr, len);
	MergeSort(testArr, 0, len - 1);

	DisplayArray(testArr, len);



}






