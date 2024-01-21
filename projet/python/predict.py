import pandas as pd
import numpy as np
import os
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.neural_network import MLPClassifier
from sklearn.svm import LinearSVC
from sklearn.metrics import confusion_matrix, classification_report
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import GridSearchCV, cross_val_score, KFold
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.utils import to_categorical
from joblib import load

def load_dataset(path):
    dataset = pd.read_csv(path, header=None).values

    descriptors = dataset[:, :-1] 
    labels = dataset[:, -1]

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

def load_tflite_model(model_path):
    interpreter = tf.lite.Interpreter(model_path=model_path)
    interpreter.allocate_tensors()
    return interpreter

def run_tflite_model(interpreter, input_data):
    input_details = interpreter.get_input_details()
    output_details = interpreter.get_output_details()

    input_data = np.array(input_data, dtype=np.float32)
    interpreter.set_tensor(input_details[0]['index'], input_data)

    interpreter.invoke()

    output_data = interpreter.get_tensor(output_details[0]['index'])
    return output_data


def run(dataset_path, model_path):
    descriptors, labels = load_dataset(dataset_path)

    mean, scale = load_scaler_from_txt("resources/scaler.txt")
    descriptors = normalize_data(descriptors, mean, scale)
    

    model_extension = os.path.splitext(model_path)[1]
    if model_extension == '.joblib':
        model = load(model_path)
        predictions = model.predict(descriptors)

        cpt = 0
        for index, pred in enumerate(predictions):
            if labels[index] == pred:
                cpt += 1

        print(f"Correct prediction: {cpt}/{len(descriptors)}")
        print(f"Accuracy: {cpt/len(descriptors)}")
    elif model_extension == '.tflite':
        interpreter = load_tflite_model(model_path)

        cpt = 0
        for index, desc in enumerate(descriptors):
            pred = run_tflite_model(interpreter, [desc])
            predicted_label = np.argmax(pred)

            if labels[index] == predicted_label:
                cpt += 1

        print(f"Correct prediction: {cpt}/{len(descriptors)}")
        print(f"Accuracy: {cpt/len(descriptors)}")

    else:
        print("Unsupported model type")

if __name__ == '__main__':
    run("resources/csv_files/dataset_test.csv", "resources/model_python/RandomForestClassifier.joblib")
