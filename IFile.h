#pragma once
#include <fstream>
#include <vector>
#include "Point.h"
#include "FileError.h"
class  IFile
{
protected:
	std::fstream file;
	std::string filePath;
	unsigned long length;
	std::fstream::openmode openMode;
public:
    IFile(std::string,std::string);
    ~IFile();
    virtual FileError Read(std::vector<Point>&);
    virtual FileError Read(Point&, int);
    virtual FileError Write(const std::vector<Point>);
};
