#include "BinaryFile.h"

BinaryFile::BinaryFile(const std::string filePath, const std::string mode) : IFile(filePath, mode)
{
}


IFile::Error BinaryFile::Write(const std::vector<Point>& v)
{
	IFile::Error retVal = IFile::Error(ACCESS_DENIED);

	if (!file.is_open())
	{
		retVal = IFile::Error(FILE_INVALID);
	}
	else if (openMode & std::fstream::out)
	{
		file.write((const char *)v.data(), v.size() * sizeof(Point));
		retVal = IFile::Error(SUCCESS);
	}

	return retVal;
}

IFile::Error BinaryFile::Read(std::vector<Point>& v)
{
	IFile::Error retVal = IFile::Error(ACCESS_DENIED);

	if (!file.is_open())
	{
		retVal = IFile::Error(FILE_INVALID);
	}
	else if (openMode & std::fstream::in)
	{
		v.clear();
		v.resize(length / sizeof(Point));
		file.seekg(0, std::fstream::beg);
		file.read((char *)v.data(), length);
		retVal = IFile::Error(SUCCESS);
	}

	return retVal;
}

IFile::Error BinaryFile::Read(Point & p, const unsigned long idx)
{
	IFile::Error retVal = IFile::Error(ACCESS_DENIED);

	if (!file.is_open())
	{
		retVal = IFile::Error(FILE_INVALID);
	}
	else if (idx >= length / sizeof(Point))
	{
		retVal = IFile::Error(OUT_OF_BOUNDS);
	}
	else if (openMode & std::fstream::in)
	{
		file.seekg(idx * sizeof(Point));
		file.read((char*)(&p), sizeof(Point));
		retVal = IFile::Error(SUCCESS);
	}

	return retVal;
}
