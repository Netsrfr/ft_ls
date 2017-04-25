#include <dirent.h>
#include <sys/stat.h>
#include "ft_ls.h"

size_t ft_count_files(char *argv)
{
	DIR	*dir;
	size_t count;
	count = 1;

	dir = opendir(argv);
	while (dir != NULL)
	{
		if(readdir(dir) != NULL)
			count++;
		else
			break;
	}
	closedir(dir);
	return (count);
}

int	ft_parse_flags(char *arg)
{
	int	i;

	i = 1;
	flags.flag = 1;
	while(arg[i])
	{
		if (arg[i] == 'l' && flags.l == 0)
			flags.l = 1;
		else if (arg[i] == 'R'&& flags.R == 0)
			flags.R = 1;
		else if (arg[i] == 'a'&& flags.a == 0)
			flags.a = 1;
		else if (arg[i] == 'r'&& flags.r == 0)
			flags.r = 1;
		else if (arg[i] == 't'&& flags.t == 0)
			flags.t = 1;
		else
			return (-1);
		i++;
	}
	printf("l = %d, R = %d, t = %d\n", flags.l, flags.R, flags.t);
	return (0);
}

int	ft_get_arguments(char **argv, int argc)
{
	int		i;

i = 1;
	if (argv[1][0] == '-')
		if ((ft_parse_flags(argv[1])) == -1)
			return (-1);
//	if (flags.flag == 1)
//		while (i < argc)
//		{
//			argv[i] = ft_strdup(argv[i + 1]);
//			i++;
//		}
	//argv[i + 1] = 0;
	return (1);
}

t_cont	*ft_init_contents(char *argv)
{
	t_cont	*contents;
	size_t	i;
	size_t	count;

	i = 0;
	count = ft_count_files(argv);
	contents = ft_memalloc(sizeof(t_cont*) * count + 1);
	while (i <= count)
	{

		contents[i].dir = 1;
		i++;
	}
	return (contents);
}

int main(int argc, char **argv)
{
	DIR		*dir;
	struct	dirent *directory;
	t_cont	*contents;
	int		i;
	int		j;
	char	**arguments;

	i = 0;
	j = 0;
	if (ft_get_arguments(argv, argc) == -1)
		return (-1);
	dir = opendir(argv[1 + flags.flag]);
	contents = ft_init_contents(argv[1 + flags.flag]);
	printf("argv0 = %s\n", argv[1 + flags.flag]);
	while (dir != NULL)
	{
		if((directory = readdir(dir)) != NULL)
		{
			contents[i].file = ft_strdup(directory->d_name);
			i++;
		}
		else
			break;
	}
	if (dir == NULL)
	{
//		while (contents[j].file)
//		{
//			if (ft_strcmp(contents[j].file, argv[i + flags.flag]) == 0)
//			{
//				contents[j].dir = 0;
//			}
//			j++;
//		}
		perror("Error");
		return (-1);
	}
	stat()
	i = 0;
	while (contents[i].file)
		printf("%s\n", contents[i++].file);
	closedir(dir);
	return (0);
}