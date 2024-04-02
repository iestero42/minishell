/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestTrimCommand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:29:43 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/02 10:25:09 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*s;
	char	*input;

	printf("Test 1: \"hola\"\"hola\" \n\n");
	input = "\"hola\"\"hola\"";
	s = trim_command(input);
	printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 2: \"\"hola\"\"hola\"\" \n\n");
	input = "\"\"hola\"\"hola\"\"";
	s = trim_command(input);
	printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 3: \"\'$PATH $PATH $hola\'\"$PATH\"hola\"hola \n\n");
	input = "\"\'$PATH $PATH $hola\'\"$PATH\"hola\"hola";
	s = trim_command(input);
	printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 4: adios\'\"hola\"\'\"hola\" \n\n");
	input = "adios\'\"hola\"\'\"hola\"";
	s = trim_command(input);
	printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	return (0);
}
