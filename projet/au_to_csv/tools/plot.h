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
void descriptorPlot(const std::vector<T> &mu, const std::vector<T> &sigma, const int fs, const char* title) {
    if (mu.size() != FFT_SIZE || sigma.size() != FFT_SIZE) {
        std::cerr << "Erreur : La taille des données ne correspond pas à FFT_SIZE" << std::endl;
        return;
    }

    // Création des copies locales pour appliquer le FFT shift
    std::vector<T> shifted_mu = mu;
    std::vector<T> shifted_sigma = sigma;

    // Application du FFT shift
    std::rotate(shifted_mu.begin(), shifted_mu.begin() + shifted_mu.size() / 2, shifted_mu.end());
    std::rotate(shifted_sigma.begin(), shifted_sigma.begin() + shifted_sigma.size() / 2, shifted_sigma.end());

    // Calcul des fréquences pour l'affichage avec fréquence zéro au centre
    std::vector<double> freqs(FFT_SIZE);
    for (int i = 0; i < FFT_SIZE; ++i) {
        freqs[i] = ((i + FFT_SIZE / 2) % FFT_SIZE - FFT_SIZE / 2) * static_cast<double>(fs) / FFT_SIZE / 1000.0;
    }

    plt::figure_size(1200, 600);

    plt::suptitle(title);
    plt::subplot(1, 2, 1);
    plt::plot(freqs, shifted_mu);
    plt::xlabel("Fréquence (kHz)");
    plt::ylabel("Amplitude");
    plt::title("Moyenne temporelle du spectrogramme");
    plt::grid(true);

    plt::subplot(1, 2, 2);
    plt::plot(freqs, shifted_sigma);
    plt::xlabel("Fréquence (kHz)");
    plt::ylabel("Amplitude");
    plt::title("Ecart-type temporel du spectrogramme");
    plt::grid(true);

    plt::show();
}



#endif