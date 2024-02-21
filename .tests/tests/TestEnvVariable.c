/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestEnvVariable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:48:55 by iestero-          #+#    #+#             */
/*   Updated: 2024/02/21 10:51:56 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*s;

    printf("Test 1: $PATH \n\n");
	s = "$PATH";
    built_env_variable(&s, 42);
    printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 2: $hola \n\n");
	s = "$hola";
    built_env_variable(&s, 42);
    printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 3: $? \n\n");
	s = "$?";
    built_env_variable(&s, 42);
    printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 4: $PATH$PATH \n\n");
	s = "$PATH$PATH";
    built_env_variable(&s, 42);
    printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 5: $ROOT \n\n");
	s = "$ROOT";
    built_env_variable(&s, 42);
    printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 6: $$ \n\n");
	s = "$$";
    built_env_variable(&s, 42);
    printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 7: $ \n\n");
	s = "$";
    built_env_variable(&s, 42);
    printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 8: $ \n\n");
	s = "$";
    built_env_variable(&s, 42);
    printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 9: hola$PATH \n\n");
	s = "hola$PATH";
    built_env_variable(&s, 42);
    printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 10: $PATH\"hola\" \n\n");
	s = "$PATH\"hola\"";
    built_env_variable(&s, 42);
    printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

	printf("Test 11: \"hola $PATH como\"$PATH \n\n");
	s = "\"hola $PATH como\"$PATH";
    built_env_variable(&s, 42);
    printf("-- string: %s -- \n", s);
	printf("\n\n");
	free(s);

    return (0);
}
