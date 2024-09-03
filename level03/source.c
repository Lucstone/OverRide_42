/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaidu <lnaidu@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:55:07 by lnaidu            #+#    #+#             */
/*   Updated: 2024/09/03 19:11:08 by lnaidu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int decrypt(EVP_PKEY_CTX *ctx,uchar *out,size_t *outlen,uchar *in,size_t inlen)
{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  byte *pbVar5;
  int in_GS_OFFSET;
  bool bVar6;
  bool bVar7;
  uint local_2c;
  undefined4 local_21;
  undefined4 local_1d;
  undefined4 local_19;
  undefined4 local_15;
  undefined local_11;
  int local_10;
  
  local_10 = *(int *)(in_GS_OFFSET + 0x14);
  local_21 = 0x757c7d51; // u|}Q
  local_1d = 0x67667360; // gfs`
  local_19 = 0x7b66737e; // {fs~
  local_15 = 0x33617c7d; // 3a|}
  local_11 = 0;
  uVar2 = 0xffffffff;
  puVar4 = &local_21;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *(char *)puVar4;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  } while (cVar1 != '\0');
  local_2c = 0;
  while( true ) {
    bVar6 = local_2c < ~uVar2 - 1;
    bVar7 = local_2c == ~uVar2 - 1;
    if (!bVar6) break;
    *(byte *)((int)&local_21 + local_2c) = (byte)ctx ^ *(byte *)((int)&local_21 + local_2c);
    local_2c = local_2c + 1;
  }
  iVar3 = 0x11;
  puVar4 = &local_21;
  pbVar5 = (byte *)"Congratulations!";
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *(byte *)puVar4 < *pbVar5;
    bVar7 = *(byte *)puVar4 == *pbVar5;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
    pbVar5 = pbVar5 + 1;
  } while (bVar7);
  if ((!bVar6 && !bVar7) == bVar6) {
    iVar3 = system("/bin/sh");
  }
  else {
    iVar3 = puts("\nInvalid Password");
  }
}

void test(int param_1,int param_2)
{
  int resultat = param_2 - param_1;
  
  switch(resultat) {
  default:

  case 0x1: // 1
    decrypt(resultat);
    break;
  case 0x2: // 2
    decrypt(resultat);
    break;
  case 0x3: // 3
    decrypt(resultat);
    break;
  case 0x4: // 4
    decrypt(resultat);
    break;
  case 0x5: // 5
    decrypt(resultat);
    break;
  case 0x6: // 6
    decrypt(resultat);
    break;
  case 0x7: // 7
    decrypt(resultat);
    break;
  case 0x8: // 8
    decrypt(resultat);
    break;
  case 0x9: // 9
    decrypt(resultat);
    break;
  case 0x10: // 16
    decrypt(resultat);
    break;
  case 0x11: // 17
    decrypt(resultat);
    break;
  case 0x12: // 18
    decrypt(resultat);
    break;
  case 0x13: // 19
    decrypt(resultat);
    break;
  case 0x14: // 20
    decrypt(resultat);
    break;
  case 0x15: // 21
    decrypt(resultat);
  }
  return;
}

int main(void)
{
  uint __seed;
  int input;    
  __seed = time((time_t *)0x0);
  srand(__seed);
  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");
  printf("Password:");
  __isoc99_scanf();
  test(input, 0x1337d00d); // 322424845
  return 0;
}


