/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:46:35 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/16 10:46:35 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_get_arguments(char **argv, int *argc)
{
	int		i;
	i = 1;
	while (i < *argc && argv[i][0] == '-')
	{
		ft_parse_flags(argv[i]);
		i++;
	}
	i = 1;
	if (g_flags.flag != 0)
	{
		while (i + g_flags.flag < *argc)
		{
			free(argv[i]);
			argv[i] = ft_strdup(argv[i + g_flags.flag]);
			i++;
		}
		while(i < *argc)
		{
			free(argv[i]);
			i++;
		}
	}
	*argc -= g_flags.flag;
	g_flags.start = *argc;
	return (1);
}

void	ft_clear_invalid(char **argv, int *argc, int i)
{
	perror(ft_strjoin("ft_ls: ", argv[i]));
	if (*argc == 2)
		exit (0);
	while (i + 1 < *argc)
	{
		free(argv[i]);
		argv[i] = ft_strdup(argv[i + 1]);
		i++;
	}
	free(argv[i]);
	*argc = *argc - 1;
}

void	ft_args(char **argv, int *argc)
{
	struct stat	stats;
	int			i;

	i = 1;
	ft_get_arguments(argv, argc);
	while (i < *argc)
	{
		if (stat(argv[i], &stats) == -1)
		{
			ft_clear_invalid(argv, argc, i);
			i--;
		}
		if ((stats.st_mode & S_IRUSR) == 0)
			if ((stats.st_mode & S_IFMT) == S_IFDIR)
			{
				errno = 13;
				perror(ft_strjoin("ft_ls: ", argv[i]));
			}
		i++;
	}
	if (g_flags.t == 1 && *argc > 2)
		ft_sort_time(&argv, 1, *argc);
	if (*argc > 2)
		g_flags.r == 1 ? ft_rsort(&argv, 1, *argc) : ft_sort(&argv, 1, *argc);
}

void	ft_next_arg(char **argv, int argc)
{
	int	i;

	i = 1;
	if (argc > 3)
	{
		while (i + 1 < argc)
		{
			free(argv[i]);
			argv[i] = ft_strdup(argv[i + 1]);
			i++;
		}
		free(argv[i]);
		ft_parse_contents(argv, (argc - 1));
	}
	if (argc == 3)
	{
		free(argv[1]);
		argv[1] = ft_strdup(argv[2]);
		free(argv[2]);
		ft_parse_contents(argv, (argc - 1));
	}
}