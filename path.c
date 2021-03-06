/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:39:35 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/16 10:39:35 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_swap(char ***argv, int i, int j)
{
	char *temp;

	temp = ft_strdup((*argv)[i]);
	free((*argv)[i]);
	(*argv)[i] = ft_strdup((*argv)[j]);
	free((*argv)[j]);
	(*argv)[j] = ft_strdup(temp);
	free(temp);
}

char	*ft_add_path(char **argv)
{
	char	*temp;

	if (ft_strcmp(argv[0], "./ft_ls") == 0 || argv[1][0] == '/')
		temp = ft_strdup(argv[1]);
	else if (ft_strncmp("..", argv[1], 2) == 0)
		temp = ft_strjoin("/", argv[1]);
	else
	{
		temp = ft_strjoin(argv[0], argv[1]);
	}
	return (temp);
}

char	*ft_add_path_single(char *argv0, char *argv1)
{
	char	*temp;

	if (ft_strcmp(argv0, "./ft_ls") == 0 || argv1[0] == '/')
		temp = ft_strdup(argv1);
	else if (ft_strncmp("..", argv1, 2) == 0)
		temp = ft_strjoin("/", argv1);
	else
		temp = ft_strjoin(argv0, argv1);
	return (temp);
}

size_t	ft_count_files(char *argv)
{
	DIR		*dir;
	size_t	count;

	count = 1;
	dir = opendir(argv);
	while (dir != NULL)
	{
		if (readdir(dir) != NULL)
			count++;
		else
			break ;
	}
	closedir(dir);
	return (count);
}
