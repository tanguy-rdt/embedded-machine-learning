#include <iostream>
#include <string>

#include "audio_preprocessing.h"
#include "fft_utils.h"

#ifdef DEBUG
#include "plot.h"
#endif

AudioPreprocessing auPreprocessing;

int main(int argc, char *argv[]){
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <audio file path>" << std::endl;
        return 1;
    }

    const std::string filePath = argv[1];

    size_t lastSlashIndex = filePath.find_last_of("/");
    std::string fileNameWithExtension = filePath.substr(lastSlashIndex + 1);
    size_t typeSlashIndex = filePath.find_last_of("/", lastSlashIndex - 1);
    std::string fileType = filePath.substr(typeSlashIndex + 1, lastSlashIndex - typeSlashIndex - 1);
    size_t lastDotIndex = fileNameWithExtension.find_last_of(".");
    std::string fileName = fileNameWithExtension.substr(0, lastDotIndex);


    char csvPath[1024];
    sprintf(csvPath, "csv_files/%s/%s", fileType.c_str(), fileName.c_str());
    auPreprocessing.setCsvPath(csvPath);

    // ------
    // Part 1: read audio file
    auPreprocessing.readAudioFile(filePath.c_str());
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