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

static void	ft_ls_flags(char arg)
{
	if (arg == 'l')
		g_flags.l = 1;
	else if (arg == 'R')
		g_flags.re = 1;
	else if (arg == 'a')
		g_flags.a = 1;
	else if (arg == 'r')
		g_flags.r = 1;
	else if (arg == 't')
		g_flags.t = 1;
	else if (arg == '1')
		g_flags.one = 1;
	else if (arg == '@')
		g_flags.at = 1;
	else if (arg == 's')
		g_flags.s = 1;
	else
		ft_printf("flag '%c' invalid: resuming with valid flag(s)\n", arg);
}

void		ft_parse_flags(char *arg)
{
	int	i;

	i = 1;
	g_flags.flag++;
	while (arg[i])
	{
		ft_ls_flags(arg[i]);
		i++;
	}
}

void		ft_init_attributes(t_attr *attributes, t_col *columns)
{
	attributes->xattr = 0;
	attributes->acl = NULL;
	columns->f_size = 0;
	columns->group = 0;
	columns->links = 0;
	columns->user = 0;
}

char		**ft_init_contents(char *argv)
{
	char	**contents;
	size_t	count;

	count = ft_count_files(argv);
	contents = ft_memalloc(sizeof(char*) * count);
	return (contents);
}

void		ft_print_error(char *argv)
{
	char *err;

	perror(err = ft_strjoin("ft_ls: ", argv));
	free(err);
}
