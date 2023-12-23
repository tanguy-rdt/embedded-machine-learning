import matplotlib.pyplot as plt
import csv
import numpy as np

# Remplacez ces valeurs par vos données réelles
fft_size = 512  # Par exemple, 1024 points dans votre FFT
fs = 22050       # Fréquence d'échantillonnage, par exemple 48 kHz
# Lire les données

mu_values = []
with open('./fft.csv', 'r') as file:
    csv_reader = csv.reader(file)
    for row in csv_reader:
        # Ici, on suppose que chaque ligne a une seule colonne avec la valeur mu
        mu_values.append(float(row[0])) 

frequencies = np.fft.fftfreq(fft_size, 1/fs)

amplitudes = np.abs(mu_values)

plt.plot(frequencies, amplitudes)
plt.title('Amplitude en fonction de la Fréquence')
plt.xlabel('Fréquence (Hz)')
plt.ylabel('Amplitude')
plt.show()

