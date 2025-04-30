#include "CsvFile.h"
#include <cstring>
#include <format>
#include <iostream>
#include <sstream>

CsvFile::CsvFile(const std::string filePath, const std::string mode) : IFile(filePath, mode)
{
}

IFile::Error CsvFile::Write(const std::vector<Point>& v)
{
	IFile::Error retVal = IFile::Error(ACCESS_DENIED);

	if (!file.is_open())
	{
		retVal = IFile::Error(FILE_INVALID);
	}
	else if (openMode & std::fstream::out)
	{
		for (int i = 0; i < v.size(); i++)
		{
			Point p = v.at(i);
			file << p.x << ";" << p.y << ";" << p.z << std::endl;
		}

		retVal = IFile::Error(SUCCESS);
	}

	return retVal;
}

IFile::Error CsvFile::Read(std::vector<Point>& v)
{
	IFile::Error retVal = IFile::Error(ACCESS_DENIED);

	if (!file.is_open())
	{
		retVal = IFile::Error(FILE_INVALID);
	}
	else if (openMode & std::fstream::in)
	{
		v.clear();
		file.clear();
		file.seekg(0, std::fstream::beg);

		std::string line;
		retVal = IFile::Error(SUCCESS);

		while (std::getline(file, line))
		{
			std::vector<std::string> wartosci = Split(line, ';');

			if (wartosci.size() != 3)
			{
				retVal = IFile::Error(FILE_INVALID);
				break;
			}

			Point p(std::stod(wartosci.at(0)), std::stod(wartosci.at(1)), std::stod(wartosci.at(2)));
			v.push_back(p);
		}
	}

	return retVal;
}

IFile::Error CsvFile::Read(Point& p, const unsigned long idx)
{
	IFile::Error retVal = IFile::Error(ACCESS_DENIED);

	if (!file.is_open())
	{
		retVal = IFile::Error(FILE_INVALID);
	}
	else if (openMode & std::fstream::in)
	{
		std::string line;
		unsigned long aktulany_idx = 0;
		file.clear();
		file.seekg(0, std::fstream::beg);

		while (aktulany_idx <= idx && std::getline(file, line))
		{
			aktulany_idx++;
		}

		if (aktulany_idx == 0 || aktulany_idx <= idx)
		{
			retVal = IFile::Error(OUT_OF_BOUNDS);
		}
		else
		{
			std::vector<std::string> wartosci = Split(line, ';');

			if (wartosci.size() != 3)
			{
				retVal = IFile::Error(FILE_INVALID);
			}
			else
			{
				p.x = std::stod(wartosci.at(0));
				p.y = std::stod(wartosci.at(1)); 
				p.z = std::stod(wartosci.at(2));

				retVal = IFile::Error(SUCCESS);
			}

		}

	}

	return retVal;
}

std::vector<std::string> CsvFile::Split(std::string str, char delim) 
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string item;
	
	while (getline(ss, item, delim)) 
	{ 
		result.push_back(item); 
	} 
	
	return result;
}