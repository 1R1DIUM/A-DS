#include <iostream>
#include "Sorts and functions.h"


int main()
{
	int testArr[128];
	for (int i = 0; i < 128; i++)
	{
		testArr[i] = 128 - i;
	}
	int len = sizeof(testArr) / sizeof(testArr[0]);
	

	DisplayArray(testArr, len);
	TimSort(testArr, len);
	DisplayArray(testArr, len);




}






