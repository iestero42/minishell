/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestSplitCommand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:24:49 by iestero-          #+#    #+#             */
/*   Updated: 2024/01/11 12:21:05 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "unity.h"
#include "minishell.h"

void	setUp(void)
{

}

void	tearDown(void)
{

}

void	test_split_command(void)
{
	char	**command;
	int 	output;

	command = split_command("echo\"$hola me llamo israel\" \'hola\' $hola <<tres > adios");
	for (int i = 0; command[i] != NULL; i++)
	{
		printf("%s\n", command[i]);
	}
	output = (command != NULL);
	TEST_ASSERT_EQUAL(EXIT_SUCCESS, output);
}

int	main(void)
{
	UNITY_BEGIN();
	
	RUN_TEST(test_split_command);
	
	UNITY_END();
}
