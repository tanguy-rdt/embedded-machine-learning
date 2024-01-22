#include "predictor.h"
#include "DecisionTreeClassifier.h"
#include "RandomForestClassifier.h"
#include "LinearSVC.h"
#include <ctime>

Predictor::Predictor() {
}

Predictor::~Predictor() {
}

void Predictor::predict(const char* datasetPath, const char* model_name, const char* scaler_path){
    std::vector<std::vector<float>> descriptors;
    std::vector<std::string> labels;
    loadDataset(datasetPath, descriptors, labels);

    std::vector<float> mean, scale;
    loadScalerParams(scaler_path, mean, scale);
    normalizeData(descriptors, mean, scale);


    _predictions.clear();
    std::vector<int>().swap(_predictions);
    _nbGoodPrediction = 0;

    if (!strcmp(model_name, "random_forest")) {
        randomForestPredict(descriptors, labels);
    }
    else if (!strcmp(model_name, "decision_tree")) {
        decisionTreePredict(descriptors, labels);
    }
    else if (!strcmp(model_name, "linear_svc")) {
        linearSVCPredict(descriptors, labels);
    }
    else if (!strcmp(model_name, "neural_network")) {
        #ifdef COMPILE_FOR_RPI
        neuralNetworkPredict(descriptors, labels);
        #else
        std::cout << "ERROR: To use the neural network model you need to be on the target" << std::endl;
        #endif
    }

    _lastAverage = static_cast<float>(_nbGoodPrediction)/descriptors.size();
}

void Predictor::randomForestPredict(std::vector<std::vector<float>>& features, std::vector<std::string>& labels) {
    _begin = clock();
    for (int i = 0; i < features.size(); i++){
        _lastPrediction = RandomForestClassifier_predict(features[i].data(), features[i].size());
        _predictions.push_back(_lastPrediction);
        if (_lastPrediction == std::stoi(labels[i])) {
            _nbGoodPrediction++;
        }
    }
    _end = clock();
}

void Predictor::decisionTreePredict(std::vector<std::vector<float>>& features, std::vector<std::string>& labels){
    _begin = clock();
    for (int i = 0; i < features.size(); i++){
        _lastPrediction = DecisionTreeClassifier_predict(features[i].data(), features[i].size());
        _predictions.push_back(_lastPrediction);
        if (_lastPrediction == std::stoi(labels[i])) {
            _nbGoodPrediction++;
        }
    }
    _end = clock();
}

void Predictor::linearSVCPredict(std::vector<std::vector<float>>& features, std::vector<std::string>& labels){
    _begin = clock();
    for (int i = 0; i < features.size(); i++){
        int bestClass = -1;
        float bestScore = 0.0f;

        for (size_t cls = 0; cls < 10; ++cls) {
            float score = 0.0f;
            for (size_t j = 0; j < features[i].size(); ++j) {
                score += features[i][j] * svc_model_coefficients[cls][j];
            }
            score += svc_model_intercepts[cls];

            if (score > bestScore) {
                bestScore = score;
                bestClass = cls;
            }
        }

        _lastPrediction = bestClass;
        _predictions.push_back(_lastPrediction);                
        
        if (_lastPrediction == std::stoi(labels[i])) {
            _nbGoodPrediction++;
        }
    }
    _end = clock();
}

#ifdef COMPILE_FOR_RPI
void Predictor::neuralNetworkPredict(std::vector<std::vector<float>>& features, std::vector<std::string>& labels){
    auto model = tflite::FlatBufferModel::BuildFromFile("cpp/model/NeuralNetwork.tflite");
    if (!model) {
        std::cerr << "Failed to load model" << std::endl;
        return;
    }

    tflite::ops::builtin::BuiltinOpResolver resolver;
    std::unique_ptr<tflite::Interpreter> interpreter;
    tflite::InterpreterBuilder(*model, resolver)(&interpreter);
    if (!interpreter) {
        std::cerr << "Failed to construct interpreter" << std::endl;
        return;
    }

    if (interpreter->AllocateTensors() != kTfLiteOk) {
        std::cerr << "Failed to allocate tensors" << std::endl;
        return;
    }

    float* input = interpreter->typed_tensor<float>(0);

    _begin = clock();
    for (int i = 0; i < features.size(); i++){
		for (int j = 0; j < features[i].size(); j++){
			input[j]=features[i][j];
		}

        interpreter->Invoke();

        float *output=interpreter->typed_output_tensor<float>(0);

        float max_score=output[0];
        int class_predicted=0;

		for (int j = 1; j < 10; j++){
			if (output[j] > max_score) {
				max_score=output[j];
				class_predicted=j;
			}
		}

        _lastPrediction = class_predicted;
        _predictions.push_back(_lastPrediction);       

		if (class_predicted == std::stoi(labels[i])){
            _nbGoodPrediction++;
		}
    }
    _end = clock();
}
#endif

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

double Predictor::getLastExecTimeMs(){
    return (double(_end - _begin) / CLOCKS_PER_SEC) * 1000.0;
}

