#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>




class Predictor {
public:
    Predictor();
    ~Predictor();

    void predict(const char* datasetPath, const char* model_name, const char* scaler_path);
    int getLastPrediction();
    std::vector<int> getPrediction();
    int getNbPrediction();
    float getLastAverage();

private:
    void randomForestPredict(const float *features, int32_t features_length);
    void decisionTreePredict(const float *features, int32_t features_length);

    
    int _lastPrediction = 0;
    int _nbPrediction = 0;
    float _lastAverage = 0.0;
};

#endif
