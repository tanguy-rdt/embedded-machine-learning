#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>

#include "au_utils.cpp"
#include "fft_utils.cpp"
#include "src/constants.h"

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
    int nSample = 0;
    std::vector<int> vSample;


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

    int sample = readSample(file);
    csvFile << sample;

    while (!file.eof()) {
        int sample = readSample(file);
        if (!file.eof()){
            csvFile << ", ";
            csvFile << sample;
            vSample.push_back(sample);
            nSample++;
        }
    }

    std::cout << nSample << std::endl;

    file.close();
    csvFile.close();


    std::vector<Complex> fft(FFT_SIZE);

    int n = 0;
    for(int i = 0; i < vSample.size(); i += FFT_SIZE){
        fft[n] = vSample[i];
        n++;
    }
    ite_dit_fft(fft);

    std::ofstream fftCsvFile("./fft.csv");
    for(int i = 0; i < fft.size(); i++){
        fftCsvFile << fft[i].real();
        fftCsvFile << "\n";
    }

    std::ofstream muCsvFile("./mu.csv");

    double magnitude_tot = 0.0;
    std::vector<double> mu;
    std::vector<double> var;
    for (int i = 0; i < fft.size(); i++) {
        double magnitude = std::norm(fft[i]);

        magnitude_tot += magnitude;
        mu.push_back(magnitude_tot/i);
        muCsvFile << magnitude_tot/i;
        muCsvFile << "\n";
    }

    return 0;
}