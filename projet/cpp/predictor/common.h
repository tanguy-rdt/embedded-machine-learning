#ifndef COMMON_H
#define COMMON_H

void load_dataset(const std::string& path, std::vector<std::vector<float>>& descriptors, std::vector<std::string>& labels) {
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

void load_scaler_params(const std::string& path, std::vector<float>& mean, std::vector<float>& scale) {
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

void normalize_data(std::vector<std::vector<float>>& data, const std::vector<float>& mean, const std::vector<float>& scale) {
    for (auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            row[i] = (row[i] - mean[i]) / scale[i];
        }
    }
}

#endif