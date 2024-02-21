/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestRedirInput.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:32:12 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/21 10:58:12 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char		*s;
	char		*nextToken;
	t_command	cmd;


	cmd.input_redirect = -2;
	printf("Test 1: \n\n");
	s = "<";
	nextToken = "../../src/main/minishell.c";
    built_input(s, &cmd, nextToken);
    printf("-- string: %s -- \n", s);
	printf("-- cmd: %i -- \n", cmd.input_redirect);
	printf("-- string: %s -- \n", nextToken);
	printf("\n\n");

	cmd.input_redirect = -2;
	printf("Test 2: \n\n");
	s = "<";
	nextToken = "";
    built_input(s, &cmd, nextToken);
    printf("-- string: %s -- \n", s);
	printf("-- cmd: %i -- \n", cmd.input_redirect);
	printf("-- string: %s -- \n", nextToken);
	printf("\n\n");

	cmd.input_redirect = -2;
	printf("Test 3: \n\n");
	s = "<";
	nextToken = NULL;
    built_input(s, &cmd, nextToken);
    printf("-- string: %s -- \n", s);
	printf("-- cmd: %i -- \n", cmd.input_redirect);
	printf("-- string: %s -- \n", nextToken);
	printf("\n\n");

	cmd.input_redirect = -2;
	printf("Test 4: \n\n");
	s = "<";
	nextToken = ">";
    built_input(s, &cmd, nextToken);
    printf("-- string: %s -- \n", s);
	printf("-- cmd: %i -- \n", cmd.input_redirect);
	printf("-- string: %s -- \n", nextToken);
	printf("\n\n");

	cmd.input_redirect = -2;
	printf("Test 5: \n\n");
	s = "<<";
	nextToken = "hola";
    built_input(s, &cmd, nextToken);
    printf("-- string: %s -- \n", s);
	printf("-- cmd: %i -- \n", cmd.input_redirect);
	printf("-- string: %s -- \n", nextToken);
	printf("\n\n");

	cmd.input_redirect = -2;
	printf("Test 6: \n\n");
	s = "<<";
	nextToken = "";
    built_input(s, &cmd, nextToken);
    printf("-- string: %s -- \n", s);
	printf("-- cmd: %i -- \n", cmd.input_redirect);
	printf("-- string: %s -- \n", nextToken);
	printf("\n\n");
}
