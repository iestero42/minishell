/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_format_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:52:23 by iestero-          #+#    #+#             */
/*   Updated: 2023/09/03 12:15:43 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

/**
 * Function that look for the zeroflag in the format string
 * @param str where the zeroflag should be
 * @return char "0" if it was found or null if not
 */
char	find_zeroflag(char	*str)
{
	int		i;

	i = 0;
	while ((str[i] < '0' || str[i] > '9') && str[i] != '\0')
		i++;
	if (str[i] == '0')
		return (str[i]);
	return (0);
}

/**
 * Funtion use to calculate the value of the precision
 * @param str the string where the precision is
 * @return int which store the value of the precision
*/
static int	ft_calculate_precision(char	*str)
{
	return (ft_atoi(str + 1));
}

/**
 * Auxiliar function that insert in the tree the rest of the flags 
 * if they are found
 * @param str the string with all the flags
 * @param tree the binary tree where all the flags goes
 * @param width the int value of the width 
*/
static void	ft_store_format_aux(char *str, t_tree **tree, int width)
{
	int	precision;

	if (ft_strchr(str, '-'))
		ft_insert_node(tree, MINUSFLAG, "", width);
	else if (find_zeroflag(str))
		ft_insert_node(tree, ZEROFLAG, "", width);
	if (ft_strchr(str, '.'))
	{
		precision = ft_calculate_precision(ft_strnstr(str, ".",
					ft_strlen((const char *) str)));
		ft_insert_node(tree, PRECISION, "", precision);
	}
	if (ft_strchr(str, '+'))
		ft_insert_node(tree, PLUSFLAG, "", '+');
	if (ft_strchr(str, '#'))
	{
		if (ft_strchr(str, 'x'))
			ft_insert_node(tree, HASHFLAG, "0x", 0);
		else if (ft_strchr(str, 'X'))
			ft_insert_node(tree, HASHFLAG, "0X", 0);
	}
	if (ft_strchr(str, ' '))
		ft_insert_node(tree, SPACEFLAG, "", ' ');
}

/**
 * Function that insert in a tree all the flags and conversions
 * @param str the string where the format is and use to found all the flags
 * @return binary tree with the flags and conversions on it
*/
t_tree	**ft_store_format(char *str)
{
	int		width;
	char	*format;
	t_tree	**tree;

	if (!str)
		return (NULL);
	tree = (t_tree **) malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	str++;
	format = ft_substr(str, 0, ft_formatlen(str));
	width = ft_calculate_width(format);
	*tree = ft_new_node(PERCENT, "", '%');
	ft_insert_node(tree, CONVERSION, "", find(format, "cpsdiuxX%"));
	ft_insert_node(tree, WIDTH, "", width);
	ft_store_format_aux(format, tree, width);
	free(format);
	return (tree);
}
