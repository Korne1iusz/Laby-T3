
#pragma once
//#include <fstream>
//#include <vector>
//#include "Point.h"
//#include "FileError.h"
#include "IFile.h"
#include <sstream>
class CsvFile: public IFile
{
private:
	std::vector<std::string> Split(std::string, char);
	std::string PointToString(Point pkt);
	std::string VectorToString(std::vector<Point> wektor);
	Point VstringtoPoint(std::vector<std::string>);
public:
	CsvFile(const std::string, const std::string);
	~CsvFile();

	FileError Write(const std::vector<Point>&);
	FileError Read(std::vector<Point>&);
	FileError Read(Point&, const unsigned long);
};
