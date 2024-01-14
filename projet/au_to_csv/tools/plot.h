#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

template<typename T>
void timePlot(const std::vector<T> data, const int fs, const char* title){
    std::vector<double> time(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        time[i] = static_cast<double>(i) / fs;
    }

    plt::plot(time, data);
    plt::xlabel("Time (s)");
    plt::ylabel("Amplitude");
    plt::title(title);
    plt::grid(true);
    plt::show();
}

template<typename T>
void descriptorPlot(const std::vector<T> mu, const std::vector<T> sigma, const int fs, const char* title){
    if ((mu.size() != FFT_SIZE * FFT_NUMBER) && (sigma.size() != FFT_SIZE * FFT_NUMBER)) {
        std::cerr << "Erreur : La taille des données ne correspond pas à FFT_SIZE * FFT_NUMBER" << std::endl;
    }

    std::vector<double> meanMuFFT(FFT_SIZE, 0.0);
    for (int i = 0; i < FFT_NUMBER; ++i) {
        for (int j = 0; j < FFT_SIZE; ++j) {
            meanMuFFT[j] += mu[i * FFT_SIZE + j] / FFT_NUMBER;
        }
    }
    std::rotate(meanMuFFT.begin(), meanMuFFT.begin() + meanMuFFT.size() / 2, meanMuFFT.end());

    std::vector<double> meanSigmaFFT(FFT_SIZE, 0.0);
    for (int i = 0; i < FFT_NUMBER; ++i) {
        for (int j = 0; j < FFT_SIZE; ++j) {
            meanSigmaFFT[j] += sigma[i * FFT_SIZE + j] / FFT_NUMBER;
        }
    }
    std::rotate(meanSigmaFFT.begin(), meanSigmaFFT.begin() + meanSigmaFFT.size() / 2, meanSigmaFFT.end());

    std::vector<double> freqs(FFT_SIZE);
    for (int i = 0; i < FFT_SIZE; ++i) {
        freqs[i] = (i - FFT_SIZE / 2) * fs / FFT_SIZE / 1000.0; 
    }

    plt::figure_size(1200, 600);

    plt::suptitle(title);
    plt::subplot(1, 2, 1);
    plt::plot(freqs, meanMuFFT);
    plt::xlabel("Time (s)");
    plt::ylabel("Amplitude");
    plt::title("Moyenne temporelle du spectrogramme");
    plt::grid(true);

    plt::subplot(1, 2, 2);
    plt::plot(freqs, meanSigmaFFT);
    plt::xlabel("Time (s)");
    plt::ylabel("Amplitude");
    plt::title("Ecart-type temporel du spectrogramme");
    plt::grid(true);

    plt::show();
}

template<typename T>
void frequencyPlot(const std::vector<T> fft, const int fs){
    if (fft.size() != FFT_SIZE * FFT_NUMBER) {
        std::cerr << "Erreur : La taille des données ne correspond pas à FFT_SIZE * FFT_NUMBER" << std::endl;
    }

    std::vector<double> meanFFT(FFT_SIZE, 0.0);
    for (int i = 0; i < FFT_NUMBER; ++i) {
        for (int j = 0; j < FFT_SIZE; ++j) {
            meanFFT[j] += fft[i * FFT_SIZE + j] / FFT_NUMBER;
        }
    }
    std::rotate(meanFFT.begin(), meanFFT.begin() + meanFFT.size() / 2, meanFFT.end());

    std::vector<double> freqs(FFT_SIZE);
    for (int i = 0; i < FFT_SIZE; ++i) {
        freqs[i] = (i - FFT_SIZE / 2) * fs / FFT_SIZE / 1000.0; 
    }

    plt::figure_size(1200, 600);

    plt::plot(freqs, meanFFT);
    plt::xlabel("freq");
    plt::ylabel("Amplitude");
    plt::title("FFT");
    plt::grid(true);

    plt::show();
}



void spectrogramme(){

}

#endif