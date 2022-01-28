# Recherche

## Description

Ce programme permet d'effectuer des recherches dans une banque de recettes d'un fichier et d'enregistrer une série de statistiques dans un fichier de sortie. Il doit donc recevoir en paramètre un fichier ```liste.txt``` contenant à chaque ligne le nom d'une recette suivi par le nom des catégies qu'elle appartienne (entre crochet). Une recette peut être retrouvée dans une à plusieurs catégories et une catégorie peut contenir plusieurs recettes. L'utilisateur peut rechercher soit par catégorie, soit par catégorie avec un mot-clé. Si le catégorie ou le catégorie avec mot-clé est trouvé, le nom de la(des) recette(s) sera affiché, si rien n'est trouvé, un message d'erreur sera affiché. Toute autre combinaison sera considérée invalide et sera rejeté par l'application. D'ailleurs, il est important qu'aucune ligne du fichier dépasse 120 caractères et l'utilisateur peut faire autant de recherches qu'il désire a chaque exécution du programme. 

Pour arrêter le programme, il faut taper sur ```Ctrl + C```.

**Exemple d'une banque de recettes**

* Poulet au romarin [poulet] [bbq]
* Boeuf au satay [boeuf] [asiatique]
* Salade du jardin [vegetarien]
* Poulet crapaudine [poulet]
* Pho [soupe] [asiatique]
* Authentique gibelotte des iles de Sorel [soupe] [poisson] [terroir]

**Statistiques à produire**

* Le nombre de lignes dans le fichier d'entrée
* Le nombre de mots sans doublons
* Le nombre de mots avec doublons
* La lettre la plus fréquente (sans considérer les doublons)
* Le nombre de catégories
* Le nombre de recettes
* La catégorie la plus populaire (la plus fréquente)
* La catégorie qui a le plus grand nombre de recettes
* La recette la plus longue (en termes de nombre de caractères)


## Auteur

Fang, Xin Ran

  
## Fonctionnement

**Guide d'utilisation**

Avant de pouvoir compiler un programme en ```C``` à l'aide de la ligne de commande, il faut s'assurer d'avoir déjà installé GCC ```GNU C Compiler``` sur le système.


**Compilation du programme Recherche**

Pour compiler le programme ```recherche```, il faut utiliser l'une des deux commandes suivantes:

```
$ gcc -Wall -c recherche.c
```

```
$ make build
```


Pour faire l'édition des liens au programme ```recherche```, il faut utiliser l'une des trois commandes suivantes:

```
$ gcc -Wall recherche.c -o recherche
```

```
$ make
```

```
$ make link
```


Pour effacer les fichiers créés, il faut utiliser l'une des deux commandes suivantes:

```
$ rm -f recherche *.o *.txt
```

```
$ make clean
```


**Exécution du programme Recherche**

Pour effectuer une recherche par catégorie il faut lancer le programme ```recherche``` avec la commande suivante:

```
$ ./recherche [liste.txt] [nom_de_categorie]
```

Pour effectuer une recherche par catégorie avec mot-clé, il faut lancer le programme ```recherche``` avec la commande suivante:

```
$ ./recherche [liste.txt] [nom_de_categorie] [mot_cle]
```

Le programme permet aussi de calculer des statistiques, les résultats seront sauvegardés dans un fichier spécifié à la console. Si le fichier de sortie n'existe pas, il sera créé; s'il existe, il sera écrasé. La commande à utiliser est la suivante:

```
$ ./recherche [liste.txt] -S [stats.txt]
```


* ```[liste.txt]``` représente le fichier qui contient les recettes et les catégories des recettes, il doit être déjà créé avant que le programme soit lancé.
* ```[stats.txt]``` représente le fichier qui sert à enregistrer le statistiques, si ce fichier existait avant que le programme soit lancé, son contenu sera effacé et sera remplacé par les statistiques.
  

**Cas d'erreur**

* Si tout va bien, le programme s'arrête et retourne le code ```0```.

* Si le nombre d'arguments n'égale pas à trois (exécutable, fichier d'entrée et fichier de sorite), un message d'erreur et le guide d'utilisation seront affichés. Puis le programme s'arrête et retourne le code ```1```.

* Si le fichier d'entrée n'existe pas, un message d'erreur et le guide d'utilisation seront affichés. Puis le programme s'arrête et retourne le code ```2```. 

* S'il y a une ligne du fichier d'entrée qui contient 120 chars et plus, un message d'erreur et le guide d'utilisation seront affichés. Puis le programme s'arrête et retourne le code ```3```. 

* S'il y a une erreur d'allocation de type string, un message d'erreur sera affiché, le programme s'arrêtera et retournera le code ```4```. 

* S'il y a une erreur d'allocation de type struct Node, un message d'erreur sera affiché, le programme s'arrêtera et retournera le code ```5```. 


## Tests

Pour vérifier le fonctionnement du programme ```recherche```, il faut utiliser la commande suivante afin de lancer une série de tests:

```
$ make test
```
* 1 - test_isInputStringLessThan120Chars();
* 2 - test_createNewNode();
* 3 - test_getLength();
* 4 - test_deleteList();
* 5 - test_equalsIgnoreCase();

## Dépendances

* [GCC](https://gcc.gnu.org/) - The GNU C Compiler
* [Vim](https://www.vimorg/) - The text editor
* [CUnit](http://cunit.sourceforge.net/) - A Unit Testing Framework for C
* [GitLab-CI](https://docs.gitlab.com/ee/ci/) - Continuous Integration (CI)


## Références

* [geeksforgeeks] (https://www.geeksforgeeks.org/given-a-linked-list-which-is-sorted-how-will-you-insert-in-sorted-way/) - Linked list
