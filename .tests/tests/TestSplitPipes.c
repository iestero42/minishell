/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestSplitPipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:51:38 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/19 09:51:11 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char	**s;
    
    printf("Test 1:\n\n");
    s = split_pipes("echo hola> | como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 2:\n\n");
	s = split_pipes("echo | $hola <| como |<< adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 3:\n\n");
	s = split_pipes("echo $? como <<adios ||");
    printf("Error doble pipe");
	printf("\n\n");

    printf("Test 4:\n\n");
	s = split_pipes("echo >>  ||| como <<adios");
    printf("Error triple pipe");
	printf("\n\n");

    printf("Test 5:\n\n");
	s = split_pipes("<< $adios \"|1234\" >>");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 6:\n\n");
	s = split_pipes("<< $adios \' | 1234 \' <>>");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	printf("\n\n");

    printf("Test 7:\n\n");
	s = split_pipes("| << $adios \' | 1234 \' <>>");
    printf("Error inicio con pipe");
	printf("\n\n");

    return (0);
}
