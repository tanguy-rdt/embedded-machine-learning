#include <iostream>

#include "audio_preprocessing.h"
#include "fft_utils.h"

#ifdef DEBUG
#include "plot.h"
#endif

AudioPreprocessing auPreprocessing;

int main(){
    // ------
    // Part 1: read audio file
    auPreprocessing.readAudioFile("./resources/blues.00000.au");
    const AudioPreprocessing::AuHeader auHeader = auPreprocessing.getAuHeader();
    const AudioPreprocessing::AuData auData = auPreprocessing.getAuData();

    #ifdef DEBUG
    std::cout << "Magic number: " << auHeader.magicNumber << std::endl;
    std::cout << "Data shift: " << auHeader.dataShift << std::endl;
    std::cout << "Data size: " << auHeader.dataSize << std::endl;
    std::cout << "Encoding: " << auHeader.encoding << std::endl;
    std::cout << "Sample rate: " << auHeader.fs << std::endl;
    std::cout << "Canal number: " << auHeader.nbCanal << std::endl;
    std::cout << "Sample number: " << auData.nbSample << std::endl;
    #endif

    #ifdef DEBUG
    timePlot(auData.samples, auHeader.fs, "audio");
    #endif

    // ------
    // Part 2: Extract descriptor
    auPreprocessing.extractDescriptor(auData.samples);
    const AudioPreprocessing::AuDescriptor auDescriptor = auPreprocessing.getAuDescriptor();
    
    #ifdef DEBUG
    descriptorPlot(auDescriptor.mu, auDescriptor.sigma, auHeader.fs, "Spectrogramme et descripteurs");
    #endif

    return 0;
}