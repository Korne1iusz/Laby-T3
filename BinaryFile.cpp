#include "BinaryFile.h"

BinaryFile::BinaryFile(const std::string filePath, const std::string mode) : IFile(filePath,mode+"b"){}

FileError BinaryFile::Write(const std::vector<Point>& v)
{
	FileError retVal = FileError(ACCESS_DENIED);

	if (!file.is_open())
	{
		retVal = FileError(FILE_INVALID);
	}
	else if (openMode & std::fstream::out)
	{
		file.write((const char *)v.data(), v.size() * sizeof(Point));
		retVal = FileError(SUCCESS);
	}

	return retVal;
}

FileError BinaryFile::Read(std::vector<Point>& v)
{
	FileError retVal = FileError(ACCESS_DENIED);

	if (!file.is_open())
	{
		retVal = FileError(FILE_INVALID);
	}
	else if (openMode & std::fstream::in)
	{
		v.clear();
		v.resize(length / sizeof(Point));
		file.seekg(0, std::fstream::beg);
		file.read((char *)v.data(), length);
		retVal = FileError(SUCCESS);
	}

	return retVal;
}

FileError BinaryFile::Read(Point & p, const unsigned long idx)
{
	FileError retVal = FileError(ACCESS_DENIED);

	if (!file.is_open())
	{
		retVal = FileError(FILE_INVALID);
	}
	else if (idx >= length / sizeof(Point))
	{
		retVal = FileError(OUT_OF_BOUNDS);
	}
	else if (openMode & std::fstream::in)
	{
		file.seekg(idx * sizeof(Point));
		file.read((char*)(&p), sizeof(Point));
		retVal = FileError(SUCCESS);
	}

	return retVal;
}
