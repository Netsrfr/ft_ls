/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 16:05:12 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/17 16:05:12 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_directories(char **argv, DIR *dir)
{
	char			**contents;
	int				count;
	char			*path;
	char			*temp;

	count = 0;
	path = ft_add_path(argv);
	contents = ft_init_contents(path);
	if (strcmp(argv[0], "./ft_ls") == 0)
		contents[0] = ft_strjoin(argv[1], "/");
	else
	{
		ft_printf("\n%s:\n", path);
		temp = ft_strjoin(argv[0], argv[1]);
		contents[0] = ft_strjoin(temp, "/");
		free(temp);
	}
	ft_read_dir(dir, &count, &contents);
	if (g_flags.t == 1)
		ft_sort_time(&contents, 1, count + 1);
	else
		g_flags.r == 1 ? ft_rsort(&contents, 1, count + 1) \
		: ft_sort(&contents, 1, count + 1);
	free(path);
	main((count + 1), contents);
}

void	ft_read_dir(DIR *dir, int *count, char ***contents)
{
	struct dirent	*directory;

	while (dir != NULL && *count < 200)
	{
		if ((directory = readdir(dir)) != NULL)
		{
			(*contents)[*count + 1] = ft_strdup(directory->d_name);
			(*count)++;
		}
		else
			break ;
	}
	closedir(dir);
}

void	ft_parse_contents(char **argv, int argc)
{
	struct stat	stats;
	char		*path;

	if (ft_hidden(argv, argc) == 0)
		return ;
	path = ft_add_path(argv);
	lstat(path, &stats);
	if ((!(stats.st_mode & S_IRUSR)) && g_flags.R == 1)
	{
		if ((stats.st_mode & S_IFMT) == S_IFDIR)
		{
			ft_printf("\n%s:\n", path);
			errno = 13;
			ft_print_error(argv[1]);
		}
	}
	if ((stats.st_mode & S_IFMT) == S_IFDIR && (stats.st_mode & S_IRUSR))
		ft_print_path(argv, path);
	free(path);
	ft_next_arg(argv, argc);
}
