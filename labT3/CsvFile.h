#include <fstream>
#include <vector>
#include "Point.h"
#include "IFile.h"

class CsvFile : public IFile
{
private:
	std::vector<std::string> Split(std::string, char);
	
public:
	CsvFile(const std::string, const std::string);

	Error Write(const std::vector<Point>&) override;
	Error Read(std::vector<Point>&) override;
	Error Read(Point&, const unsigned long) override;
};

