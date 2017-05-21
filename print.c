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
	if (ft_mylog(stats->st_blocks) > columns.b_size)
		columns.b_size = ft_mylog(stats->st_blocks);
	return (columns);
}

t_col			ft_columns(char **argv, int argc, struct stat stats)
{
	int		i;
	t_col	columns;
	char	*path;

	i = 1;
	columns.f_size = 0;
	columns.b_size = 0;
	columns.group = 0;
	columns.user = 0;
	columns.links = 0;
	while (i < argc)
	{
		path = ft_add_path_single(argv[0], argv[i]);
		lstat(path, &stats);
		g_total += stats.st_blocks;
		free(path);
		columns = ft_parse_stats(columns, &stats);
		i++;
	}
	return (columns);
}
