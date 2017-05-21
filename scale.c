/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 12:05:43 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/05/21 12:05:43 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_put_width(char *argv, unsigned short max, int pos, int width)
{
	size_t space;

	space = max - ft_strlen(argv);
	if (g_flags.s == 1)
		space -= (width + 1);
	if (pos < max - 1)
		while (space-- > 0)
			ft_printf(" ");
}

static void	ft_print(char *argv, char *parent, int *printed, int width)
{
	struct stat	stats;
	char		*path;

	path = ft_add_path_single(parent, argv);
	lstat(path, &stats);
	if (g_flags.a == 1 && argv[0] == '.')
	{
		if (g_flags.s == 1)
			ft_printf("%*d ", width, stats.st_blocks);
		ft_printf("%s", argv);
	}
	else if (argv[0] != '.')
	{
		if (g_flags.s == 1)
			ft_printf("%*d ", width, stats.st_blocks);
		ft_printf("%s", argv);
	}
	else
		(*printed)--;
}

static int	ft_block_width(int argc, char **argv)
{
	struct stat	stats;
	char		*path;
	int			w;
	int			i;

	if (g_flags.s == 0)
		return (0);
	i = 1;
	w = 0;
	while (i < argc)
	{
		path = ft_add_path_single(argv[0], argv[i]);
		lstat(path, &stats);
		w = ft_mylog(stats.st_blocks) > w ? ft_mylog(stats.st_blocks) : w;
		free(path);
		i++;
	}
	return (w);
}

void		ft_scale_window(int argc, char **argv, struct winsize win, int i)
{
	int pos;
	int printed;
	int height;
	int width;

	pos = 0;
	printed = 0;
	width = ft_block_width(argc, argv);
	height = (argc - 1) / win.ws_xpixel ? ((argc - 1) / win.ws_xpixel) + 1 : 1;
	while ((i + (height * pos)) < argc)
	{
		while (pos < win.ws_xpixel && (i + (height * pos)) < argc)
		{
			printed++;
			ft_print(argv[i + (height * pos)], argv[0],
					&printed, width);
			ft_put_width(argv[i + height * pos], win.ws_ypixel, pos, width);
			pos++;
		}
		ft_printf("\n");
		if (printed >= argc - 1)
			break ;
		i++;
		pos = 0;
	}
}
