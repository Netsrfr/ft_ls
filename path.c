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

	if (strcmp(argv[0], "./ft_ls") == 0)
		temp = ft_strdup(argv[1]);
	else
	{
		temp = ft_strjoin(argv[0], argv[1]);
	}
	return (temp);
}

char	*ft_add_path_single(char *argv0, char *argv1)
{
	char	*temp;

	if (strcmp(argv0, "./ft_ls") == 0)
		return (argv1);
	else
	{
		temp = ft_strjoin(argv0, argv1);
	}
	return (temp);
}
