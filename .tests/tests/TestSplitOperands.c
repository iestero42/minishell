/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestSplitOperands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 08:34:02 by yunlovex          #+#    #+#             */
/*   Updated: 2024/05/17 10:08:07 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	main(void)
{
	char	**s;

	printf("Test 1: cat hola || echo adios \n\n");
	s = split_operands("cat hola || echo adios");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	double_free(s);
	
	printf("Test 2: ((cat || echo ) && echo) || cat | echo \n\n");
	s = split_operands("((cat || echo ) && echo) || cat | echo");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	double_free(s);
	
	printf("Test 3: ((cat || echo ) && echo) || cat && \n\n");
	s = split_operands("((cat || echo ) && echo) || cat &&");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	double_free(s);

	printf("Test 4: ( (cat || echo ) && echo) || cat && \n\n");
	s = split_operands("( (cat || echo ) && echo) || cat &&");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	double_free(s);

	printf("Test 4: && ( (cat || echo ) && echo) || cat && \n\n");
	s = split_operands(" && ( (cat || echo ) && echo) || cat &&");
    for (size_t i = 0; s[i] != NULL; i++)
        printf("-- posicion: %zi string: %s -- \n", i, s[i]);
	double_free(s);
	
	printf("\n\n");
}