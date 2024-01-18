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
    return descriptors

def load_model(model_path):
    return load(model_path)

def main():
    opt = opt_parse()
    dataset_path = opt.dataset
    model_path = opt.model

    descriptors = load_dataset(dataset_path)
    #descriptors = StandardScaler().fit_transform(descriptors)

    model = load_model(model_path)
    predictions = model.predict(descriptors)

    print("Predicted music type:", predictions[0])



if __name__ == '__main__':
    main()
