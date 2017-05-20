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
	ft_sort_wrapper(&contents, count + 1);
	free(path);
	main((count + 1), contents);
}

void	ft_read_dir(DIR *dir, int *count, char ***contents)
{
	struct dirent	*directory;

	while (dir != NULL)
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
	if ((!(stats.st_mode & S_IRUSR)) && g_flags.re == 1)
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

void	ft_single(void)
{
	DIR				*dir;
	struct dirent	*directory;
	char			**contents;
	int				count;

	count = 0;
	dir = opendir(".");
	contents = ft_init_contents("./");
	contents[0] = ft_strdup("");
	while (dir != NULL)
	{
		if ((directory = readdir(dir)) != NULL)
		{
			contents[count + 1] = ft_strdup(directory->d_name);
			count++;
		}
		else
			break ;
	}
	ft_sort_wrapper(&contents, count + 1);
	closedir(dir);
	main((count + 1), contents);
}
