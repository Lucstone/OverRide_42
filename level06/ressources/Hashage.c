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