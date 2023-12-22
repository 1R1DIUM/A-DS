#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "VectorsInfo.h"

class FileUtil
{
private:
	std::ifstream readStream;
public:
	FileUtil(std::string fileName);

	VectorsInfo getVectorsFromFile();
};

