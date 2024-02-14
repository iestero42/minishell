/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestSplitPipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:51:38 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/14 10:56:40 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char	**s;

    s = split_pipes("echo hola> | como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_pipes("echo | $hola <| como |<< adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_pipes("echo $? como <<adios ||");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_pipes("echo >>  ||| como <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_pipes("<< $adios \"|1234\" >>");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

	s = split_pipes("<< $adios \' | 1234 \' <>>");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("posicion: %zi string: %s -- ", i, s[i]);
	printf("\n");

    return (0);
}