#include "CsvFile.h"

/*CsvFile::CsvFile(const std::string filePath, const std::string mode) : filePath(filePath), length(0)
{

	if (mode.find("r") != std::string::npos) openMode |= std::fstream::in;
	if (mode.find("w") != std::string::npos) openMode |= std::fstream::out;
	if (mode.find("a") != std::string::npos) openMode |= std::fstream::app;
	if (mode.find("t") != std::string::npos) openMode |= std::fstream::trunc;
	if (mode.find("e") != std::string::npos) openMode |= std::fstream::ate;

	file.open(filePath, openMode);
	if (file.is_open()) {
		file.seekg(0, std::fstream::end);
		length = file.tellg();
		file.seekg(0, std::fstream::beg);
	}
}

CsvFile::~CsvFile()
{
	file.close();
}*/
CsvFile::CsvFile(const std::string filePath, const std::string mode) : IFile(filePath,mode){}

FileError CsvFile::Write(const std::vector<Point>&v){
    FileError retVal(ACCESS_DENIED);
    
	if (!file.is_open())
	{
		retVal = FileError(FILE_INVALID);
	}
	else if (openMode & std::fstream::out){
        std::string string=VectorToString(v);
        string.pop_back();  //usuwa ostatni \n zeby plik nie konczyl sie pusta linia
        file<<string;
        retVal=SUCCESS;
    }
    return retVal;
}

std::string CsvFile::PointToString(Point pkt){
    std::string wynik;
    wynik.clear();
    wynik.append(std::to_string(pkt.x));
    wynik.append(",");
    wynik.append(std::to_string(pkt.y));
    wynik.append(",");
    wynik.append(std::to_string(pkt.z));
    wynik.append("\n");
    return wynik;
}

    std::string CsvFile::VectorToString(std::vector<Point> wektor){
        int i;
        std::string wynik;
        for (i=0;i<wektor.size();i++){
            wynik.append(PointToString(wektor.at(i)));
        }
        return wynik;
    }

    FileError CsvFile::Read(std::vector<Point>&v){
    FileError retVal = FileError(ACCESS_DENIED);

	if (!file.is_open()){
		retVal = FileError(FILE_INVALID);
	}
	else if (openMode & std::fstream::in){
		v.clear();
		//v.resize(length / sizeof(Point));
		file.seekg(0, std::fstream::beg);
        std::vector<std::string> Vstring;
        std::string ZawartoscPliku;
        while(file){
        file>>ZawartoscPliku;
        Vstring=Split(ZawartoscPliku,',');
        v.push_back(VstringtoPoint(Vstring));
    }
		retVal = FileError(SUCCESS);
	}

	return retVal;

    }
    
	std::vector<std::string> CsvFile::Split(std::string string, char a){
        std::vector<std::string> wynik;
        std::string AktualnaWartosc;
        std::stringstream ss (string);
        while(std::getline(ss,AktualnaWartosc,a)){
            wynik.push_back(AktualnaWartosc);
        }
        return wynik;
    }
	Point CsvFile::VstringtoPoint(std::vector<std::string> Vstring){
        int i;
        Point wynik;
        wynik.x=stod(Vstring.at(0));
        wynik.y=stod(Vstring.at(1));
        wynik.z=stod(Vstring.at(2));
        return wynik;
   }

   /* FileError CsvFile::Read(Point& p, const unsigned long idx){
        FileError retVal = FileError(ACCESS_DENIED);

    	if (!file.is_open())
	    {
		retVal = FileError(FILE_INVALID);
	}
	else if (idx >= length / sizeof(Point))
	{
		retVal = FileError(OUT_OF_BOUNDS);
	}
	//else if (openMode & std::fstream::in)}*/
    // tego nie zrobilem