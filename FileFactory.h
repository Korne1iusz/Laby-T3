#include "IFile.h"
#include "BinaryFile.h"
#include "CsvFile.h"

class FileFactory
{
public:
static IFile* OpenFile(std::string,std::string);
};