/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:28:11 by iestero-          #+#    #+#             */
/*   Updated: 2024/04/23 10:12:07 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_BONUS_H
# define BUILTINS_BONUS_H

int			built_cd(char **args);

int			built_echo(char **args);

int			built_env(void);

int			built_exit(char **args);

int			built_export(char **args);

int			built_pwd(void);

int			built_unset(char **args);

#endif