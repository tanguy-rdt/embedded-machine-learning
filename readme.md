
Au cours des 16h de Cr dédiés à cette matière nous avons conçu un programme permettant la reconnaissance de style musical d’après un extrait audio de 30 secondes.
Nous avons utilisé la base de données GTZAN[1] : 1000 pistes audio de 30 secondes, format .au, avec 10 classes (blues, classique, country, Disco, Hiphop, Jazz, Metal, Pop, Reggae, Rock).

![Image Locale](cours/result_emb_proj.png)

## Utilisation

1. [__Extraction des descripteurs__](#extraction-des-descripteurs)
    - Mode normal: Extrait les descripteurs de tous les fichiers audio
        ```bash
        $ ./run.sh setup_project 
        $ ./run.sh create_dataset
        ```
    - Mode de debug: Extrait et affiche les descripteurs d'un fichier audio
        ```
        $ ./run.sh setup_project -d
        $ ./run.sh create_dataset -d
        ```

2. [__Entrainement des models__](#entrainement-des-models)
    ```bash
    $ ./run.sh setup_project 
    $ ./run.sh train_model
    ```

3. [__Prédiction à l'aide des models__](#prédiction-à-laide-des-models)
    - En Python sur PC de dev
        ```bash
        $ ./run.sh setup_project 
        $ ./run.sh predict -l python
        ```
    - En C++ sur PC de dev
        ```bash
        $ ./run.sh setup_project 
        $ ./run.sh predict -l cpp
        ```
    - En C++ sur cible
        ```bash
        $ ./run.sh setup_project -t
        $ ./run.sh predict -l cpp
        ```

_NB: Il est important de conservé la structure de nos dossiers, sinon le code ne fonctionnera pas:_
- _Les fichiers audio: `resources/au_files`_
- _Les fichiers CSV: `resources/csv_files`_
- _Les modèle Python: `resources/model`_
- _Les modèle C++: `cpp/predictor/model`_

## Extraction des descripteurs

## Entrainement des models

## Prédiction à l'aide des models

## Mesure de performance

Pour utiliser correctement le projet, il faut executer les codes en suivant rigoureusement les étapes ci-dessous :

### Extraction des descriptors
#### Mode normal

Pour une utilisation normale du code, executez ces lignes de commande qui permettent d'extraire les descripteurs de tous les fichiers audio dans resoources/au_files, les csv se trouvent dans resources/csv_files.

```
$ ./run.sh setup_project 
$ ./run.sh create_dataset
```

#### Mode Debug
<p>
  <a href="https://youtu.be/et4SyZprzkw">
    <img src="https://img.shields.io/badge/Youtube-red?logo=youtube" alt="">
  </a>
</p>
Ce mode à utiliser en debug permet d'extraire les descripteurs pour un seul fichier audio et de les afficher graphiquement.

```
$ ./run.sh setup_project -d
$ ./run.sh create_dataset -d
```

### Entrainement des modèles

Executez ces lignes pour entrainer tous les modèles et réaliser une évaluation à la suite.

```
$ ./run.sh setup_project 
$ ./run.sh train_model
```
### Prédiction du modèle

Après avoir entrainé les modèles on réalise la prédiction avec les lignes suivantes:

#### Sur pc en python
<p>
  <a href="https://youtu.be/fa-HDyBif2s">
    <img src="https://img.shields.io/badge/Youtube-red?logo=youtube" alt="">
  </a>
</p>

```
$ ./run.sh setup_project 
$ ./run.sh predict -l python
```

#### Sur pc en cpp 
<p>
  <a href="https://youtu.be/UQsWJZHy_KQ">
    <img src="https://img.shields.io/badge/Youtube-red?logo=youtube" alt="">
  </a>
</p>

```
$ ./run.sh setup_project 
$ ./run.sh predict -l cpp
```

#### Sur rpi en cpp 
<p>
  <a href="https://youtu.be/3dIC714V6eE">
    <img src="https://img.shields.io/badge/Youtube-red?logo=youtube" alt="">
  </a>
</p>

```
$ ./run.sh setup_project -t target
$ ./run.sh predict -l cpp
```
## Performances du système
![Image Locale](cours/pred_RF.png)

En testant chacun des modèles nous observons que le plus performant est le Random Forest avec une précision de 55% qui est un résultat attendu. Pour améliorer encore cette précision nous pourrions à l'avenir jouer sur les hyperparamètres pour affiner la prédiction.

## Contributing

Si vous souhaitez contribuer, lisez le fichier [CONTRIBUTING.md](https://example.org) pour savoir comment le faire.

## Auteurs
* **Tanguy Roudaut** _alias_ [@tanguy-rdt](https://github.com/tanguy-rdt)
* **Baptiste Le Roux** _alias_ [@BaptisteLeRouxx](https://github.com/tanguy-rdt)
* **Mathis Le Roux** _alias_ [@Math-lrx](https://github.com/tanguy-rdt)

Lisez la liste des [contributeurs](https://github.com/your/project/contributors) pour voir qui à aidé au projet !
