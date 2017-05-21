/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:44:58 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/16 10:44:58 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_hidden(char **argv, int argc)
{
	if (argv[1][0] == '.')
	{
		if (g_flags.a == 1 || argv[1][1] == '/' || argv[1][2] == '/')
		{
			if (ft_strcmp(argv[1], ".") == 0 || ft_strcmp(argv[1], "..") == 0)
			{
				ft_next_arg(argv, argc);
				return (0);
			}
		}
		else if (g_flags.a == 0)
		{
			ft_next_arg(argv, argc);
			return (0);
		}
	}
	return (1);
}

int	ft_remove_hidden(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '.' && argv[i][1] != '/' && argv[i][2] != '/')
		{
			while (i < argc - 1)
			{
				free(argv[i]);
				argv[i] = ft_strdup(argv[i + 1]);
				i++;
			}
			free(argv[i]);
			argc = ft_remove_hidden(argv, argc - 1);
		}
		i++;
	}
	return (argc);
}
