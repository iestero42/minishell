/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestSplitOperands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 08:34:02 by yunlovex          #+#    #+#             */
/*   Updated: 2024/05/23 08:25:46 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	main(void)
{
	char	**s;

	printf("Test 1: cat hola || echo adios \n\n");
	s = split_command("cat hola || echo  <<adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	double_free(s);
	
	printf("Test 2: ((cat || echo ) && echo) || cat | echo \n\n");
	s = split_command("((cat || echo <<) && >>echo) || cat< | echo>");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	double_free(s);
	
	printf("Test 3: ((cat || echo ) && echo) || cat && \n\n");
	s = split_command("<< ((<cat || echo ) && echo) || cat &&");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	double_free(s);

	printf("Test 4: ( (cat || echo ) && echo) || cat && \n\n");
	s = split_command("( (cat || echo ) && echo) || cat &&");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	double_free(s);

	printf("Test 4: && ( (cat || echo ) && echo) || cat && \n\n");
	s = split_command("&& ( (cat || echo ) && echo) || cat &&");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	double_free(s);
	
	printf("\n\n");
}