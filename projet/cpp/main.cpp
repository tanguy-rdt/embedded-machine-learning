#include <iostream>
#include <string>

#include "audio_preprocessing.h"
#include "predictor.h"


void createDataset(std::string audioPath, std::string outputPath, std::string audioType){
    AudioPreprocessing auPreprocessing;

    auPreprocessing.setCsvPath(outputPath.c_str());
    auPreprocessing.setAudioType(audioType.c_str());
    auPreprocessing.readAudioFile(audioPath.c_str());
    const AudioPreprocessing::AuData auData = auPreprocessing.getAuData();
    auPreprocessing.extractDescriptor(auData.samples);
}

void predict(std::string datasetPath, std::string model_name, std::string scaler_path) {
    Predictor predictor;

    predictor.predict(datasetPath.c_str(), model_name.c_str(), scaler_path.c_str());
    std::cout << "Average: " << predictor.getLastAverage() << std::endl;
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
        if (argc != 5) {
            std::cerr << "Usage: " << argv[0] << " predict <dataset> <model_name> <scaler_path>\n";
            return 1;
        }
        std::string datasetPath = argv[2];
        std::string modelName = argv[3];
        std::string scalerPath = argv[4];
        predict(datasetPath, modelName, scalerPath);
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