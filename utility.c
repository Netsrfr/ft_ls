/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 16:23:00 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/17 16:23:00 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t ft_count_files(char *argv)
{
	DIR	*dir;
	size_t count;
	count = 1;

	dir = opendir(argv);
	while (dir != NULL)
	{
		if(readdir(dir) != NULL)
			count++;
		else
			break;
	}
	closedir(dir);
	return (count);
}

int	ft_parse_flags(char *arg)
{
	int	i;

	i = 1;
	g_flags.flag++;
	while(arg[i])
	{
		if (arg[i] == 'l')
			g_flags.l   = 1;
		else if (arg[i] == 'R')
			g_flags.R = 1;
		else if (arg[i] == 'a')
			g_flags.a = 1;
		else if (arg[i] == 'r')
			g_flags.r = 1;
		else if (arg[i] == 't')
			g_flags.t = 1;
		else if (arg[i] == '1')
			g_flags.one = 1;
		else if (arg[i] == '@')
			g_flags.at = 1;
		i++;
	}
	return (0);
}

void	ft_init_attributes(t_attr *attributes, t_col *columns)
{
	attributes->xattr = 0;
	attributes->acl = NULL;
	columns->f_size = 0;
	columns->group = 0;
	columns->links = 0;
	columns->user = 0;
}

char	**ft_init_contents(char *argv)
{
	char	**contents;
	size_t	count;

	count = ft_count_files(argv);
	contents = ft_memalloc(sizeof(char*) * count);
	return (contents);
}

void	ft_print_error(char *argv)
{
	char *err;
	perror(err = ft_strjoin("ft_ls: ", argv));
	free(err);
}
