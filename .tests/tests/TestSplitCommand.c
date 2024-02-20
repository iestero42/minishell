/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestSplitCommand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:43:17 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/20 09:43:53 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char	**s;

    printf("Test 1: echo hola> como <<adios \n\n");
    s = split_command("echo hola> como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 2: echo $hola < como << adios \n\n");
	s = split_command("echo $hola < como << adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 3: echo $? como <<adios \n\n");
	s = split_command("echo $? como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 4: echo >> como <<adios \n\n");
	s = split_command("echo >> como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 5: << $adios 1234 >> \n\n");
	s = split_command("<< $adios 1234 >>");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 6: << $adios 1234 <>> \n\n");
	s = split_command("<< $adios 1234 <>>");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 7: <<hola <<$adios 1234 <>> \n\n");
	s = split_command("<<hola <<$adios 1234 <>>");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 8:  << $adios \"hola < como te >>\" \n\n");
	s = split_command("<< $adios \"hola < como te >>\"");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 9: << $adios \'hola < como te >>\' \n\n");
	s = split_command("<< $adios \'hola < como te >>\'");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 10: <<  $adios        \'hola < como te >>\'  \n\n");
	s = split_command("<<  $adios        \'hola < como te >>\' ");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 11: << $adios \'hola < como te >>\' <<hola \n\n");
	s = split_command("<< $adios \'hola < como te >>\' <<hola ");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 12: << $adios \'hola < como te >>\'<<hola  \n\n");
    s = split_command("<< $adios \'hola < como te >>\'<<hola ");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 13: << $adios \'hola < como te >>\' <<hola       \n\n");
    s = split_command("<< $adios \'hola < como te >>\' <<hola        ");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 14: << $adios $hola\'hola < como te >>\' <<hola \n\n");
    s = split_command("<< $adios $hola\'hola < como te >>\' <<hola");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 15: << $adios $hola\'hola < como te >>\'\"comote\" <<hola \n\n");
    s = split_command("<< $adios $hola\'hola < como te >>\'\"comote\" <<hola");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    return (0);
}
