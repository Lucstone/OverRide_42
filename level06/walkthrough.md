#### Etape 1 : Décompilation 
```bash
level06@OverRide:~$ ./level06 
***********************************
*               level06           *
***********************************
-> Enter Login: lnaidu
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: tetetetet
level06@OverRide:~$ 
level06@OverRide:~$ ./level06 
***********************************
*               level06           *
***********************************
-> Enter Login: hjkhjklklhjhjklhjklsdfhjklasdfhjkldfashjklsdfahjklfasdhjklasdfhjklsdfahjklfasdhjklsdfahjklsdfahjklfasdhjkldfashkljdfhjklashjklasdfhjkldfashjklfasdhjklsdfhklajhjklsdfahjklfsdhjsdfhjklsdfhjklahjkldfashjklfasdhjkldfhjklashjklasdfhjklfasdhjklasdfhjklsdfahjklfhjklsdahjklasdfhjklasdfhjklasdfhjkfhjklasdhjklasdfhjsdfahjklf
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: level06@OverRide:~$ 
```

Le binaire demande un login et un mot de pass, si on envoie un login trop long sa reecrit sur le serial number.

#### Etape 2 : Recherche de faille

On analyse le code grace a gdb on voit 2 fonctions interessantes, le main et la fonction auth.

le main recupere le login et le serial et les envoies a la fonction auth. le login et le serial est un unsigned int recupere avec la fonction scanf deplus si auth == 0 alors le programme lance un shell.

```c
  if (iVar1 == 0) {
    puts("Authenticated!");
    system("/bin/sh");
  }
```

lorsque nous analysont la fonction auth nous voyons que la fonction fait un hash du login et le compare avec le serial afin qu'ils soient identiques, et si ils sont identiques alors la fonction retourne 0.

```c
      local_14 = ((int)param_1[3] ^ 0x1337U) + 0x5eeded;
      for (local_18 = 0; local_18 < (int)sVar1; local_18 = local_18 + 1) {
        if (param_1[local_18] < ' ') {
          return 1;
        }
        local_14 = local_14 + ((int)param_1[local_18] ^ local_14) % 0x539;
      }
      if (param_2 == local_14) {
        uVar2 = 0;
      }
```

#### Etape 3 : Idée

Notre idée est donc de refaire le hash du serial pour qu'il soit identique au login, pour cela nous allons devoir faire une fonction qui effectue le meme hash que la fonction auth afin de renvoyer 0.

```c
#include <stdio.h>

int main (int ac, char **av) {
        unsigned int local_14;

        local_14 = ((int)av[1][3] ^ 0x1337U) + 0x5eeded;        
        for (int local_18 = 0; local_18 < 8 ; local_18++) {
               local_14 = local_14 + ((int)av[1][local_18] ^ local_14) % 0x539;
        }
        printf("Last Value %u\n", local_14);

return 0;
}
```
Voir Hashage.c dans le dossier ressources.
Attention on voit aussi que le login doit etrede minimum 6 caracteres, car sinon la fonction auth retourne 1.

```c
      if (sVar1 < 6) {
        return 1;
      }
```


#### Etape 4 : Execution 

```bash
level06@OverRide:~$ vim /tmp/Hashage.c
level06@OverRide:~$ cd /tmp
level06@OverRide:/tmp$ ./a.out lnaidu06
Last Value 6234562
level06@OverRide:/tmp$ cd
level06@OverRide:~$ ./level06 
***********************************
*               level06           *
***********************************
-> Enter Login: lnaidu06
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6234562
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
$ 
```

