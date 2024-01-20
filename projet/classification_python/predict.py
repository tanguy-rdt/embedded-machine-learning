import pandas as pd
import numpy as np
import argparse
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.neural_network import MLPClassifier
from sklearn.svm import SVC
from sklearn.metrics import confusion_matrix, classification_report
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import GridSearchCV, cross_val_score, KFold
from joblib import load

def warn(*args, **kwargs):
    pass
import warnings
warnings.warn = warn

def opt_parse():
    parser = argparse.ArgumentParser()
    parser.add_argument("--dataset", required=True, help="Dataset path")
    parser.add_argument("--model", required=True, help="Model path")
    return parser.parse_args()

def load_dataset(path):
    dataset = pd.read_csv(path, header=None).values

    descriptors = dataset[:, :-1] 
    labels = dataset[:, -1]
    labels = [label.split(".")[0] for label in labels]

    return descriptors, labels

def load_model(model_path):
    return load(model_path)

def load_scaler_from_txt(txt_path):
    means = []
    scales = []
    with open(txt_path, 'r') as file:
        for line in file:
            mean, scale = map(float, line.split())
            means.append(mean)
            scales.append(scale)
    return np.array(means), np.array(scales)

def normalize_data(data, mean, scale):
    return (data - mean) / scale

def main():
    opt = opt_parse()
    dataset_path = opt.dataset
    model_path = opt.model

    descriptors, labels = load_dataset(dataset_path)

    mean, scale = load_scaler_from_txt("resources/scaler.txt")
    descriptors = normalize_data(descriptors, mean, scale)
    
    model = load_model(model_path)
    predictions = model.predict(descriptors)

    cpt = 0
    for index, pred in enumerate(predictions):
        if labels[index] == pred:
            cpt += 1

    print(f"Correct prediction: {cpt}/{len(descriptors)}")
    print(f"Accuracy: {cpt/len(descriptors)}")



if __name__ == '__main__':
    main()
