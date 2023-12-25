#include "audio_preprocessing.h"
#include "matplotlibcpp.h"

AudioPreprocessing::AudioPreprocessing() {
}

AudioPreprocessing::~AudioPreprocessing() {
}


int AudioPreprocessing::readAudioFile(const char* path){
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Unable to open the audio file" << path << std::endl;
        return -1;
    }

    std::ofstream csvFile("./csv/signal.csv");
    if (!csvFile) {
        std::cerr << "Unable to create or write in the csv file" << std::endl;
        file.close();
        return -2;
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
    csvFile << sample;
    _auData.nbSample++;
    while (!file.eof()) {
        int sample = readSample(file);
        if (!file.eof()){
            csvFile << ", " << sample;
            _auData.samples.push_back(sample);
            _auData.nbSample++;
        }
    }

    file.close();
    csvFile.close();

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
    std::ofstream fftCsvFile("./csv/fft.csv");
    std::ofstream muCsvFile("./csv/mu.csv");
    std::ofstream sigmaCsvFile("./csv/sigma.csv");

    std::vector<double> sigma(FFT_SIZE, 0.0);
    std::vector<double> mu(FFT_SIZE, 0.0);

    for (int i = 0; i < FFT_NUMBER; i++) {
        std::vector<std::complex<float>> fft(FFT_SIZE,0);

        for (int j = 0; j < FFT_SIZE; j++) {
            fft[j] = normalized_data[j + (FFT_SIZE * i)];
        }

        ite_dit_fft(fft); 

        for (int j = 0; j < FFT_SIZE; j++) {
            fftCsvFile << fft[j] << "\n";
            double magnitude = std::norm(fft[j]);

            mu[j] += magnitude / FFT_SIZE;
            _auDescriptor.mu[j + (FFT_SIZE * i)] = mu[j] / FFT_NUMBER;
            muCsvFile << _auDescriptor.mu[j + (FFT_SIZE * i)] << "\n";

            sigma[j] += std::pow(magnitude - mu[j], 2)/FFT_SIZE;
            _auDescriptor.sigma[j + (FFT_SIZE * i)] = std::sqrt(sigma[j]/FFT_NUMBER);
            sigmaCsvFile << _auDescriptor.sigma[j + (FFT_SIZE * i)]  << "\n";
        }
    }
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