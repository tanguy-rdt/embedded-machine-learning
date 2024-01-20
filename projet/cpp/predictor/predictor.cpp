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


    _nbPrediction = 0;
    for (int i = 0; i < descriptors.size(); i++){
        randomForestPredict(descriptors[i].data(), descriptors[i].size());
        if (model_name == "random_forest") {
            std::cout << model_name << std::endl;
            randomForestPredict(descriptors[i].data(), descriptors[i].size());
        }
        else if (model_name == "decision_tree") {
            decisionTreePredict(descriptors[i].data(), descriptors[i].size());
        }

        if (label[_lastPrediction] == labels[i]) {
            _nbPrediction++;
        }
    }

    _lastAverage = static_cast<float>(_nbPrediction)/descriptors.size();
}

void Predictor::randomForestPredict(const float *features, int32_t features_length) {
    _lastPrediction = RandomForestClassifier_predict(features, features_length);
}

void Predictor::decisionTreePredict(const float *features, int32_t features_length){
    _lastPrediction = DecisionTreeClassifier_predict(features, features_length);
}


int Predictor::getLastPrediction(){}
std::vector<int> Predictor::getPrediction(){}


int Predictor::getNbPrediction(){

}

float Predictor::getLastAverage(){
    return _lastAverage;
}

