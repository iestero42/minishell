/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestRedirInput.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:13:24 by iestero-          #+#    #+#             */
/*   Updated: 2024/01/11 10:54:28 by iestero-         ###   ########.fr       */
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

void	test_input_simple_1(void)
{
	t_command	cmd;
	char		*token;
	char		*nextToken;
	int			output;

	token = "<";
	cmd.input_redirect = -2;
	nextToken = "./.testing/test/test_files/1";
	output = built_input(token, &cmd, nextToken);
	TEST_ASSERT_NOT_EQUAL(-1, cmd.input_redirect);
}

void	test_input_simple_2(void)
{
	t_command	cmd;
	char		*token;
	char		*nextToken;
	int			output;

	token = "<./.testing/test/test_files/2";
	cmd.input_redirect = -2;
	nextToken = "./test_files/0";
	output = built_input(token, &cmd, nextToken);
	TEST_ASSERT_NOT_EQUAL(-1, cmd.input_redirect);
}

void	test_input_simple_3(void)
{
	t_command	cmd;
	char		*token;
	char		*nextToken;
	int			output;

	token = "<";
	cmd.input_redirect = -1;
	nextToken = NULL;
	output = built_input(token, &cmd, nextToken);
	TEST_ASSERT_EQUAL(EXIT_FAILURE, output);
}

void	test_input_simple_4(void)
{
	t_command	cmd;
	char		*token;
	char		*nextToken;
	int			output;

	token = "<";
	cmd.input_redirect = -1;
	nextToken = "./.testing/test/test_files/0";
	output = built_input(token, &cmd, nextToken);
	TEST_ASSERT_EQUAL(EXIT_FAILURE, output);
}

void	test_input_double_1(void)
{
	t_command	cmd;
	char		*token;
	char		*nextToken;
	int			output;

	token = "<<";
	cmd.input_redirect = -1;
	nextToken = "double_1";
	output = built_input(token, &cmd, nextToken);
	TEST_ASSERT_NOT_EQUAL(-1, cmd.input_redirect);
}

void	test_input_double_2(void)
{
	t_command	cmd;
	char		*token;
	char		*nextToken;
	int			output;

	token = "<<double_2";
	cmd.input_redirect = -1;
	nextToken = "adios";
	output = built_input(token, &cmd, nextToken);
	TEST_ASSERT_NOT_EQUAL(-1, cmd.input_redirect);
}

void	test_input_double_3(void)
{
	t_command	cmd;
	char		*token;
	char		*nextToken;
	int			output;

	token = "<<";
	cmd.input_redirect = -1;
	nextToken = NULL;
	output = built_input(token, &cmd, nextToken);
	TEST_ASSERT_EQUAL(EXIT_FAILURE, output);
}

int	main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_input_simple_1);
	RUN_TEST(test_input_simple_2);
	RUN_TEST(test_input_simple_3);
	RUN_TEST(test_input_simple_4);
	
	RUN_TEST(test_input_double_1);
	RUN_TEST(test_input_double_2);
	RUN_TEST(test_input_double_3);

	UNITY_END();
}
