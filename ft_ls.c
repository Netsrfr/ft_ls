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
	int		i;
	size_t	width;

	i = 1;
	width = 0;
	while (i < argc)
	{
		width = ft_strlen(argv[i]) > width ? ft_strlen(argv[i]) : width;
		i++;
	}
	win.ws_ypixel = (unsigned short)(width + 4);
	width = (win.ws_col / (width + 4)) ? (win.ws_col / (width + 4)) : 1;
	win.ws_xpixel = (unsigned short)width;
	return (win);
}

void					ft_single(void)
{
	DIR				*dir;
	struct dirent	*directory;
	char			**c;
	int				count;

	count = 0;
	dir = opendir(".");
	c = ft_init_contents("./");
	c[0] = ft_strdup("./");
	while (dir != NULL)
	{
		if ((directory = readdir(dir)) != NULL)
		{
			c[count + 1] = ft_strdup(directory->d_name);
			count++;
		}
		else
			break ;
	}
	if (g_flags.t == 1)
		ft_sort_time(&c, 1, count + 1);
	else
		g_flags.r == 1 ? ft_rsort(&c, 1, count + 1) : ft_sort(&c, 1, count + 1);
	closedir(dir);
	main((count + 1), c);
}

void					ft_parse_arg(int argc, char **argv, struct winsize win)
{
	if (argc == 1 && (ft_strcmp(argv[0], "./ft_ls") == 0))
		ft_single();
	if (argc >= 2 && (ft_strcmp(argv[0], "./ft_ls") == 0))
	{
		ft_args(argv, &argc);
		if (argc == 1)
			ft_single();
	}
	if (argc >= 2 && (ft_strcmp(argv[0], "./ft_ls") != 0))
	{
		if (g_flags.a == 0)
			argc = ft_remove_hidden(argv, argc);
		if (g_flags.one == 1 || g_flags.l == 1)
			ft_print_contents_simple(argc, argv);
		else
			ft_scale_window(argc, argv, ft_max_width(argv, argc, win));
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
	ft_parse_arg(argc, argv, win);
	free(argv);
	return (0);
}
