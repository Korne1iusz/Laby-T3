#pragma once
#include <fstream>
#include <vector>
#include "Point.h"
#include "IFile.h"

class BinaryFile : public IFile
{
public:
	BinaryFile(const std::string filePath, const std::string mode);

	Error Write(const std::vector<Point>&) override;
	Error Read(std::vector<Point>&) override;
	Error Read(Point&, const unsigned long) override;
};