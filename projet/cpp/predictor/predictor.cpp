#include "predictor.h"
#include "common.h"
#include "DecisionTreeClassifier.h"
#include "RandomForestClassifier.h"

Predictor::Predictor() {
}

Predictor::~Predictor() {
}

void Predictor::predict(const char* datasetPath, const char* model_name, const char* scaler_path){
    const char* label[10] = {"blues", "classical", "country", "disco", "hiphop", "jazz", "metal", "pop", "reggae", "rock"};
    std::vector<std::vector<float>> descriptors;
    std::vector<std::string> labels;
    load_dataset(datasetPath, descriptors, labels);

    std::vector<float> mean, scale;
    load_scaler_params(scaler_path, mean, scale);
    normalize_data(descriptors, mean, scale);


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
            linearSVCPredict(descriptors[i].data(), descriptors[i].size());
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

void Predictor::linearSVCPredict(const float *features, int features_length){
    std::vector<std::vector<float>> parameters;
    std::vector<float> bias;

    loadLinearSVCParameters(parameters, bias);

    int bestClass = -1;
    float bestScore = 0.0f;

    for (size_t i = 0; i < parameters.size(); ++i) {
        float score = 0.0f;
        for (size_t j = 0; j < features_length; ++j) {
            score += features[j] * parameters[i][j];
        }
        score += bias[i];

        if (score > bestScore) {
            bestScore = score;
            bestClass = i;
        }
    }

    _lastPrediction = bestClass;
    _predictions.push_back(_lastPrediction);
}

void Predictor::loadLinearSVCParameters(std::vector<std::vector<float>>& parameters, std::vector<float>& bias) {
    std::ifstream file("cpp/model/LinearSVC.txt");
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<float> currentModelParameters;
    while (getline(file, line)) {
        if (line.empty()) { 
            if (!currentModelParameters.empty()) {
                bias.push_back(currentModelParameters.back());
                currentModelParameters.pop_back();
                parameters.push_back(currentModelParameters);
                currentModelParameters.clear();
            }
        } 
        else {
            std::stringstream ss(line);
            float param;

            if (ss >> param) {
                currentModelParameters.push_back(param);
            }
        }
    }

    if (!currentModelParameters.empty()) {
        parameters.push_back(currentModelParameters);
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

