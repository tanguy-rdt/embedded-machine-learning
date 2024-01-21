#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/kernels/register.h"

class Predictor {
public:
    Predictor();
    ~Predictor();

    void predict(const char* datasetPath, const char* model_name, const char* scaler_path);
    int getLastPrediction();
    std::vector<int> getPrediction();
    int getNbGoodPrediction();
    float getLastAverage();

private:
    void randomForestPredict(std::vector<std::vector<float>>& features, std::vector<std::string>& labels);
    void decisionTreePredict(std::vector<std::vector<float>>& features, std::vector<std::string>& labels);
    void linearSVCPredict(std::vector<std::vector<float>>& features, std::vector<std::string>& labels);
    void neuralNetworkPredict(std::vector<std::vector<float>>& features, std::vector<std::string>& labels);
    void loadDataset(const std::string& path, std::vector<std::vector<float>>& descriptors, std::vector<std::string>& labels);
    void loadScalerParams(const std::string& path, std::vector<float>& mean, std::vector<float>& scale);
    void normalizeData(std::vector<std::vector<float>>& data, const std::vector<float>& mean, const std::vector<float>& scale);

    int _lastPrediction = 0;
    int _nbGoodPrediction = 0;
    float _lastAverage = 0.0;
    std::vector<int> _predictions; 
};

#endif
