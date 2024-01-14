#ifndef AUDIO_PREPROCESSING_H
#define AUDIO_PREPROCESSING_H

#include <iostream>
#include <vector>
#include <cstdio>
#include <fstream>
#include <complex>

#include "au_utils.h"
#include "fft_utils.h"
#include "constants.h"
#include "matplotlibcpp.h"


class AudioPreprocessing {
public:
    struct AuHeader{
        int magicNumber = 0;
        int dataShift = 0;
        int dataSize = 0;
        int encoding = 0;
        int fs = 0;
        int nbCanal = 0;
    };

    struct AuData{
        int nbSample = 0;
        std::vector<double> samples;
    };

    struct AuDescriptor{
        std::vector<double> sigma;
        std::vector<double> mu;

        AuDescriptor() : sigma(MAX_SAMPLE, 0.0), mu(MAX_SAMPLE, 0.0) {}
    };

    struct FFT{
        std::vector<double> fft;

        FFT() : fft(FFT_SIZE * FFT_NUMBER,0) {}
    };

    AudioPreprocessing();
    ~AudioPreprocessing();

    int readAudioFile(const char* path);
    void extractDescriptor(std::vector<double> normalized_data);
    const AuHeader& getAuHeader() const;
    const AuData& getAuData() const;
    const AuDescriptor& getAuDescriptor() const;
    const FFT& getFFT() const;

private:
    AuHeader _auHeader;
    AuData _auData;
    AuDescriptor _auDescriptor;
    FFT _fft;

    void normalizeData();
};

#endif
