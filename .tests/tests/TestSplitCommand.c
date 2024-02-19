/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestSplitCommand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:43:17 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/19 09:48:10 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char	**s;

    printf("Test 1:\n\n");
    s = split_command("echo hola> como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 2:\n\n");
	s = split_command("echo $hola < como << adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 3:\n\n");
	s = split_command("echo $? como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 4:\n\n");
	s = split_command("echo >> como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 5:\n\n");
	s = split_command("<< $adios 1234 >>");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 6:\n\n");
	s = split_command("<< $adios 1234 <>>");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 7:\n\n");
	s = split_command("<<hola <<$adios 1234 <>>");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 8:\n\n");
	s = split_command("<< $adios \"hola < como te >>\"");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 9:\n\n");
	s = split_command("<< $adios \'hola < como te >>\'");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 10:\n\n");
	s = split_command("<<  $adios        \'hola < como te >>\' ");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 11:\n\n");
	s = split_command("<< $adios \'hola < como te >>\' <<hola ");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 12:\n\n");
    s = split_command("<< $adios \'hola < como te >>\'<<hola ");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 13:\n\n");
    s = split_command("<< $adios \'hola < como te >>\' <<hola        ");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    return (0);
}
