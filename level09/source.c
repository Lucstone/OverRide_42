/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaidu <lnaidu@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:47:42 by lnaidu            #+#    #+#             */
/*   Updated: 2024/09/07 15:05:36 by lnaidu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void handle_msg(void)
{
  char local_c8 [140];

  set_username(local_c8);
  set_msg(local_c8);
  puts(">: Msg sent!");
  return;
}


void secret_backdoor(void)
{
  char local_88 [128];
  
  fgets(local_88,0x80,_stdin);
  system(local_88);
  return;
}

void set_msg(char *param_1)
{
  long lVar1;
  undefined8 *puVar2;
  undefined8 local_408 [128];
  
  puVar2 = local_408;
  for (lVar1 = 0x80; lVar1 != 0; lVar1 = lVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puts(">: Msg @Unix-Dude");
  printf(">>: ");
  fgets((char *)local_408,0x400,_stdin);
  strncpy(param_1,(char *)local_408,(long)*(int *)(param_1 + 0xb4));
  return;
}

void set_username(long param_1)
{
  long lVar1;
  undefined8 *puVar2;
  undefined8 local_98 [17];
  int local_c;
  
  puVar2 = local_98;
  for (lVar1 = 0x10; lVar1 != 0; lVar1 = lVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puts(">: Enter your username");
  printf(">>: ");
  fgets((char *)local_98,0x80,_stdin);
  for (local_c = 0; (local_c < 0x29 && (*(char *)((long)local_98 + (long)local_c) != '\0'));
      local_c = local_c + 1) {
    *(undefined *)(param_1 + 0x8c + (long)local_c) = *(undefined *)((long)local_98 + (long)local_c);
  }
  printf(">: Welcome, %s",param_1 + 0x8c);
  return;
}


int main(void)
{
  puts(
      "--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n- -------------------------------------------"
      );
  handle_msg();
  return 0;
}