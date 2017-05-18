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

	if(i + 1 < size)
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

char	*ft_parse_time(char *file_time, char *current, char *result, int i)
{
	while (i <= 3)
	{
		if (file_time[i + 20] != current[i + 20])
		{
			i = 0;
			while (i <= 6)
			{
				result[i] = file_time[i + 4];
				i++;
			}
			while (i <= 11)
			{
				result[i] = file_time[i + 12];
				i++;
			}
			return (result);
		}
		i++;
	}
	i = 0;
	while (i <= 11)
	{
		result[i] = file_time[i + 4];
		i++;
	}
	return (result);
}

char	*ft_time(time_t tse)
{
	char	*file_time;
	char	*current;
	char	*result;
	time_t	now;

	time(&now);
	file_time = ft_strdup(ctime(&tse));
	current = ctime(&now);
	result = ft_memalloc(sizeof(char) * 13);
	result = ft_parse_time(file_time, current, result, 0);
	free(file_time);
	return (result);
}