#include "audio_preprocessing.h"

AudioPreprocessing::AudioPreprocessing() {
}

AudioPreprocessing::~AudioPreprocessing() {
}


int AudioPreprocessing::readAudioFile(const char* path){
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Unable to open the audio file " << path << std::endl;
        return -1;
    }

    _auHeader.magicNumber = read32Bits(file);
    _auHeader.dataShift = read32Bits(file);
    _auHeader.dataSize = read32Bits(file);
    _auHeader.encoding = read32Bits(file);
    _auHeader.fs = read32Bits(file);
    _auHeader.nbCanal = read32Bits(file);


    file.seekg(_auHeader.dataShift, std::ios::beg);
    int sample = readSample(file);
    _auData.samples.push_back(sample);
    _auData.nbSample++;
    while (!file.eof()) {
        int sample = readSample(file);
        if (!file.eof()){
            _auData.samples.push_back(sample);
            _auData.nbSample++;
        }
    }

    file.close();

    normalizeData();

    return 0;

}

void AudioPreprocessing::normalizeData(){
    int max_value = *std::max_element(_auData.samples.begin(), _auData.samples.end(), 
                                      [](int a, int b) { return std::abs(a) < std::abs(b); });
    if (max_value != 0) {
        for (double &data : _auData.samples) {
            data /= max_value;
        }
    }
}


void AudioPreprocessing::extractDescriptor(std::vector<double> normalized_data) {
    char descriptorCsvPath[1024];
    sprintf(descriptorCsvPath, "%s/descriptor.csv", _csvPath);
    std::ofstream descriptorCsvFile(descriptorCsvPath);

    std::vector<double> sum(FFT_SIZE, 0.0);
    std::vector<double> c(FFT_SIZE, 0.0);   

    for (int i = 0; i < FFT_NUMBER; i++) {
        std::vector<std::complex<float>> fft(FFT_SIZE,0);

        for (int j = 0; j < FFT_SIZE; j++) {
            fft[j] = normalized_data[j + (FFT_SIZE * i)];
        }

        ite_dit_fft(fft); 


        for (int j = 0; j < FFT_SIZE; j++) {
            double magnitude = std::norm(fft[j]);

            _auDescriptor.mu[j] += magnitude / FFT_SIZE;

            sum[j] += magnitude;
            if (i == 0) {
                c[j]=0;
            }
            else {
                c[j] = c[j] + std::pow(((i+1) * magnitude - sum[j]), 2)/(i * (i + 1));
            }
            _auDescriptor.sigma[j] += std::sqrt(c[j]/FFT_SIZE);
        }
    }

    for(int i = 0; i < FFT_SIZE; i++){
        descriptorCsvFile << _auDescriptor.mu[i] << ",";
    }
    for(int i = 0; i < FFT_SIZE; i++){
        descriptorCsvFile << _auDescriptor.sigma[i] << ",";
    }
    descriptorCsvFile << _audioType;
}

const AudioPreprocessing::AuHeader& AudioPreprocessing::getAuHeader() const {
    return _auHeader;
}

const AudioPreprocessing::AuData& AudioPreprocessing::getAuData() const {
    return _auData;
}

const AudioPreprocessing::AuDescriptor& AudioPreprocessing::getAuDescriptor() const {
    return _auDescriptor;
}


void AudioPreprocessing::setCsvPath(const char* path) {
    _csvPath = path;
}

void AudioPreprocessing::setAudioType(const char* audioType) {
    _audioType = audioType;
}


