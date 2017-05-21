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

# include "libft/libft.h"
# include "libraries/ft_printf/ft_printf.h"
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <sys/xattr.h>
# include <sys/acl.h>

typedef struct			s_flag
{
	int	flag;
	int	l;
	int	re;
	int	a;
	int	r;
	int	t;
	int s;
	int	at;
	int	one;
	int start;
}						t_flags;

typedef struct			s_col
{
	int		links;
	size_t	user;
	size_t	group;
	int		f_size;
	int		b_size;
}						t_col;

typedef struct			s_attr
{
	struct stat		stats;
	ssize_t			xattr;
	acl_t			acl;
	char			*buffer;
	char			*name;
	struct passwd	uid;
	struct group	gid;

}						t_attr;

t_flags					g_flags;
blkcnt_t				g_total;
int						g_blk_print;

int						main(int argc, char **argv);

/*
** arguments.c
*/
int						ft_get_arguments(char **argv, int *argc);
void					ft_clear_invalid(char **argv, int *argc, int i);
void					ft_args(char **argv, int *argc);
void					ft_next_arg(char **argv, int argc);

/*
** directories.c
*/
void					ft_directories(char **argv, DIR *dir);
void					ft_read_dir(DIR *dir, int *count, char ***contents);
void					ft_parse_contents(char **argv, int argc);
void					ft_single(void);

/*
** hidden.c
*/
int						ft_hidden(char **argv, int argc);
int						ft_remove_hidden(char **argv, int argc);

/*
** path.c
*/
void					ft_swap(char ***argv, int i, int j);
char					*ft_add_path(char **argv);
char					*ft_add_path_single(char *argv0, char *argv1);
size_t					ft_count_files(char *argv);

/*
** print.c
*/
t_col					ft_columns(char **argv, int argc, struct stat stats);

/*
** print2.c
*/
void					ft_print_contents_simple(int argc, char **argv);
void					ft_print_path(char **argv, char *path);

/*
** scale.c
*/
void					ft_scale_window
		(int argc, char **argv, struct winsize win, int i);

/*
** sort.c
*/
void					ft_sort_wrapper(char ***argv, int size);

/*
** time.c
*/
void					ft_qsort_time(char ***argv, int start, int size);
void					ft_rqsort_time(char ***argv, int start, int size);
char					*ft_parse_time
						(char *file_time, char *current, char *result, int i);
char					*ft_time(time_t tse);

/*
** utility.c
*/
void					ft_parse_flags(char *arg);
void					ft_init_attributes(t_attr *attributes, t_col *columns);
char					**ft_init_contents(char *argv);
void					ft_print_error(char *argv);

/*
** xattr.c
*/
int						ft_files(char **argv, int argc);
void					ft_get_permissions
						(char *argv, t_col columns, t_attr atr);
#endif
