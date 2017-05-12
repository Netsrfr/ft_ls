
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
		if (arg[i] == 'l')
			g_flags.l   = 1;

		else if (arg[i] == 'R')
			g_flags.R = 1;
		else if (arg[i] == 'a')
			g_flags.a = 1;
		else if (arg[i] == 'r')
			g_flags.r = 1;
		else if (arg[i] == 't')
			g_flags.t = 1;
		else if (arg[i] == '1')
			g_flags.one = 1;
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
	g_flags.start = *argc;
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
	perror(ft_strjoin("ft_ls: ", argv[i]));
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
	struct stat	*stats;
	int			i;

	i = 1;
	stats = ft_memalloc(sizeof(struct stat) * 10);
	ft_get_arguments(argv, argc);
	while (i < *argc)
	{
		if (stat(argv[i], stats) == -1)
		{
			ft_clear_invalid(argv, argc, i);
			i--;
		}
		if ((stats->st_mode & S_IRUSR) == 0)
			if ((stats->st_mode & S_IFMT) == S_IFDIR)
			{
				errno = 13;
				perror(ft_strjoin("ft_ls: ", argv[i]));
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

void	ft_uid_TEST(char **argv)
{
	struct passwd *uid;
	struct group	*gid;
	struct stat		*stats;
	struct stat		*stats2;
	printf("irwxu = %u\n", S_IRWXU);

	stats = ft_memalloc(sizeof(struct stat));
	//printf("file3 = %s\n", contents[26].file);
	lstat(argv[1], stats);
	printf("uid = %u\n", stats->st_uid);
	printf("mode = %u\n", stats->st_mode);
	printf("irwxu = %u\n", stats->st_mode & S_IRWXU);
	printf("irusr = %u\n", stats->st_mode & S_IRUSR);
	printf("iwusr = %u\n", stats->st_mode & S_IWUSR);
	printf("ixusr = %u\n", stats->st_mode & S_IXUSR);
	printf("isdir = %u\n", (stats->st_mode & S_IFMT) == S_IFDIR);


	uid = getpwuid(stats->st_uid);
	gid = getgrgid(stats->st_gid);
	printf("uid = %s\n", uid->pw_name);
	printf("class = %s\n", uid->pw_class);
	printf("dir = %s\n", uid->pw_dir);
	printf("gecos = %s\n", uid->pw_gecos);
	printf("passwd = %s\n", uid->pw_passwd);
	printf("shell = %s\n\n", uid->pw_shell);
	printf("gid = %s\n", gid->gr_name);
	printf("mem0 = %s\n", gid->gr_mem[0]);
	//printf("mem1 = %s\n\n", gid->gr_mem[1]);
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
	struct stat *stats;
	if(ft_hidden(argv, argc) == 0)
		return ;
	stats = ft_memalloc(sizeof(struct stat));
	lstat(ft_add_path(argv), stats);
	if (!(stats->st_mode & S_IRUSR))
	{
		if ((stats->st_mode & S_IFMT) == S_IFDIR)
		{
			printf("\n%s:\n", ft_add_path(argv));
			errno = 13;
			perror(ft_strjoin("ft_ls: ", argv[1]));
		}
	}
	if((dir = opendir(ft_add_path(argv))) != '\0' && (g_flags.R == 1 \
 	|| strcmp(argv[0], "./ft_ls") == 0))
	{
		if (g_flags.start > 2 && strcmp(argv[0], "./ft_ls") == 0)
		{
			if (g_flags.first == 0)
			{
				printf("%s:\n", ft_add_path(argv));
				g_flags.first = 1;
			}
			else
				printf("\n%s:\n", ft_add_path(argv));
		}
		ft_directories(argv, dir);
		closedir(dir);
	}
	ft_next_arg(argv, argc);
}


int	ft_temp(char **argv, int argc)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '.')
		{
			while (i < argc - 1)
			{
				argv[i] = ft_strdup(argv[i + 1]);
				i++;
			}
			argc = ft_temp(argv, argc - 1);
		}
		i++;
	}
	return(argc);
}

void	ft_print_scaled(char *argv, char *parent, int *printed)
{
	struct stat	stats;

	if (ft_strcmp(parent, "./ft_ls") != 0)
	{
		if (g_flags.a == 1 && argv[0] == '.')
			printf("%s", argv);
		else if (argv[0] != '.')
			printf("%s", argv);
		else
			(*printed)--;
	}
	else
	{
		stat(argv, &stats);
		if ((stats.st_mode & S_IFMT) != S_IFDIR)
		{
			if (g_flags.a == 1 && argv[0] == '.')
				printf("%s", argv);
			else if (argv[0] != '.')
				printf("%s", argv);
			else
				(*printed)--;
		}
	}
}

void	ft_put_width(char *argv, unsigned short max, int position)
{
	size_t space;

	space = max - ft_strlen(argv);
	if (position < max - 1)
		while (space-- > 0)
			printf(" ");
}

void	ft_scale_window(int argc, char **argv, struct winsize win)
{
	int position;
	int printed;
	int height;
	int	i;

	position = 0;
	printed = 0;
	i = 1;
	height = (argc - 1) / win.ws_xpixel ? ((argc - 1) / win.ws_xpixel) + 1 : 1;
	while ((i + (height * position)) < argc)
	{
		while (position < win.ws_xpixel && (i + (height * position)) < argc)
		{
			printed++;
			ft_print_scaled(argv[i + (height * position)], argv[0], &printed);
			ft_put_width(argv[i + height * position], win.ws_ypixel, position);
			position++;
		}
		printf("\n");
		if(printed >= argc - 1)
			break;
		i++;
		position = 0;
	}
}

void	ft_print_contents_simple(int argc, char **argv)
{
	int	i;
	struct stat	stats;


	i = 1;
	stat(argv[i], &stats);
	while (i < argc)
	{
		if (ft_strcmp(argv[0], "./ft_ls") != 0)
		{
			if (g_flags.a == 1 && argv[i][0] == '.')
				printf("%s\n", argv[i]);
			if (argv[i][0] != '.')
				printf("%s\n", argv[i]);
		}
		else
		{
			stat(argv[i], &stats);
			if ((stats.st_mode & S_IFMT) != S_IFDIR)
			{
				if (g_flags.a == 1 && argv[i][0] == '.')
					printf("%s\n", argv[i]);
				if (argv[i][0] != '.')
					printf("%s\n", argv[i]);
			}
		}
		i++;
	}
}

struct winsize	ft_max_width(char **argv, int argc, struct winsize win)
{
	int		i;
	size_t	width;
	size_t	height;

	i = 1;
	width = 0;
	while(i < argc)
	{
		width = ft_strlen(argv[i]) > width ? ft_strlen(argv[i]) : width;
		i++;
	}
	win.ws_ypixel = (unsigned short)(width + 4);
	width = (win.ws_col / (width + 4)) ? (win.ws_col / (width + 4)) : 1;
	win.ws_xpixel = (unsigned short)width;
	return (win);
}


void	ft_single(void)
{
	DIR				*dir;
	struct	dirent *directory;
	char	**test;
	int		count;

	count = 0;
	dir = opendir(".");
	test = ft_init_test("./");
		test[0] = ft_strdup("./");
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

int main(int argc, char **argv)
{
	int i;
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	i = 1;
	if (argc == 1 && (ft_strcmp(argv[0], "./ft_ls") == 0))
	{
		ft_single();
	}
	if (argc >= 2 && (ft_strcmp(argv[0], "./ft_ls") == 0))
	{
		ft_args(argv, &argc);
		if (argc == 1)
			ft_single();
	}
	if (argc >= 2 && (ft_strcmp(argv[0], "./ft_ls") != 0))
	{
		if (g_flags.a == 0)
			argc = ft_temp(argv, argc);
		if (g_flags.one == 1)
			ft_print_contents_simple(argc, argv);
		else
			ft_scale_window(argc, argv, ft_max_width(argv, argc, win));
	}
	if (argc >= 2)
	{
		ft_parse_contents(argv, argc);
	}
//	ft_uid_TEST(argv);
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



