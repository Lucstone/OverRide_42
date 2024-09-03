#### Etape 1 : Décompilation 
```bash
level03@OverRide:~$ ./level03 
***********************************
*               level03         **
***********************************
Password:jdsaljdkasl

Invalid Password
level03@OverRide:~$ ./level03 
***********************************
*               level03         **
***********************************
Password:565656 565656

Invalid Password
```

Le binaire demande un mot de passe et le compare a une chaine de caractère. si le mot de passe est incorrecte il affiche "Invalid Password".

#### Etape 2 : Recherche de faille

On analyse le code grace a gdb et ghidra et on trouve une fonction test dans le main qui soustrait le mot de passe a une valeur : 322424845 a qui on soustrait le mot de passe.
Nous voyons aussi que la valeur resultante est utilisée dans un switch case.

```c
  test(input, 0x1337d00d); // 322424845

void test(int param_1,int param_2)
{
  int resultat = param_2 - param_1;
  
  switch(resultat) {
```
Lorsque l'on soustrait le resultat rentre dans le switch case (voir code source) la fonction test appel la fonction decrypt qui a une chaine de caractère en hexa qui fait lóbjet d'un XOR avec la chaine de caractère "Congratulations!".

```c
  local_21 = 0x757c7d51; // u|}Q
  local_1d = 0x67667360; // gfs`
  local_19 = 0x7b66737e; // {fs~
  local_15 = 0x33617c7d; // 3a|}

    pbVar5 = (byte *)"Congratulations!";
```
la chaine est a passer en little endian

#### Etape 3 : Idée

2 idées sont possibles :
- la premiere pour trouver le mot de passe est de tester toutes les valeurs des switch case pour trouver le bon.
- la deuxieme est de trouver la valeur XOR qui donne "Congratulations!" et de la soustraire a la valeur 322424845.

Nous allons utiliser la deuxieme idée.

on convertis donc les lettres en binaire et on fait un XOR avec les valeurs.
Xor : si 0 et 0 alors 0, si 1 et 1 alors 0, si 0 et 1 alors 1, si 1 et 0 alors 1.
                            Xor
C=1000011 | Q=1010001  | 0010010 = 18 
o=1101111 | }=01111101 | 0010010 = 18
n=1101110 | |=01111100 | 0010010 = 18
g=1100111 | u=01110101  | ...
[...]

On obtient donc la valeur 18 en décimal.
nous deduisons donc que la valeur a soustraire a 322424845 est 18 donc 322424845 - 18 = 322424827.


#### Etape 4 : Execution 

```bash
level03@OverRide:~$ ./level03
***
level03        **
***
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
$
```

