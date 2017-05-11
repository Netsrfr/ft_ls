
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

char *ft_add_path(char **argv)
{
	char	*temp;

	if (strcmp(argv[0], "./ft_ls") == 0)
		temp = ft_strdup(argv[1]);
	else
	{
		temp = ft_strjoin(argv[0], argv[1]);
	}
	return (temp);
}

int	ft_parse_flags(char *arg)
{
	int	i;

	i = 1;
	g_flags.flag++;
	while(arg[i])
	{
		if (arg[i] == 'l' && g_flags.l == 0)
			g_flags.l = 1;
		else if (arg[i] == 'R'&& g_flags.R == 0)
			g_flags.R = 1;
		else if (arg[i] == 'a'&& g_flags.a == 0)
			g_flags.a = 1;
		else if (arg[i] == 'r'&& g_flags.r == 0)
			g_flags.r = 1;
		else if (arg[i] == 't'&& g_flags.t == 0)
			g_flags.t = 1;
		i++;
	}
	return (0);
}

int	ft_get_arguments(char **argv, int *argc)
{
	int		i;
	i = 1;
	while (i < *argc && argv[i][0] == '-')
	{
		ft_parse_flags(argv[i]);
		i++;
	}
	i = 1;
	if (g_flags.flag != 0)
	{
		while (i + g_flags.flag < *argc)
		{
			argv[i] = ft_strdup(argv[i + g_flags.flag]);
			i++;
		}
		argv[i + 1] = 0;
	}
	*argc -= g_flags.flag;
	return (1);
}

t_cont	*ft_init_contents(char *argv)
{
	t_cont	*contents;
	size_t	i;
	size_t	count;

	i = 0;
	count = ft_count_files(argv);
	contents = ft_memalloc(sizeof(t_cont) * count + 1);
	while (i <= count)
	{
		contents[i].dir = 0;
		i++;
	}
	return (contents);
}

void	ft_init_flags(void)
{
	g_flags.flag = 0;
	g_flags.l = 0;
	g_flags.R = 0;
	g_flags.a = 0;
	g_flags.r = 0;
	g_flags.t = 0;
}

void	ft_clear_invalid(char **argv, int *argc, int i)
{
	perror(argv[i]);
	if (*argc == 2)
		exit (0);
	while (i + 1 < *argc)
	{
		argv[i] = ft_strdup(argv[i + 1]);
		i++;
	}
	argv[i] = 0;
	*argc = *argc - 1;
}

void	ft_args(char **argv, int *argc)
{
	struct stat	*test;
	int			i;

	i = 1;
	test = ft_memalloc(sizeof(struct stat) * 10);
	ft_get_arguments(argv, argc);
	while (i < *argc)
	{
		if (stat(argv[i], test) == -1)
		{
			ft_clear_invalid(argv, argc, i);
			i--;
		}
		i++;
	}
	if (*argc > 2)
		g_flags.r == 1 ? ft_rsort(&argv, 1, *argc) : ft_sort(&argv, 1, *argc);
}

void	ft_rsort(char ***argv, int i, int size)
{
	char *temp;

	if(ft_strcmp((*argv)[i], (*argv)[i + 1]) < 0)
	{
		temp = ft_strdup((*argv)[i + 1]);
		(*argv)[i + 1] = ft_strdup((*argv)[i]);
		(*argv)[i] = ft_strdup(temp);
		free(temp);
		ft_rsort(argv, 1, size);
	}
	if (i + 1 < size - 1)
		ft_rsort(argv, i + 1, size);
}

void	ft_sort(char ***argv, int i, int size)
{
	char *temp;

	if(ft_strcmp((*argv)[i], (*argv)[i + 1]) > 0)
	{
		temp = ft_strdup((*argv)[i]);
		(*argv)[i] = ft_strdup((*argv)[i + 1]);
		(*argv)[i + 1] = ft_strdup(temp);
		free(temp);
		ft_sort(argv, 1, size);
	}
	if (i + 1 < size - 1)
		ft_sort(argv, i + 1, size);
}

void	ft_uid_TEST(t_cont *contents)
{
	struct passwd *uid;
	struct group	*gid;

	printf("file27 = %s\n", contents[26].file);
	stat("test3", &contents[26].stats);
	printf("uid = %u\n", contents[26].stats.st_uid);
	uid = getpwuid(contents[26].stats.st_uid);
	gid = getgrgid(contents[26].stats.st_gid);
	printf("uid = %s\n", uid->pw_name);
	printf("class = %s\n", uid->pw_class);
	printf("dir = %s\n", uid->pw_dir);
	printf("gecos = %s\n", uid->pw_gecos);
	printf("passwd = %s\n", uid->pw_passwd);
	printf("shell = %s\n\n", uid->pw_shell);
	printf("gid = %s\n", gid->gr_name);
	printf("mem0 = %s\n", gid->gr_mem[0]);
	printf("mem1 = %s\n\n", gid->gr_mem[1]);
}

char	**ft_init_test(char *argv)
{
	char	**test;
	size_t	i;
	size_t	count;

	i = 0;
	count = ft_count_files(argv);
	test = ft_memalloc(sizeof(char*) * count + 1);
	return (test);
}



void	ft_next_arg(char **argv, int argc)
{
	int	i;

	i = 1;
	if (argc > 3)
	{
		while (i + 1 < argc)
		{
			argv[i] = ft_strdup(argv[i + 1]);
			i++;
		}
		ft_parse_contents(argv, (argc - 1));
	}
	if (argc == 3)
	{
		argv[1] = ft_strdup(argv[2]);
		ft_parse_contents(argv, (argc - 1));
	}
}

int	ft_hidden(char **argv, int argc)
{
	if (argv[1][0] == '.')
	{
		if (g_flags.a == 1)
		{
			if (ft_strcmp(argv[1], ".") == 0 || ft_strcmp(argv[1], "..") == 0)
			{
				ft_next_arg(argv, argc);
				return (0);
			}
		}
		else if (g_flags.a == 0)
		{
			ft_next_arg(argv, argc);
			return (0);
		}
	}
	return (1);
}

void	ft_directories(char **argv, DIR *dir)
{
	struct	dirent *directory;
	char	**test;
	int		count;

	count = 0;
	test = ft_init_test(ft_add_path(argv));
	if (strcmp(argv[0], "./ft_ls") == 0)
		test[0] = ft_strjoin(argv[1], "/");
	else
	{
		printf("\n%s:\n", ft_add_path(argv));
		test[0] = ft_strjoin(argv[0], argv[1]);
		test[0] = ft_strjoin(test[0], "/");
	}
	while (dir != NULL)
	{
		if((directory = readdir(dir)) != NULL)
		{
			test[count + 1] = ft_strdup(directory->d_name);
			count++;
		}
		else
			break;
	}
	g_flags.r == 1 ? ft_rsort(&test, 1, count + 1) : ft_sort(&test, 1, count + 1);
	main((count + 1), test);
}

void	ft_parse_contents(char **argv, int argc)
{
	DIR		*dir;

	if(ft_hidden(argv, argc) == 0)
		return ;
	if((dir = opendir(ft_add_path(argv))) != '\0' && (g_flags.R == 1 \
 	|| strcmp(argv[0], "./ft_ls") == 0))
	{
		ft_directories(argv, dir);
		closedir(dir);
	}
	ft_next_arg(argv, argc);
}

void	ft_print_contents(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (g_flags.a == 1 && argv[i][0] == '.')
			printf("%s\n", argv[i]);
		if (argv[i][0] != '.')
			printf("%s\n", argv[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc >= 2 && (ft_strcmp(argv[0], "./ft_ls") == 0))
		ft_args(argv, &argc);
	if (argc >= 2 && (ft_strcmp(argv[0], "./ft_ls") != 0))
		ft_print_contents(argc, argv);
	if (argc >= 2)
	{
		ft_parse_contents(argv, argc);
	}
//	ft_uid_TEST(contents);
//	while (i < count)
//	{
//		printf("%s\n", contents[i].file);
//		free(contents[i].file);
//		i++;
//	}
	//free(contents);
	//closedir(dir);
	return (0);
}