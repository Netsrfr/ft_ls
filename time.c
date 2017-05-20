/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 10:51:59 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/19 10:51:59 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_compare_time(char **argv, int i, int j)
{
	struct stat	stats;
	struct stat	stats2;
	char		*path;

	path = ft_add_path_single(argv[0], argv[i]);
	lstat(path, &stats);
	free(path);
	path = ft_add_path_single(argv[0], argv[j]);
	lstat(path, &stats2);
	free(path);
	if (stats.st_mtimespec.tv_sec == stats2.st_mtimespec.tv_sec)
	{
		if (stats.st_mtimespec.tv_nsec < stats2.st_mtimespec.tv_nsec)
			return (1);
		else
			return (0);
	}
	if (stats.st_mtimespec.tv_sec < stats2.st_mtimespec.tv_sec)
		return (1);
	else
		return (0);
}

void		ft_qsort_time(char ***argv, int start, int size)
{
	int progress;
	int i;
	int j;

	if (start < size)
	{
		progress = start;
		i = start;
		j = size;
		while (i < j)
		{
			while (ft_compare_time(*argv, i, progress) == 0 && i < size)
				i++;
			while (ft_compare_time(*argv, j, progress) == 1 && j > start)
				j--;
			if (i < j)
				ft_swap(argv, i, j);
		}
		ft_swap(argv, j, progress);
		ft_qsort_time(argv, start, j - 1);
		ft_qsort_time(argv, j + 1, size);
	}
}

void		ft_rqsort_time(char ***argv, int start, int size)
{
	int progress;
	int i;
	int j;

	if (start < size)
	{
		progress = start;
		i = start;
		j = size;
		while (i < j)
		{
			while (ft_compare_time(*argv, i, progress) == 1 && i < size)
			{
				i++;
			}
			while (ft_compare_time(*argv, j, progress) == 0 && j > start)
				j--;
			if (i < j)
				ft_swap(argv, i, j);
		}
		ft_swap(argv, j, progress);
		ft_rqsort_time(argv, start, j - 1);
		ft_rqsort_time(argv, j + 1, size);
	}
}

char		*ft_parse_time(char *file_time, char *current, char *result, int i)
{
	while (i <= 3)
	{
		if (file_time[i + 20] != current[i + 20])
		{
			i = 0;
			while (i <= 11)
			{
				if (i <= 6)
					result[i] = file_time[i + 4];
				else
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

char		*ft_time(time_t tse)
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
