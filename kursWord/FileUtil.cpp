#include "FileUtil.h"

FileUtil::FileUtil(std::string fileName)
{
	//Попытка открыть файл
	readStream.open(fileName);
	if (!readStream.is_open())
	{
		std::cout << "Cannot open file!\n";
	}
}

VectorsInfo FileUtil::getVectorsFromFile()
{
	VectorsInfo vec;
	try
	{
		if (!readStream)
		{
			throw "Trying to get vectors from non-existing file!";
		}

		std::string line;
		while (std::getline(readStream, line)) //пока есть строки, которые можно прочитать
		{
			std::vector<int> tempVector; //вектор для хранения и записи данных в vec

			//обработка строки
			int i = 1, j = 0; // i - конец числа; j - начало числа
			while (line[i - 1] != 0 and line[i - 1] != '\n')
			{
				if (line[i] == ',' or line[i] == '\n' or line[i] == 0)
				{
					tempVector.push_back(std::stoi(line.substr(j, i))); //делаем срез до разделителя
					j = i + 1;
				}
				i++;
			}

			//Запись в vec данных
			vec.vectors.push_back(tempVector);
			vec.count = tempVector.size();
			tempVector.clear();
		}

	}
	catch (const char* err_message)
	{
		std::cout << err_message << '\n';
	}
	return vec;
}