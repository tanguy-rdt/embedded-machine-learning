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
from joblib import dump

def warn(*args, **kwargs):
    pass
import warnings
warnings.warn = warn

def opt_parse():
    parser = argparse.ArgumentParser()
    parser.add_argument("--dataset", required=True, help="Dataset path")
    parser.add_argument("--estimator", nargs='+', choices=['random_forest', 'logistic_regression', 'svm', 'neural_network', 'all'], required=True, help="Estimator type to train")
    return parser.parse_args()

def get_estimator(estimator_name):
    estimator = []

    if 'all' in estimator_name:
        estimator = [RandomForestClassifier(), LogisticRegression(), SVC(), MLPClassifier()]
    else:
        for name in estimator_name:
            if name == 'random_forest':
                estimator.append(RandomForestClassifier())
            elif name == 'logistic_regression':
                estimator.append(LogisticRegression())
            elif name == 'svm':
                estimator.append(SVC())
            elif name == 'neural_network':
                estimator.append(MLPClassifier())
            else:
                raise ValueError(f"Unknow model: {name}")

    return estimator

def load_dataset(path):
    dataset = pd.read_csv(path, header=None).values

    descriptors = dataset[:, :-1] 
    labels = dataset[:, -1]
    labels = [label.split(".")[0] for label in labels]

    return descriptors, labels

def train_model(estimator, X_train, y_train, param_grid=None):
    if param_grid:
        cv_inner = KFold(n_splits=3, shuffle=True, random_state=1)
        grid_search = GridSearchCV(estimator=estimator, param_grid=param_grid, scoring='accuracy', n_jobs=1, cv=cv_inner, refit=True)
        grid_search.fit(X_train, y_train)
        best_params = grid_search.best_params_
        model = estimator.set_params(**best_params)
    else:
        model = estimator

    model.fit(X_train, y_train)
    return model

def estimate_model(model, X_test, y_test):
    predictions = model.predict(X_test)

    print(f"\nMatrice de Confusion - {model.__class__.__name__}:", confusion_matrix(y_test, predictions), sep="\n")
    print(f"\nRapport de Classification - {model.__class__.__name__}:", classification_report(y_test, predictions), sep="\n")

def save_model(model, path):
    dump(model, path)

def main():
    opt = opt_parse()
    dataset_path = opt.dataset
    estimator_name = opt.estimator
    estimator = get_estimator(estimator_name)

    descriptors, labels = load_dataset(dataset_path)
    #descriptors = StandardScaler().fit_transform(descriptors)
    X_train, X_test, y_train, y_test = train_test_split(descriptors, labels, test_size=0.33, random_state=42) 

    for e in estimator:
        model = train_model(e, X_train, y_train)
        estimate_model(model, X_test, y_test)
        save_model(model, "model/"+str(model.__class__.__name__)+'.joblib')

if __name__ == '__main__':
    main()
