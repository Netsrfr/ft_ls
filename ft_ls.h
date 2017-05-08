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
#define FT_LS_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "libraries/get_next_line/get_next_line.h"

typedef struct			s_flag
{
	int	flag;
	int	l;
	int	R;
	int	a;
	int	r;
	int	t;
}						g_flags;

typedef struct			s_cont
{
	char	*file;
	size_t	len;
	int		dir;
}						t_cont;

g_flags flags;

#endif
