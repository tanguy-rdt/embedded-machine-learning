import os, sys
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import random

def load_dataset():
    directory_path = '../csv_files'
    label_names = []
    data = []

    for label in os.listdir(directory_path):
        label_path = os.path.join(directory_path, label)
        if os.path.isdir(label_path):
            for file in os.listdir(label_path):

                csv_path = os.path.join(os.path.join(label_path, file), "descriptor.csv")
                if os.path.isfile(csv_path):
                    descriptor = pd.read_csv(csv_path, header=None, names=['mu', 'sigma'])
                    last_row = descriptor.tail(1).to_numpy()
                    mu = last_row[0][0]
                    sigma = last_row[0][1]
                    data.append([label, mu, sigma])

    random.shuffle(data)
    label_names = np.array([label[0] for label in data])
    descriptors = np.array([descriptor[1:] for descriptor in data])

    return label_names, descriptors

label_names, descriptors = load_dataset()

labels = ["blues", "classical", "country", "disco", "hiphop", "jazz", "metal", "pop", "reggae", "rock"]

for lab in labels:
    blues_indices = np.where(label_names == lab)[0]
    mu_values_for_blues = descriptors[blues_indices, 0]  # 0 pour la colonne mu
    sigma_values_for_blues = descriptors[blues_indices, 1]  # 0 pour la colonne mu

    print("Moyenne de mu pour", lab, ":", np.mean(mu_values_for_blues))
    print("Moyenne de sigma pour", lab, ":", np.mean(sigma_values_for_blues))
    print("ecart type de mu pour", lab, ":", np.std(mu_values_for_blues))
    print("ecart type de sigma pour", lab, ":", np.std(sigma_values_for_blues))
    print("-----------------------------------------------")




