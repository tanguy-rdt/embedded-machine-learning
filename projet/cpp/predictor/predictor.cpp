#include "predictor.h"
#include "DecisionTreeClassifier.h"
#include "RandomForestClassifier.h"
#include "LinearSVC.h"

Predictor::Predictor() {
}

Predictor::~Predictor() {
}

void Predictor::predict(const char* datasetPath, const char* model_name, const char* scaler_path){
    const char* label[10] = {"blues", "classical", "country", "disco", "hiphop", "jazz", "metal", "pop", "reggae", "rock"};
    std::vector<std::vector<float>> descriptors;
    std::vector<std::string> labels;
    loadDataset(datasetPath, descriptors, labels);

    std::vector<float> mean, scale;
    loadScalerParams(scaler_path, mean, scale);
    normalizeData(descriptors, mean, scale);


    _predictions.clear();
    std::vector<int>().swap(_predictions);
    _nbGoodPrediction = 0;
    for (int i = 0; i < descriptors.size(); i++){
        if (!strcmp(model_name, "random_forest")) {
            randomForestPredict(descriptors[i].data(), descriptors[i].size());
        }
        else if (!strcmp(model_name, "decision_tree")) {
            decisionTreePredict(descriptors[i].data(), descriptors[i].size());
        }
        else if (!strcmp(model_name, "linear_svc")) {
            linearSVCPredict(descriptors[i].data(), descriptors[i].size(), 10);
        }

        if (label[_lastPrediction] == labels[i]) {
            _nbGoodPrediction++;
        }
    }

    _lastAverage = static_cast<float>(_nbGoodPrediction)/descriptors.size();
}

void Predictor::randomForestPredict(const float *features, int32_t features_length) {
    _lastPrediction = RandomForestClassifier_predict(features, features_length);
    _predictions.push_back(_lastPrediction);
}

void Predictor::decisionTreePredict(const float *features, int32_t features_length){
    _lastPrediction = DecisionTreeClassifier_predict(features, features_length);
    _predictions.push_back(_lastPrediction);
}

void Predictor::linearSVCPredict(const float *features, int features_length, int nbCls){
    int bestClass = -1;
    float bestScore = 0.0f;

    for (size_t i = 0; i < nbCls; ++i) {
        float score = 0.0f;
        for (size_t j = 0; j < features_length; ++j) {
            score += features[j] * svc_model_coefficients[i][j];
        }
        score += svc_model_intercepts[i];

        if (score > bestScore) {
            bestScore = score;
            bestClass = i;
        }
    }

    _lastPrediction = bestClass;
    _predictions.push_back(_lastPrediction);
}

void Predictor::loadDataset(const std::string& path, std::vector<std::vector<float>>& descriptors, std::vector<std::string>& labels) {
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

void Predictor::loadScalerParams(const std::string& path, std::vector<float>& mean, std::vector<float>& scale) {
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

void Predictor::normalizeData(std::vector<std::vector<float>>& data, const std::vector<float>& mean, const std::vector<float>& scale) {
    for (auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            row[i] = (row[i] - mean[i]) / scale[i];
        }
    }
}


int Predictor::getLastPrediction(){
    return _lastPrediction;
}

std::vector<int> Predictor::getPrediction(){
    return _predictions;
}


int Predictor::getNbGoodPrediction(){
    return _nbGoodPrediction;
}

float Predictor::getLastAverage(){
    return _lastAverage;
}

