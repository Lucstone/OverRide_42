#### Etape 1 : Décompilation 
Nous trouvons un binaire level00 dans le répertoire, lorsque nous l'exécutons, il nous demande un mot de passe.

```bash
level00@OverRide:~$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:level00

Invalid Password!
```
Nous decidons de le décompiler avec ghidra et trouvons le code dans source.c.


#### Etape 2 : Faiblesses

Le programme de mande un mot de passe et enregistre ce mot de passe dans la variable local_14. Ensuite il compare le mot de passe avec la valeur 0x149c (5276). Si le mot de passe est correct, le programme affiche /bin/sh.

#### Etape 3 : Plan d'action

Ecrire la valeur 5276 lorsque le mot de passe est demandé

# Etape 4 : Execution

```bash
level00@OverRide:~$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!

$ whoami
level01
$ pwd
/home/users/level00
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL

```