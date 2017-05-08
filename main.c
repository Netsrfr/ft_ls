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
	flags.flag++;
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
		i++;
	}
	return (0);
}

int	ft_get_arguments(char **argv, int *argc)
{
	int		i;
	i = 1;
	while (i < *argc)
	{
		if (argv[i][0] == '-')
			ft_parse_flags(argv[i]);
		i++;
	}
	i = 1;
	if (flags.flag != 0)
		while (i + flags.flag < *argc)
		{
			argv[i] = ft_strdup(argv[i + flags.flag]);
			i++;
		}
	argv[i + 1] = 0;
	*argc -= flags.flag;
	return (1);
}

t_cont	*ft_init_contents(char *argv)
{
	t_cont	*contents;
	size_t	i;
	size_t	count;

	i = 0;
	count = ft_count_files(argv);
	printf("count = %zu\n", count);
	contents = ft_memalloc(sizeof(t_cont) * count + 1);
	while (i <= count)
	{
		contents[i].dir = 1;
		i++;
	}
	return (contents);
}

void	ft_init_flags(void)
{
	flags.flag = 0;
	flags.l = 0;
	flags.R = 0;
	flags.a = 0;
	flags.r = 0;
	flags.t = 0;
}

void	ft_args(char **argv, int argc, DIR **dir, t_cont **contents)
{

	ft_get_arguments(argv, &argc);
	*dir      = opendir(argv[1]);
	*contents = ft_init_contents(argv[1]);
}

t_cont	*ft_ascii_sort(t_cont *contents, int start, int count)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (i < contents[start].len && i < contents[start + 1].len && (contents[start].file[i] < contents[start + 1].file[i]))
		i++;
	if (i == contents[start + 1].len || (contents[start].file[i] > contents[start + 1].file[i]))
	{
		temp = ft_strdup(contents[start].file);
		free(contents[start].file);
		contents[start].file = ft_strdup(contents[start + 1].file);
		free(contents[start + 1].file);
		contents[start + 1].file = ft_strdup(temp);
		free(temp);
		printf("TEST\n");
		contents = ft_ascii_sort(contents, 0, count);
	}
	start++;
	printf("start = %d\n", start);
	if (start + 1 < count)
		contents = ft_ascii_sort(contents, start, count);
	return (contents);
}

//t_cont	*ft_ascii_sort(t_cont *contents, int start, int count)
//{
//	int		i;
//	char	*temp;
//
//	i = 0;
//	while(start + 1 < count)
//	{
//
//		while(contents[start].file[i] && contents[start + 1].file[i])
//		{
//			while ((contents[start].file[i] < contents[start + 1].file[i]))
//				i++;
//			if (contents[start].file[i] && contents[start + 1].file[i] && (contents[start].file[i] > contents[start + 1].file[i]))
//			{
//				temp = ft_strdup(contents[start].file);
//				free(contents[start].file);
//				contents[start].file = ft_strdup(contents[start + 1].file);
//				free(contents[start + 1].file);
//				contents[start + 1].file = ft_strdup(temp);
//				free(temp);
//				printf("TEST\n");
//			}
//			i++;
//		}
//		start++;
//		i = 0;
//	}
//	return (contents);
//}

int main(int argc, char **argv)
{
	DIR		*dir = 0;
	struct	dirent *directory;
	t_cont	*contents = 0;
	int		i;
	int		j;
	char	**arguments;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	ft_init_flags();
	dir = ft_memalloc(sizeof(DIR));
	if (argc >= 2)
		ft_args(argv, argc, &dir, &contents);
	while (dir != NULL)
	{
		if((directory = readdir(dir)) != NULL)
		{
//			printf("directory = %s\n", directory->d_name);
			if((contents[i].file = ft_strdup(directory->d_name)) == 0)
			{
				perror("Error");
				return (-1);
			}
			contents[i].len = ft_strlen(directory->d_name);
//			printf("file = %s\n\n", contents[i].file);
			count++;
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
	i = 0;
	ft_ascii_sort(contents, 0, count);
	while (i < count)
	{
		printf("%s\n", contents[i].file);
		free(contents[i].file);
		i++;
	}
	free(contents);
	closedir(dir);
	return (0);
}