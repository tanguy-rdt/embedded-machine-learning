import pandas as pd
import numpy as np
import argparse
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import LinearSVC
from sklearn.metrics import confusion_matrix, classification_report
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import GridSearchCV, cross_val_score, KFold
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.utils import to_categorical
from joblib import dump
import emlearn

def NeuralNetwork(input_dim, num_classes):
    model = Sequential()
    model.add(Dense(128, activation='relu', input_dim=input_dim))
    model.add(Dense(64, activation='relu'))
    model.add(Dense(num_classes, activation='softmax'))

    model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    return model

def get_estimator(estimator_name):
    estimator = []

    if 'all' in estimator_name:
        estimator = [RandomForestClassifier(), DecisionTreeClassifier(), LinearSVC(), NeuralNetwork(1024, 10)]
    else:
        for name in estimator_name:
            if name == 'random_forest':
                estimator.append(RandomForestClassifier())
            elif name == 'decision_tree_classifier':
                estimator.append(DecisionTreeClassifier())
            elif name == 'LinearSVC':
                estimator.append(LinearSVC())
            elif name == 'neural_network':
                estimator.append(NeuralNetwork(1024, 10))
            else:
                raise ValueError(f"Unknow model: {name}")

    return estimator

def load_dataset(path):
    dataset = pd.read_csv(path, header=None).values

    descriptors = dataset[:, :-1] 
    labels = dataset[:, -1]
    labels = [label.split(".")[0] for label in labels]

    label_encoder = LabelEncoder()
    labels = label_encoder.fit_transform(labels)

    return descriptors, labels

def save_dataset_train_and_test(X_train, y_train, X_test, y_test):
    f = open("resources/csv_files/dataset_train.csv", "w")
    for index, line in enumerate(X_train):
        for value in line:
            f.write(f"{value},")
        f.write(f"{y_train[index]}\n")
    f.close()

    f = open("resources/csv_files/dataset_test.csv", "w")
    for index, line in enumerate(X_test):
        for value in line:
            f.write(f"{value},")
        f.write(f"{y_test[index]}\n")
    f.close()

def train_model(estimator, X_train, y_train):
    if isinstance(estimator, tf.keras.Model):
        model = estimator
        model.fit(X_train, y_train, epochs=10, batch_size=32) 
    else:
        model = estimator
        model.fit(X_train, y_train)

    return model

def save_model(model):
    if model.__class__.__name__ in ["RandomForestClassifier", "DecisionTreeClassifier"]:
        model_c = emlearn.convert(model)
        c_source = model_c.save(file='resources/model/'+model.__class__.__name__+'.h')
    elif model.__class__.__name__ == 'LinearSVC':
        with open(f"resources/model/{model.__class__.__name__}.h", "w") as file:
            file.write(f"#ifndef LINEAR_SVC_H\n")
            file.write(f"#define LINEAR_SVC_H\n\n")
            file.write("const float svc_model_coefficients[][1024] = {\n")  # Assurez-vous que 1024 correspond au nombre de features

            for class_index in range(model.coef_.shape[0]):  
                file.write("    { ")
                file.write(", ".join(f"{coef}" for coef in model.coef_[class_index]))
                file.write(" },\n")
            
            file.write("};\n\n")

            file.write("const float svc_model_intercepts[] = { ")
            file.write(", ".join(f"{intercept}" for intercept in model.intercept_))
            file.write(" };\n\n")

            file.write("#endif")
    elif isinstance(model, tf.keras.Model):
        converter = tf.lite.TFLiteConverter.from_keras_model(model)
        tflite_model = converter.convert()
        with open(f'resources/model/NeuralNetwork.tflite', 'wb') as f:
            f.write(tflite_model)

    dump(model, "resources/model/"+str(model.__class__.__name__)+'.joblib')
        
def estimate_model(model, X_test, y_test):
    if isinstance(model, tf.keras.Model):
        loss, accuracy = model.evaluate(X_test, y_test)
        print(f"Loss: {loss}, Accuracy: {accuracy}")
    else:
        predictions = model.predict(X_test)
        print(f"\nMatrice de Confusion - {model.__class__.__name__}:", confusion_matrix(y_test, predictions), sep="\n")
        print(f"\nRapport de Classification - {model.__class__.__name__}:", classification_report(y_test, predictions), sep="\n")

def run(dataset_path, estimator_name):
    estimator = get_estimator(estimator_name)

    descriptors, labels = load_dataset(dataset_path)
    X_train, X_test, y_train, y_test = train_test_split(descriptors, labels, test_size=0.33, random_state=42) 
    save_dataset_train_and_test(X_train, y_train, X_test, y_test)

    scaler = StandardScaler().fit(descriptors)
    with open('resources/scaler.txt', 'w') as file:
        for mean, scale in zip(scaler.mean_, scaler.scale_):
            file.write(f'{mean} {scale}\n')
    X_train = scaler.transform(X_train)
    X_test = scaler.transform(X_test)

    for e in estimator:
        model = train_model(e, X_train, y_train)
        save_model(model)
        estimate_model(model, X_test, y_test)

if __name__ == '__main__':
    run("resources/csv_files/datatset.csv", "all")
