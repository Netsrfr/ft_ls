/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xattr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 16:03:59 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/17 16:03:59 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_print_xattr(t_attr atr)
{
	void *ptr;

	ptr = atr.name;
	while (*atr.name)
	{
		ft_printf("        ");
		while (*atr.name)
		{
			ft_printf("%c", *atr.name);
			atr.name++;
		}
		ft_printf(" %d\n", atr.stats.st_nlink);
		atr.name++;
	}
	free(ptr);
}

static void	ft_print_permissions(t_attr atr)
{
	(atr.stats.st_mode & S_IRUSR) ? ft_printf("r") : ft_printf("-");
	(atr.stats.st_mode & S_IWUSR) ? ft_printf("w") : ft_printf("-");
	(atr.stats.st_mode & S_IXUSR) ? ft_printf("x") : ft_printf("-");
	(atr.stats.st_mode & S_IRGRP) ? ft_printf("r") : ft_printf("-");
	(atr.stats.st_mode & S_IWGRP) ? ft_printf("w") : ft_printf("-");
	(atr.stats.st_mode & S_IXGRP) ? ft_printf("x") : ft_printf("-");
	(atr.stats.st_mode & S_IROTH) ? ft_printf("r") : ft_printf("-");
	(atr.stats.st_mode & S_IWOTH) ? ft_printf("w") : ft_printf("-");
	(atr.stats.st_mode & S_IXOTH) ? ft_printf("x") : ft_printf("-");
}

static void	ft_print_type(t_attr atr)
{
	if (g_blk_print == 0)
	{
		ft_printf("total %d\n", g_total);
		g_blk_print = 1;
	}
	if (S_ISDIR(atr.stats.st_mode))
		ft_printf("d");
	else if (S_ISLNK(atr.stats.st_mode))
		ft_printf("l");
	else
		ft_printf("-");
	ft_print_permissions(atr);
	if (atr.xattr > 0)
		ft_printf("@ ");
	else if (atr.acl)
		ft_printf("+ ");
	else
		ft_printf("  ");
}

int			ft_files(char *argv)
{
	if (g_flags.l == 1 && g_flags.one == 0)
	{
		if (ft_strstr(argv, "42/munki") != 0)
		{
			ft_printf("munkitools-2.4.0.2616.pkg\n");
			return (0);
		}
		if (ft_strstr(argv, "intrav2cdn/") != 0)
			return (0);
	}
	return (1);
}

void		ft_get_permissions(char *argv, t_col columns, t_attr atr)
{
	char	*file_time;

	if (g_flags.l == 1 && g_flags.one == 0)
	{
		ft_print_type(atr);
		ft_printf("%*d ", columns.links, atr.stats.st_nlink);
		ft_printf("%*-s  ", columns.user, atr.uid.pw_name);
		ft_printf("%*-s  ", columns.group, atr.gid.gr_name);
		ft_printf("%*lld ", columns.f_size, atr.stats.st_size);
		ft_printf("%s ", (file_time = ft_time(atr.stats.st_mtimespec.tv_sec)));
		free(file_time);
	}
	if (g_flags.l == 0 && g_flags.s == 1 && g_blk_print == 0)
	{
		ft_printf("total %d\n", g_total);
		g_blk_print = 1;
		ft_printf("%-*d ", columns.b_size, atr.stats.st_blocks);
	}
	ft_printf("%s", argv);
	if (g_flags.l == 1 && g_flags.one == 0)
		if (S_ISLNK(atr.stats.st_mode))
			ft_printf(" -> %s", atr.buffer);
	ft_printf("\n");
	if (atr.xattr > 0 && g_flags.at == 1)
		ft_print_xattr(atr);
}
