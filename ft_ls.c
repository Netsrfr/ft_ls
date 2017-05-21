/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:02:30 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/04/24 18:02:30 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static struct winsize	ft_max_width(char **argv, int argc, struct winsize win)
{
	int			i;
	char		*path;
	size_t		width;
	blkcnt_t	s;
	struct stat	stats;

	i = 1;
	width = 0;
	s = 0;
	while (i < argc)
	{
		width = ft_strlen(argv[i]) > width ? ft_strlen(argv[i]) : width;
		if (g_flags.s == 1)
		{
			lstat((path = ft_add_path(argv)), &stats);
			free(path);
			s = ft_mylog(stats.st_blocks) > s ? ft_mylog(stats.st_blocks) : s;
		}
		i++;
	}
	width = g_flags.s == 1 ? width + s + 1 : width;
	win.ws_ypixel = (unsigned short)(width + 5);
	width = (win.ws_col / (width + 5)) ? (win.ws_col / (width + 5)) : 1;
	win.ws_xpixel = (unsigned short)width;
	return (win);
}

static void				ft_parse_reg(char **argv, int argc, int count)
{
	struct stat	stats;
	char		**contents;
	char		*path;
	int			i;
	int			j;

	i = 1;
	j = 1;
	contents = ft_memalloc(sizeof(char*) * count + 1);
	contents[0] = ft_strdup("./");
	while (i < argc)
	{
		path = ft_add_path_single("./", argv[i]);
		lstat(path, &stats);
		if (S_ISREG(stats.st_mode))
		{
			contents[j] = ft_strdup(argv[i]);
			j++;
		}
		free(path);
		i++;
	}
	main(count + 1, contents);
}

static void				ft_print_files(char **argv, int argc)
{
	struct stat	stats;
	char		*path;
	int			i;
	int			count;

	count = 0;
	i = 1;
	while (i < argc)
	{
		path = ft_add_path_single("./", argv[i]);
		lstat(path, &stats);
		if (S_ISREG(stats.st_mode))
			count++;
		free(path);
		i++;
	}
	ft_parse_reg(argv, argc, count);
}

static void				ft_parse_arg(int argc, char **argv, struct winsize win)
{
	if (argc == 1 && (ft_strcmp(argv[0], "./ft_ls") == 0))
		ft_single();
	if (argc >= 2 && (ft_strcmp(argv[0], "./ft_ls") == 0))
	{
		ft_args(argv, &argc);
		if (argc == 1)
			ft_single();
		else if (g_flags.l == 0)
			ft_print_files(argv, argc);
	}
	if (argc >= 2 && (ft_strcmp(argv[0], "./ft_ls") != 0))
	{
		if (g_flags.a == 0)
			argc = ft_remove_hidden(argv, argc);
		if (g_flags.one == 1 || g_flags.l == 1)
			ft_print_contents_simple(argc, argv);
		else
			ft_scale_window(argc, argv, ft_max_width(argv, argc, win), 1);
	}
	if (argc >= 2)
	{
		ft_parse_contents(argv, argc);
		free(argv[1]);
	}
	free(argv[0]);
}

int						main(int argc, char **argv)
{
	char			**temp;
	struct winsize	win;
	int				i;

	ioctl(0, TIOCGWINSZ, &win);
	if (ft_strcmp(argv[0], "./ft_ls") == 0)
	{
		temp = ft_memalloc(sizeof(char *) * argc);
		i = 0;
		while (i < argc)
		{
			temp[i] = ft_strdup(argv[i]);
			i++;
		}
		argv = temp;
	}
	if (ft_files(argv, argc) == 0)
		return (0);
	ft_parse_arg(argc, argv, win);
	free(argv);
	return (0);
}
