#include "BinaryFile.h"

// Konstruktor klasy BinaryFile - otwiera plik binarny w okreœlonym trybie
BinaryFile::BinaryFile(const std::string filePath, const std::string mode) : filePath(filePath), length(0)
{
    // Domyœlny tryb to plik binarny
    openMode = std::fstream::binary;

    // Sprawdzamy przekazany tryb i ustawiamy odpowiednie flagi:
    if (mode.find("r") != std::string::npos) openMode |= std::fstream::in;     // tryb czytania
    if (mode.find("w") != std::string::npos) openMode |= std::fstream::out;    // tryb zapisu
    if (mode.find("a") != std::string::npos) openMode |= std::fstream::app;    // tryb dopisywania
    if (mode.find("t") != std::string::npos) openMode |= std::fstream::trunc;  // wyczyœæ plik przy otwarciu
    if (mode.find("e") != std::string::npos) openMode |= std::fstream::ate;    // przejdŸ na koniec pliku

    // Otwieramy plik z ustawionymi flagami
    file.open(filePath, openMode);

    // Jeœli plik zosta³ otwarty, obliczamy jego d³ugoœæ
    if (file.is_open()) {
        file.seekg(0, std::fstream::end);  // przejdŸ na koniec pliku
        length = file.tellg();             // pobierz pozycjê (d³ugoœæ pliku)
        file.seekg(0, std::fstream::beg);  // wróæ na pocz¹tek pliku
    }
}

// Destruktor - zamyka plik
BinaryFile::~BinaryFile()
{
    file.close();
}

// Zapisuje wektor punktów do pliku
FileError BinaryFile::Write(const std::vector<Point>& v)
{
    FileError retVal = FileError(ACCESS_DENIED);  // domyœlny b³¹d: brak dostêpu

    if (!file.is_open())  // jeœli plik nie jest otwarty
    {
        retVal = FileError(FILE_INVALID);  // zwróæ b³¹d: nieprawid³owy plik
    }
    else if (openMode & std::fstream::out)  // jeœli tryb zapisu jest aktywny
    {
        // zapisujemy dane binarne (ca³y wektor na raz)
        file.write((const char*)v.data(), v.size() * sizeof(Point));
        retVal = FileError(SUCCESS);  // zwróæ sukces
    }

    return retVal;  // zwróæ status operacji
}

// Odczytuje ca³¹ zawartoœæ pliku do wektora punktów
FileError BinaryFile::Read(std::vector<Point>& v)
{
    FileError retVal = FileError(ACCESS_DENIED);  // domyœlny b³¹d: brak dostêpu

    if (!file.is_open())  // jeœli plik nie jest otwarty
    {
        retVal = FileError(FILE_INVALID);  // b³¹d: nieprawid³owy plik
    }
    else if (openMode & std::fstream::in)  // jeœli tryb czytania jest aktywny
    {
        v.clear();  // wyczyœæ wektor
        v.resize(length / sizeof(Point));  // zmieñ rozmiar wektora na odpowiedni¹ liczbê punktów
        file.seekg(0, std::fstream::beg);  // przejdŸ na pocz¹tek pliku
        file.read((char*)v.data(), length);  // wczytaj ca³¹ zawartoœæ pliku
        retVal = FileError(SUCCESS);  // zwróæ sukces
    }

    return retVal;  // zwróæ status operacji
}

// Odczytuje pojedynczy punkt z pliku na okreœlonej pozycji
FileError BinaryFile::Read(Point& p, const unsigned long idx)
{
    FileError retVal = FileError(ACCESS_DENIED);  // domyœlny b³¹d: brak dostêpu

    if (!file.is_open())  // jeœli plik nie jest otwarty
    {
        retVal = FileError(FILE_INVALID);  // b³¹d: nieprawid³owy plik
    }
    else if (idx >= length / sizeof(Point))  // jeœli indeks wykracza poza rozmiar pliku
    {
        retVal = FileError(OUT_OF_BOUNDS);  // b³¹d: poza zakresem
    }
    else if (openMode & std::fstream::in)  // jeœli tryb czytania jest aktywny
    {
        file.seekg(idx * sizeof(Point));  // przejdŸ do odpowiedniej pozycji w pliku
        file.read((char*)(&p), sizeof(Point));  // wczytaj punkt
        retVal = FileError(SUCCESS);  // zwróæ sukces
    }

    return retVal;  // zwróæ status operacji
}