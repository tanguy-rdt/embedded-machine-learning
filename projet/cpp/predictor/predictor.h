#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>

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
    void randomForestPredict(const float *features, int32_t features_length);
    void decisionTreePredict(const float *features, int32_t features_length);
    void linearSVCPredict(const float *features, int features_length, int nbCls);
    void loadDataset(const std::string& path, std::vector<std::vector<float>>& descriptors, std::vector<std::string>& labels);
    void loadScalerParams(const std::string& path, std::vector<float>& mean, std::vector<float>& scale);
    void normalizeData(std::vector<std::vector<float>>& data, const std::vector<float>& mean, const std::vector<float>& scale);

    int _lastPrediction = 0;
    int _nbGoodPrediction = 0;
    float _lastAverage = 0.0;
    std::vector<int> _predictions; 
};

#endif
