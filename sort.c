/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:37:21 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/16 10:37:21 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


//TODO: Large recursive does not leak unless using -l flag; track leak

void	ft_rsort(char ***argv, int i, int size)
{
	char	*temp;

	if(ft_strcmp((*argv)[i], (*argv)[i + 1]) < 0)
	{
		temp = ft_strdup((*argv)[i + 1]);
		free((*argv)[i + 1]);
		(*argv)[i + 1] = ft_strdup((*argv)[i]);
		(*argv)[i] = ft_strdup(temp);
		free(temp);
		ft_rsort(argv, 1, size);
	}
	if (i + 1 < size - 1)
		ft_rsort(argv, i + 1, size);
}

void	ft_sort(char ***argv, int i, int size)
{
	char	*temp;

	if(i + 1 < size - 1)
	{
		if (ft_strcmp((*argv)[i], (*argv)[i + 1]) > 0)
		{
			temp = ft_strdup((*argv)[i]);
			free((*argv)[i]);
			(*argv)[i] = ft_strdup((*argv)[i + 1]);
			free((*argv)[i + 1]);
			(*argv)[i + 1] = ft_strdup(temp);
			free(temp);
			ft_sort(argv, 1, size);
		}
		if (i + 1 < size - 1)
			ft_sort(argv, i + 1, size);
	}
}

void	ft_sort_time(char ***argv, int i, int size)
{
	char *temp;
	struct stat	stats;
	struct stat stats2;
	char *path;

	if (i + 1 < size)
	{
		path = ft_add_path_single((*argv)[0], (*argv)[i]);
		lstat(path, &stats);
		free(path);
		path = ft_add_path_single((*argv)[0], (*argv)[i + 1]);
		lstat(path, &stats2);
		free(path);
		if (stats.st_mtimespec.tv_sec < stats2.st_mtimespec.tv_sec)
		{
			temp = ft_strdup((*argv)[i]);
			free((*argv)[i]);
			(*argv)[i]     = ft_strdup((*argv)[i + 1]);
			(*argv)[i + 1] = ft_strdup(temp);
			free(temp);
			ft_sort_time(argv, 1, size);
		}
	}
	if (i + 1 < size - 1)
		ft_sort_time(argv, i + 1, size);
}