/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaidu <lnaidu@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 18:06:27 by lnaidu            #+#    #+#             */
/*   Updated: 2024/09/08 12:02:58 by lnaidu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main() {
    char *env = getenv("SHELLCODE");
    printf("Adresse de SHELLCODE: %p\n", env);
    return 0;
}