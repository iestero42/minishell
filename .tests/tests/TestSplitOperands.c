/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestSplitOperands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 08:34:02 by yunlovex          #+#    #+#             */
/*   Updated: 2024/05/09 08:41:48 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	main(void)
{
	char	*s;

	printf("Test 1: echo $? como <<adios \n\n");
	s = split_command("echo $? como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	
	printf("Test 1: echo $? como <<adios \n\n");
	s = split_command("echo $? como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	
	printf("Test 1: echo $? como <<adios \n\n");
	s = split_command("echo $? como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	
	printf("Test 1: echo $? como <<adios \n\n");
	s = split_command("echo $? como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);

	printf("Test 1: echo $? como <<adios \n\n");
	s = split_command("echo $? como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);

	printf("Test 1: echo $? como <<adios \n\n");
	s = split_command("echo $? como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	
	printf("Test 1: echo $? como <<adios \n\n");
	s = split_command("echo $? como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");
}