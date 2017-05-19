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

//:TODO Create reverse optimizer, replace sort requests with wrapper, test large

void	ft_quicksort(char ***argv, int start, int size)
{
	int progress;
	int i;
	int j;
	char *temp;

	if(start < size)
	{
		progress = start;
		i = start;
		j = size;
		while (i < j)
		{
			while (ft_strcmp((*argv)[i], (*argv)[progress]) <= 0 && i < size)
			{
				i++;
			}
			while (ft_strcmp((*argv)[j], (*argv)[progress]) > 0 && j > start)
				j--;

			if (i < j)
			{
				temp = ft_strdup((*argv)[i]);
				free((*argv)[i]);
				(*argv)[i] = ft_strdup((*argv)[j]);
				free((*argv)[j]);
				(*argv)[j] = ft_strdup(temp);
				free(temp);
			}
		}
		temp = ft_strdup((*argv)[j]);
		free((*argv)[j]);
		(*argv)[j] = ft_strdup((*argv)[progress]);
		free((*argv)[progress]);
		(*argv)[progress] = ft_strdup(temp);
		free(temp);
		ft_quicksort(argv, start, j - 1);
		ft_quicksort(argv, j + 1, size);
	}
}

void	ft_sort_large(char ***argv, int size)
{
	int i;
	int	j;

	i = 1;
	j = 100;
	while ((j / 100) * (i * 100) < size)
	{
		while (i * 100 < size)
		{
			if (g_flags.r == 1)
				ft_rsort(argv, 1, i * 100);
			else if (g_flags.t == 1)
				ft_sort_time(argv, 1, i * 100);
			else
				ft_quicksort(argv, 1, i * 100);
			i++;
		}
		j += 100;
	}
}

void	ft_sort_wrapper(char ***argv, int size)
{
	if (size > 3 )
		ft_sort_optimize(argv, 1, size);
	if (size > 250)
		ft_sort_large(argv, size);
	if (g_flags.r == 1)
		ft_rsort(argv, 1, size);
	else if (g_flags.t == 1)
		ft_sort_time(argv, 1, size);
	else
		ft_quicksort(argv, 1, size - 1);

}

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

void	ft_rsort_optimize(char ***argv, int i, int size)
{
	char ***temp;
	int ch;
	int j;

	ch = 126;
	temp = ft_memalloc(sizeof(char**));
	*temp = ft_memalloc(sizeof(char*) * size + 1);
	(*temp)[0] = ft_strdup((*argv)[0]);
	while (ch >= 32)
	{
		j = 1;
		while (j < size)
		{
			if ((*argv)[j][0] == ch)
			{
				(*temp)[i] = ft_strdup((*argv)[j]);
				i++;
			}
			j++;
		}
		ch--;
	}
	*argv = *temp;
}

void	ft_sort_optimize(char ***argv, int i, int size)
{
	char ***temp;
	int ch;
	int j;

	ch = 32;
	temp = ft_memalloc(sizeof(char**));
	*temp = ft_memalloc(sizeof(char*) * size + 1);
	(*temp)[0] = ft_strdup((*argv)[0]);
	while (ch <= 126)
	{
			j = 1;
			while (j < size)
			{
				if ((*argv)[j][0] == ch)
				{
					(*temp)[i] = ft_strdup((*argv)[j]);
					i++;
				}
				j++;
			}
		ch++;
	}
	j = 1;
	while (j < size)
	{
		if ((*argv)[j][0] < 32 || (*argv)[j][0] > 126)
		{
			(*temp)[i] = ft_strdup((*argv)[j]);
			i++;
		}
		j++;
	}
	ft_free_array(argv, size);
	*argv = *temp;
}

void	ft_sequential_sort(char ***argv, int i, int size)
{
	char	*temp;

	while(i + 1 < size)
	{
		if (ft_strcmp((*argv)[i], (*argv)[i + 1]) > 0)
		{
			temp = ft_strdup((*argv)[i]);
			free((*argv)[i]);
			(*argv)[i] = ft_strdup((*argv)[i + 1]);
			free((*argv)[i + 1]);
			(*argv)[i + 1] = ft_strdup(temp);
			free(temp);
			i = 1;
		}
		i++;
	}
}

void	ft_sort(char ***argv, int i, int size)
{
	char	*temp;

	if(i + 1 < size && i < 600)
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
		{
			ft_sort(argv, i + 1, size);
		}

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