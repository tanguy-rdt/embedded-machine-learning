#include <iostream>
#include <ostream>
#include <string>

#include "audio_preprocessing.h"
#include "predictor.h"

#ifdef DEBUG
#include "plot.h"
#endif

void createDataset(std::string audioPath, std::string outputPath, std::string audioType){
    AudioPreprocessing auPreprocessing;

    auPreprocessing.setCsvPath(outputPath.c_str());
    auPreprocessing.setAudioType(audioType.c_str());

    // ------
    // Part 1: read audio file
    auPreprocessing.readAudioFile(audioPath.c_str());
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
}

void predict(std::string datasetPath, std::string scalerPath, std::vector<std::string> modelName) {
    Predictor predictor;

    for(const auto& model: modelName){
        predictor.predict(datasetPath.c_str(), model.c_str(), scalerPath.c_str());
        std::cout <<  model << std::endl;
        std::cout << "\tAverage: " << predictor.getLastAverage() << std::endl;
        std::cout << "\tRatio: " << predictor.getNbGoodPrediction() << "/" << predictor.getPrediction().size() << std::endl;
        std::cout << "\tExec time: " << predictor.getLastExecTimeMs() << "ms" << "\n" << std::endl;
    }    
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command> [options]\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "create_dataset") {
        if (argc != 5) {
            std::cerr << "Usage: " << argv[0] << " create_dataset <audio_path> <output_path> <audio_type>\n";
            return 1;
        }
        std::string audioPath = argv[2];
        std::string outputPath = argv[3];
        std::string audioType = argv[4];
        createDataset(audioPath, outputPath, audioType);
    } else if (command == "predict") {
        if (argc < 5) {
            std::cerr << "Usage: " << argv[0] << " predict <dataset> <scaler_path> <model_name>\n";
            return 1;
        }

        std::string datasetPath = argv[2];
        std::string scalerPath = argv[3];
        std::vector<std::string> modelName;

        for (int i = 4; i < argc; i++){
            modelName.push_back(argv[i]);  
        }

        predict(datasetPath, scalerPath, modelName);
    } else if (command == "train") {
        if (argc != 4) {
            std::cerr << "Usage: " << argv[0] << " train <dataset> <estimator>\n";
            return 1;
        }
        std::string dataset = argv[2];
        std::string estimator = argv[3];
    } else {
        std::cerr << "Unknown command: " << command << "\n";
        return 1;
    }

    return 0;
}