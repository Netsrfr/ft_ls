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

static void	ft_qsort(char ***argv, int start, int size)
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
			while (ft_strcmp((*argv)[i], (*argv)[progress]) <= 0 && i < size)
				i++;
			while (ft_strcmp((*argv)[j], (*argv)[progress]) > 0 && j > start)
				j--;
			if (i < j)
				ft_swap(argv, i, j);
		}
		ft_swap(argv, j, progress);
		ft_qsort(argv, start, j - 1);
		ft_qsort(argv, j + 1, size);
	}
}

static void	ft_rqsort(char ***argv, int start, int size)
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
			while (ft_strcmp((*argv)[i], (*argv)[progress]) > 0 && i < size)
				i++;
			while (ft_strcmp((*argv)[j], (*argv)[progress]) <= 0 && j > start)
				j--;
			if (i < j)
				ft_swap(argv, i, j);
		}
		ft_swap(argv, j, progress);
		ft_rqsort(argv, start, j - 1);
		ft_rqsort(argv, j + 1, size);
	}
}

static void	ft_rsort_optimize(char ***argv, int i, int size)
{
	int		ch;
	int		j;

	ch = 126;
	while (ch >= 32)
	{
		j = 1;
		while (j < size)
		{
			if ((*argv)[j][0] == ch)
			{
				ft_swap(argv, i, j);
				i++;
			}
			j++;
		}
		ch--;
	}
}

void		ft_sort_wrapper(char ***argv, int size)
{
	if (size > 3 && g_flags.r == 1 && g_flags.t == 0)
		ft_rsort_optimize(argv, 1, size);
	if (g_flags.r == 1 && g_flags.t == 1)
		ft_rqsort_time(argv, 1, size - 1);
	else if (g_flags.r == 1)
		ft_rqsort(argv, 1, size - 1);
	else if (g_flags.t == 1)
		ft_qsort_time(argv, 1, size - 1);
	else
		ft_qsort(argv, 1, size - 1);
}
