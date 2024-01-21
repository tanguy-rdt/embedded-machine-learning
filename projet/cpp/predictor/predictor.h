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
    void linearSVCPredict(const float *features, int features_length);
    void loadLinearSVCParameters(std::vector<std::vector<float>>& parameters, std::vector<float>& bias);

    
    int _lastPrediction = 0;
    int _nbGoodPrediction = 0;
    float _lastAverage = 0.0;
    std::vector<int> _predictions; 
};

#endif
