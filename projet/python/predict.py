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

def load_dataset(path):
    dataset = pd.read_csv(path, header=None).values

    descriptors = dataset[:, :-1] 
    labels = dataset[:, -1]
    labels = [label.split(".")[0] for label in labels]

    return descriptors, labels

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

def run(dataset_path, model_path):
    descriptors, labels = load_dataset(dataset_path)

    mean, scale = load_scaler_from_txt("resources/scaler.txt")
    descriptors = normalize_data(descriptors, mean, scale)
    
    model = load(model_path)
    predictions = model.predict(descriptors)

    cpt = 0
    for index, pred in enumerate(predictions):
        if labels[index] == pred:
            cpt += 1

    print(f"Correct prediction: {cpt}/{len(descriptors)}")
    print(f"Accuracy: {cpt/len(descriptors)}")

if __name__ == '__main__':
    run("resources/csv_files/dataset_test.csv", "resources/model_python/RandomForestClassifier.joblib")
