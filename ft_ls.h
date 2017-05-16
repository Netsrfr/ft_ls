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

typedef struct			s_attr
{
	struct stat	stats;
	ssize_t		xattr;
	ssize_t		xattr_s;
	acl_t		acl;
	char		*buffer;
	char		*name;

}						t_attr;

t_flags g_flags;
char	**mem;


int						main(int argc, char **argv);
char					**ft_init_contents(char *argv);
size_t					ft_count_files(char *argv);

/*
** sort.c
*/
void	ft_sort(char ***argv, int i, int size);
void	ft_rsort(char ***argv, int i, int size);
void	ft_sort_time(char ***argv, int i, int size);

/*
** path.c
*/
char *ft_add_path(char **argv);
char *ft_add_path_single(char *argv0, char *argv1);

/*
** hidden.c
*/
int	ft_hidden(char **argv, int argc);
int	ft_remove_hidden(char **argv, int argc);

/*
** arguments.c
*/
int	ft_get_arguments(char **argv, int *argc);
void	ft_clear_invalid(char **argv, int *argc, int i);
void	ft_args(char **argv, int *argc);
void	ft_next_arg(char **argv, int argc);

void	ft_parse_contents(char **argv, int argc);
int	ft_parse_flags(char *arg);

#endif
