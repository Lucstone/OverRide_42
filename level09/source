/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaidu <lnaidu@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:47:42 by lnaidu            #+#    #+#             */
/*   Updated: 2024/09/07 17:44:30 by lnaidu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct s_user
{
  char msg[140];
  char username[40];
  int len;
};

void handle_msg(void)
{
  char str [140];

  set_username(str);
  set_msg(str);
  puts(">: Msg sent!");
  return;
}


void secret_backdoor(void)
{
  char buffer [128];
  
  fgets(buffer,0x80,stdin); // 128
  system(buffer);
  return;
}

void set_msg(struct s_user *param_1)
{
  char local_408 [1024];
  
  memset(local_408,0,0x400); // 1024
  puts(">: Msg @Unix-Dude");
  printf(">>: ");
  fgets(local_408,0x400,stdin); // 1024
  strncpy(param_1->msg,local_408,param_1->len + 0xb4);
  return;
}

void set_username(struct s_user *param_1)
{
  char local_98 [128];
  int i = 0;
  
  bzero(local_98,0x80); // 128
  puts(">: Enter your username");
  printf(">>: ");
  fgets(local_98,0x80,stdin);
  for (i = 0; (i < 0x29 && local_98[i] != '\0'); i++); //0x29 = 41
  {
    param_1->username[i] = local_98[i];
  }
  printf(">: Welcome, %s",param_1->username + 0x8c); // 140
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