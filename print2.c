/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 16:03:06 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/17 16:03:06 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_check_link(t_attr *atr, char *path)
{
	if (S_ISLNK(atr->stats.st_mode))
	{
		atr->buffer = ft_memalloc(sizeof(char) * 128);
		readlink(path, atr->buffer, 128);
	}
}

static void	ft_subsequent(char **argv, int i, t_attr atr, t_col columns)
{
	char	*path;

	path = ft_add_path_single(argv[0], argv[i]);
	lstat(path, &atr.stats);
	atr.xattr = listxattr(path, NULL, 0, 0);
	ft_check_link(&atr, path);
	atr.acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if ((g_flags.a == 1 && argv[i][0] == '.') || argv[i][0] != '.')
	{
		atr.xattr = listxattr(path, NULL, 1024, 0);
		if (atr.xattr > 0 && g_flags.at == 1)
		{
			atr.name = ft_memalloc(sizeof(char) * atr.xattr);
			listxattr(path, atr.name, (size_t)atr.xattr, 0);
		}
		atr.uid = *getpwuid(atr.stats.st_uid);
		atr.gid = *getgrgid(atr.stats.st_gid);
		ft_get_permissions(argv[i], columns, atr);
	}
	if (S_ISLNK(atr.stats.st_mode))
		free(atr.buffer);
	acl_free(atr.acl);
	free(path);
}

static void	ft_initial(char **argv, int i, t_attr atr, t_col columns)
{
	lstat(argv[i], &atr.stats);
	atr.xattr = listxattr(argv[i], NULL, 0, 0);
	ft_check_link(&atr, argv[i]);
	atr.acl = acl_get_link_np(argv[i], ACL_TYPE_EXTENDED);
	if ((atr.stats.st_mode & S_IFMT) != S_IFDIR)
	{
		if ((g_flags.a == 1 && argv[i][0] == '.') || argv[i][0] != '.')
		{
			atr.xattr = listxattr(argv[i], NULL, 1024, 0);
			if (atr.xattr > 0 && g_flags.at == 1)
			{
				atr.name = ft_memalloc(sizeof(char) * atr.xattr);
				listxattr(argv[i], atr.name, (size_t)atr.xattr, 0);
			}
			atr.uid = *getpwuid(atr.stats.st_uid);
			atr.gid = *getgrgid(atr.stats.st_gid);
			ft_get_permissions(argv[i], columns, atr);
		}
	}
	if (S_ISLNK(atr.stats.st_mode))
		free(atr.buffer);
	acl_free(atr.acl);
}

void		ft_print_contents_simple(int argc, char **argv)
{
	int		i;
	t_col	columns;
	t_attr	atr;

	i = 1;
	ft_init_attributes(&atr, &columns);
	if (g_flags.l == 1 || g_flags.s == 1)
		columns = ft_columns(argv, argc, atr.stats);
	while (i < argc)
	{
		if (ft_strcmp(argv[0], "./ft_ls") == 0)
			ft_initial(argv, i, atr, columns);
		else
			ft_subsequent(argv, i, atr, columns);
		i++;
	}
	g_total = 0;
	g_blk_print = 0;
}

void		ft_print_path(char **argv, char *path)
{
	DIR		*dir;

	if (g_flags.re == 1 || strcmp(argv[0], "./ft_ls") == 0)
	{
		if (g_flags.start > 2 && strcmp(argv[0], "./ft_ls") == 0)
			ft_printf("\n%s:\n", path);
		if ((dir = opendir(path)))
			ft_directories(argv, dir);
	}
}
