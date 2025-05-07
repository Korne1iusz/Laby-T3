#pragma once
//#include <fstream>
//#include <vector>
//#include "Point.h"
//#include "FileError.h"
#include "IFile.h"
class BinaryFile: public IFile
{
private:
public:
	BinaryFile(const std::string, const std::string);
	~BinaryFile();

	FileError Write(const std::vector<Point>&);
	FileError Read(std::vector<Point>&);
	FileError Read(Point&, const unsigned long);
};

