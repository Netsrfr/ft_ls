/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 16:01:01 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/17 16:01:01 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_put_width(char *argv, unsigned short max, int position)
{
	size_t space;

	space = max - ft_strlen(argv);
	if (position < max - 1)
		while (space-- > 0)
			ft_printf(" ");
}

void			ft_print_scaled(char *argv, char *parent, int *printed)
{
	struct stat	stats;

	if (ft_strcmp(parent, "./ft_ls") != 0)
	{
		if (g_flags.a == 1 && argv[0] == '.')
			ft_printf("%s", argv);
		else if (argv[0] != '.')
			ft_printf("%s", argv);
		else
			(*printed)--;
	}
	else
	{
		stat(argv, &stats);
		if ((stats.st_mode & S_IFMT) != S_IFDIR)
		{
			if (g_flags.a == 1 && argv[0] == '.')
				ft_printf("%s", argv);
			else if (argv[0] != '.')
				ft_printf("%s", argv);
			else
				(*printed)--;
		}
	}
}

void			ft_scale_window(int argc, char **argv, struct winsize win)
{
	int position;
	int printed;
	int height;
	int	i;

	position = 0;
	printed = 0;
	i = 1;
	height = (argc - 1) / win.ws_xpixel ? ((argc - 1) / win.ws_xpixel) + 1 : 1;
	while ((i + (height * position)) < argc)
	{
		while (position < win.ws_xpixel && (i + (height * position)) < argc)
		{
			printed++;
			ft_print_scaled(argv[i + (height * position)], argv[0], &printed);
			ft_put_width(argv[i + height * position], win.ws_ypixel, position);
			position++;
		}
		ft_printf("\n");
		if (printed >= argc - 1)
			break ;
		i++;
		position = 0;
	}
}

static t_col	ft_parse_stats(t_col columns, struct stat *stats)
{
	struct passwd	uid;
	struct group	gid;

	uid = *getpwuid(stats->st_uid);
	gid = *getgrgid(stats->st_gid);
	if (ft_mylog(stats->st_nlink) > columns.links)
		columns.links = ft_mylog(stats->st_nlink);
	if (ft_strlen(uid.pw_name) > columns.user)
		columns.user = ft_strlen(uid.pw_name);
	if (ft_strlen(gid.gr_name) > columns.group)
		columns.group = ft_strlen(gid.gr_name);
	if (ft_mylog(stats->st_size) > columns.f_size)
		columns.f_size = ft_mylog(stats->st_size);
	return (columns);
}

t_col			ft_columns(char **argv, int argc, struct stat stats)
{
	int		i;
	t_col	columns;
	char	*path;

	i = 1;
	columns.f_size = 0;
	columns.group = 0;
	columns.user = 0;
	columns.links = 0;
	while (i < argc)
	{
		path = ft_add_path_single(argv[0], argv[i]);
		lstat(path, &stats);
		total += stats.st_blocks;
		free(path);
		columns = ft_parse_stats(columns, &stats);
		i++;
	}
	return (columns);
}
