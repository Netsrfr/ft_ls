/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfeffer <jpfeffer@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:01:50 by jpfeffer          #+#    #+#             */
/*   Updated: 2017/04/24 18:01:50 by jpfeffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "libraries/ft_printf/ft_printf.h"
# include "libraries/get_next_line/get_next_line.h"
# include <sys/stat.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <sys/ioctl.h>
#include <termios.h>
#include <sys/xattr.h>
#include <sys/acl.h>



typedef struct			s_flag
{
	int	flag;
	int	l;
	int	R;
	int	a;
	int	r;
	int	t;
	int	one;
	int first;
	int start;
}						t_flags;

typedef struct			s_col
{
	int		links;
	size_t	user;
	size_t	group;
	int		f_size;
}						t_col;

static t_flags g_flags;


int						main(int argc, char **argv);
char					**ft_init_test(char *argv);
size_t					ft_count_files(char *argv);

void	ft_sort(char ***argv, int i, int size);
void	ft_rsort(char ***argv, int i, int size);

void	ft_parse_contents(char **argv, int argc);

#endif
