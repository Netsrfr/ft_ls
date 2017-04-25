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

int	ft_read_file(int argc, char **argv, char **map)
{
	int		fd;
	char	*buffer;


	if (argc != 2)
		return (-1);
	if((fd = open(argv[1], O_RDONLY)) == -1)
		return (-2);
	if(!(buffer = ft_memalloc(sizeof(char) * BUFF_SIZE)))
		return (-3);
	if(!(*map = ft_memalloc(sizeof(char) * BUFF_SIZE)))
		return (ft_error_handler(-3, buffer, NULL, NULL));
	while (read(fd, buffer, BUFF_SIZE))
	{
		*map = ft_strjoin(*map, buffer);
		ft_bzero(buffer, BUFF_SIZE);
	}
	close(fd);
	return (0);
}


