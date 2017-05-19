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

void	ft_large_dir(int *count, char ***contents)
{
	char	**temp;
	int	i;
	int	j;

	i = 1;
	while (i < *count)
	{
		j = 1;
		temp = ft_memalloc(sizeof(char*) * 100);
		temp[0] = ft_strdup((*contents)[0]);
		while (j < 100 && i < *count)
		{
			temp[j] = ft_strdup((*contents)[i]);
			i++;
			j++;
		}
		main(j, temp);
	}
}

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
//	if (ft_strcmp("//System/Library/Frameworks/Python.framework/Versions/2.6/lib/python2.6/test", path) == 0 || ft_strcmp("//Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/share/man/man3", path) == 0 || ft_strcmp("//Applications/Xcode.app/Contents/Developer/Platforms/WatchSimulator.platform/Developer/SDKs/WatchSimulator.sdk/System/Library/PrivateFrameworks/NanoTimeKit.framework", path) == 0 || ft_strcmp("//System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/ATS.framework/Versions/A/Resources/FontInfo", path) == 0)
//	{
//		free(path);
//		ft_next_arg(argv, argc);
//		return ;
//	}
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
