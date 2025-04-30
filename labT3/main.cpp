#include <iostream>
//#include "BinaryFile.h"
#include "Point.h"
#include "IFile.h"
#include "FileFactory.h"

int main()
{
	const std::string nazwaPliku = "c:\\temp\\point1.csv";

	// Przykladowa lista
	std::vector<Point> lista;
	lista.push_back(Point(1, 2, 8));
	lista.push_back(Point(3, 1, 3));

	// Zapis listy do pliku
	IFile* plikDoZapisu = FileFactory::Open(nazwaPliku, "w");
	plikDoZapisu->Write(lista);
	delete plikDoZapisu;

	// Testowy odczyt pliku
	std::vector<Point> odczytanaLista;

	IFile* plikDoOdczytu = FileFactory::Open(nazwaPliku, "r");
	IFile::Error status = plikDoOdczytu->Read(odczytanaLista);
	delete plikDoOdczytu;

	if (status == IFile::Error::SUCCESS)
	{
		for (int i = 0; i < odczytanaLista.size(); i++)
		{
			Point p = odczytanaLista.at(i);
			std::cout << i << " - x:" << p.x << ", y:" << p.y << ", z:" << p.z << std::endl;
		}
	}
	else
	{
		std::cout << "Wystapil blad odczytu: " << status;
	}

	return 0;


	//BinaryFile *plikBinarny = new BinaryFile("c:\\temp\\point.bin", "w");
	//plikBinarny->Write(lista);
	//delete plikBinarny;

	//BinaryFile *plikOdczytany = new BinaryFile("c:\\temp\\point.bin", "r");
	//std::vector<Point> listaOdczyt;
	//
	//if (plikOdczytany->Read(listaOdczyt) == FileError(SUCCESS))
	//{
	//	for (int i = 0; i < listaOdczyt.size(); i++)
	//	{
	//		Point p = listaOdczyt.at(i);
	//		std::cout << "x:" << p.x << ", y:" << p.y << ", z:" << p.z;
	//	}

	//};

	//delete plikOdczytany;

	//return 0;
}