#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "model_c/RandomForestClassifier.h"
#include "model_c/DecisionTreeClassifier.h"


void load_dataset(const std::string& path, std::vector<std::vector<float>>& descriptors, std::vector<std::string>& labels) {
    std::ifstream file(path);
    if (file.fail()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier '" << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<float> descriptor;
        float value;
        for (int i = 0; i < 1024; ++i) {
            if (!(ss >> value)) {
                std::cerr << "Erreur de lecture de valeur." << std::endl;
                break;
            }
            descriptor.push_back(value);
            if (ss.peek() == ',') ss.ignore();
        }

        std::string label;
        if (ss >> label) {
            size_t pos = label.find(".");
            if (pos != std::string::npos) {
                label = label.substr(0, pos);
            }
            labels.push_back(label);
        }
        descriptors.push_back(descriptor);
    }
}

void load_scaler_params(const std::string& path, std::vector<float>& mean, std::vector<float>& scale) {
    std::ifstream file(path);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << path << std::endl;
        exit(EXIT_FAILURE);
    }

    while (getline(file, line)) {
        std::stringstream ss(line);
        float mean_value, scale_value;
        if (ss >> mean_value >> scale_value) {
            mean.push_back(mean_value);
            scale.push_back(scale_value);
        }
    }
}

void normalize_data(std::vector<std::vector<float>>& data, const std::vector<float>& mean, const std::vector<float>& scale) {
    for (auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            row[i] = (row[i] - mean[i]) / scale[i];
        }
    }
}

int main() {
    const char* label[10] = {"blues", "classical", "country", "disco", "hiphop", "jazz", "metal", "pop", "reggae", "rock"};
    const std::string path = "../csv_files/dataset_test.csv";
    std::vector<std::vector<float>> descriptors;
    std::vector<std::string> labels;
    load_dataset(path, descriptors, labels);

    std::vector<float> mean, scale;
    load_scaler_params("../resources/scaler.txt", mean, scale);
    normalize_data(descriptors, mean, scale);

    float cpt = .0;
    for (int i=0; i < descriptors.size(); i++){
        int32_t prediction1 = RandomForestClassifier_predict(descriptors[i].data(), descriptors[i].size());
        int32_t prediction2 = DecisionTreeClassifier_predict(descriptors[i].data(), descriptors[i].size());

        if (labels[i] == label[prediction1]) {
            cpt++;
        }
    }

    std::cout << cpt/descriptors.size() << std::endl;

    return 0;
}
