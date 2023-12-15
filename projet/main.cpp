#include <iostream>
#include <fstream>

#include "au_utils.cpp"

int main(){
    std::ifstream file("./blues.00000.au", std::ios::binary);
    if (!file) {
        std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
        return -1;
    }

    int magicNumber = read32Bits(file);
    int dataShift = read32Bits(file);
    int dataSize = read32Bits(file);
    int encoding = read32Bits(file);
    int fs = read32Bits(file);
    int nbCanal = read32Bits(file);


    std::cout << "Nombre magique: " << magicNumber << std::endl;
    std::cout << "Décalage de données: " << dataShift << std::endl;
    std::cout << "Taille de données " << dataSize << std::endl;
    std::cout << "Encodage: " << encoding << std::endl;
    std::cout << "Fréquence d'échantillonage: " << fs << std::endl;
    std::cout << "Nonmbre de canaux: " << nbCanal << std::endl;

    file.seekg(dataShift, std::ios::beg);

    std::ofstream csvFile("./signal.csv");
    if (!csvFile) {
        std::cerr << "Impossible d'ouvrir le fichier CSV" << std::endl;
        file.close();
        return -1;
    }

    int n = 0;

    int sample = readSample(file);
    csvFile << sample;

    while (!file.eof()) {
        csvFile << ", ";
        int sample = readSample(file);
        csvFile << sample;
        n++;
    }

    std::cout << n << std::endl;


    file.close();
    csvFile.close();

    return 0;
}