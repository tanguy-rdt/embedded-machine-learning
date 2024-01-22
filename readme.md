# Embedded Machine Learning

## Extraction des descriptors

### Debug mode
Sur pc, permet d'extraire pour un fihcier audio et de plot les descripteurs 

```
$ ./run.sh setup_project -d
$ ./run.sh create_dataset -d
```

### Normal mode

Sur pc, permet d'extraire les descripteurs de tous les fichiers audio dans resoources/au_files, les csv sont dans resources/csv_files

```
$ ./run.sh setup_project 
$ ./run.sh create_dataset
```

## Entrainement des models

Sur pc, entraine tous les models et realise une evaluation a la suite, les models sont sauvegarder au format joblib dans resources/model
mais egalement en .h grace au codage automatique de emlearn pour random forest et decision tree dans resources/model. Le linear svc et egalement 
convertis en .h dans ressources/model mais ca conversion et manuel. Le neural network et conmvertis au format tflite dans resources/model 
Le scaler de normalisation et sauvegarder dans resources/scalar.txt
Et la separation du dataset et sauvegarder dans resoiurces/csv_files/dataset_train.csv et dataset_test.csv

```
$ ./run.sh setup_project 
$ ./run.sh train_model
```


## Prediction du model 

### Sur pc en python 

il est important d'avoir fait d'abord ## Entrainement des models isnon ca marche pas parce que les parce qu'il chercher les trucs dans resources

```
$ ./run.sh setup_project 
$ ./run.sh predict -l python
```

### Sur pc en cpp 

le neural network n'est pas activer car necesite tensorflow qui sur rpi 

```
$ ./run.sh setup_project 
$ ./run.sh predict -l cpp
```

### Sur rpi en cpp 

tout fonction 

```
$ ./run.sh setup_project -t target
$ ./run.sh predict -l cpp
```


## Performance 

A recuperer dans les videos, et egalement les figures pour donner un peu de joie au readme 


### Les video 

a dispatche au bon endroit 

<p>
  <a href="https://youtu.be/fa-HDyBif2s">
    <img src="https://img.shields.io/badge/Youtube-red?logo=youtube" alt="">
  </a>
</p>

<p>
  <a href="https://youtu.be/UQsWJZHy_KQ">
    <img src="https://img.shields.io/badge/Youtube-red?logo=youtube" alt="">
  </a>
</p>

<p>
  <a href="https://youtu.be/3dIC714V6eE">
    <img src="https://img.shields.io/badge/Youtube-red?logo=youtube" alt="">
  </a>
</p>

<p>
  <a href="https://youtu.be/et4SyZprzkw">
    <img src="https://img.shields.io/badge/Youtube-red?logo=youtube" alt="">
  </a>
</p>
