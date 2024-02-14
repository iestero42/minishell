/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestSplitCommand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:43:17 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/14 12:09:08 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char	**s;

    s = split_command("echo hola> como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_command("echo $hola < como << adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_command("echo $? como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_command("echo >> como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_command("<< $adios 1234 >>");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_command("<< $adios 1234 <>>");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_command("<<hola <<$adios 1234 <>>");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_command("<< $adios \"hola < como te >>\"");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_command("<< $adios \'hola < como te >>\'");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_command("<<  $adios        \'hola < como te >>\' "   );
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_command("<< $adios \'hola < como te >>\' <<hola ");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

    return (0);
}
