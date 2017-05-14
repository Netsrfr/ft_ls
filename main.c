
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

char *ft_add_path_single(char *argv0, char *argv1)
{
	char	*temp;

	if (strcmp(argv0, "./ft_ls") == 0)
		return (argv1);
	else
	{
		temp = ft_strjoin(argv0, argv1);
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
	ft_printf("irwxu = %u\n", S_IRWXU);

	stats = ft_memalloc(sizeof(struct stat));
	//ft_printf("file3 = %s\n", contents[26].file);
	lstat(argv[1], stats);
	ft_printf("uid = %u\n", stats->st_uid);
	ft_printf("mode = %u\n", stats->st_mode);
	ft_printf("irwxu = %u\n", stats->st_mode & S_IRWXU);
	ft_printf("irusr = %u\n", stats->st_mode & S_IRUSR);
	ft_printf("iwusr = %u\n", stats->st_mode & S_IWUSR);
	ft_printf("ixusr = %u\n", stats->st_mode & S_IXUSR);
	ft_printf("isdir = %u\n", (stats->st_mode & S_IFMT) == S_IFDIR);


	uid = getpwuid(stats->st_uid);
	gid = getgrgid(stats->st_gid);
	ft_printf("uid = %s\n", uid->pw_name);
	ft_printf("class = %s\n", uid->pw_class);
	ft_printf("dir = %s\n", uid->pw_dir);
	ft_printf("gecos = %s\n", uid->pw_gecos);
	ft_printf("passwd = %s\n", uid->pw_passwd);
	ft_printf("shell = %s\n\n", uid->pw_shell);
	ft_printf("gid = %s\n", gid->gr_name);
	ft_printf("mem0 = %s\n", gid->gr_mem[0]);
	//ft_printf("mem1 = %s\n\n", gid->gr_mem[1]);
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

void	ft_sort_time(char ***argv, int i, int size)
{
	char *temp;
	struct stat	stats;
	struct stat stats2;



	if (i + 1 < size)
	{
		//printf("TEST\n");
		lstat(ft_add_path_single((*argv)[0], (*argv)[i]), &stats);
		lstat(ft_add_path_single((*argv)[0], (*argv)[i + 1]), &stats2);
		if (stats.st_mtimespec.tv_sec < stats2.st_mtimespec.tv_sec)
		{
			temp = ft_strdup((*argv)[i]);
			(*argv)[i]     = ft_strdup((*argv)[i + 1]);
			(*argv)[i + 1] = ft_strdup(temp);
			free(temp);
			ft_sort_time(argv, 1, size);
		}

	}
		if (i + 1 < size - 1)
			ft_sort_time(argv, i + 1, size);

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
		ft_printf("\n%s:\n", ft_add_path(argv));
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
	ft_sort_time(&test, 1, count + 1);
	//g_flags.r == 1 ? ft_rsort(&test, 1, count + 1) : ft_sort(&test, 1, count + 1);
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
			ft_printf("\n%s:\n", ft_add_path(argv));
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
				ft_printf("%s:\n", ft_add_path(argv));
				g_flags.first = 1;
			}
			else
				ft_printf("\n%s:\n", ft_add_path(argv));
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
			ft_printf("%s", argv);
		else if (argv[0] != '.')
			ft_printf("%s", argv);
		else
			(*printed)--;
	}
	else
	{
		stat(argv, &stats);
		if ((stats.st_mode & S_IFMT) != S_IFDIR)
		{
			if (g_flags.a == 1 && argv[0] == '.')
				ft_printf("%s", argv);
			else if (argv[0] != '.')
				ft_printf("%s", argv);
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
			ft_printf(" ");
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
		ft_printf("\n");
		if(printed >= argc - 1)
			break;
		i++;
		position = 0;
	}
}

char	*ft_time(time_t tse)
{
	char	*file_time;
	char	*current;
	char	*temp;
	time_t	now;
	int		i;

	time(&now);
	file_time = ft_strdup(ctime(&tse));
	current = ctime(&now);
	temp = ft_memalloc(sizeof(char) * 13);
	i = 0;
	while (i <= 3)
	{
		if (file_time[i + 20] != current[i + 20])
		{
			i = 0;
			while (i <= 6)
			{
				temp[i] = file_time[i + 4];
				i++;
			}
			while (i <= 11)
			{
				temp[i] = file_time[i + 12];
				i++;
			}
			return (temp);
		}
		i++;
	}
	i = 0;
	while (i <= 11)
	{
		temp[i] = file_time[i + 4];
		i++;
	}
	return (temp);
}

void	ft_print_xattr()
{

}

void	ft_get_permissions(char *argv, struct stat stats, t_col columns, ssize_t xattr, acl_t acl, char *buffer, ssize_t test, ssize_t s, char *name)
{
	struct passwd	uid;
	struct group	gid;
	char *ptr;

	if (g_flags.l == 1)
	{
		uid = *getpwuid(stats.st_uid);
		gid = *getgrgid(stats.st_gid);
		if(S_ISDIR(stats.st_mode))
		ft_printf("d");
		else if (S_ISLNK(stats.st_mode))
			ft_printf("l");
		else
			ft_printf("-");
		(stats.st_mode & S_IRUSR) ? ft_printf("r") : ft_printf("-");
		(stats.st_mode & S_IWUSR) ? ft_printf("w") : ft_printf("-");
		(stats.st_mode & S_IXUSR) ? ft_printf("x") : ft_printf("-");
		(stats.st_mode & S_IRGRP) ? ft_printf("r") : ft_printf("-");
		(stats.st_mode & S_IWGRP) ? ft_printf("w") : ft_printf("-");
		(stats.st_mode & S_IXGRP) ? ft_printf("x") : ft_printf("-");
		(stats.st_mode & S_IROTH) ? ft_printf("r") : ft_printf("-");
		(stats.st_mode & S_IWOTH) ? ft_printf("w") : ft_printf("-");
		(stats.st_mode & S_IXOTH) ? ft_printf("x") : ft_printf("-");
		if (xattr)
			ft_printf("@ ");
		else if (acl)
			ft_printf("+ ");
		else
			ft_printf("  ");
		ft_printf("%*d ", columns.links, stats.st_nlink);
		ft_printf("%*-s  ", columns.user, uid.pw_name);
		ft_printf("%*-s  ", columns.group, gid.gr_name);
		ft_printf("%*lld ", columns.f_size, stats.st_size);
		ft_printf("%s ", ft_time(stats.st_ctimespec.tv_sec));
	}
	ft_printf("%s", argv);
	if (S_ISLNK(stats.st_mode))
	{
		printf(" -> %s", buffer);
		free(buffer);
	}
	printf("\n");
	if (test > 0)
	{
		ptr = name;
		while (*name)
		{
			printf("        ");

			while (*name)
			{
				printf("%c", *name);
				name++;
			}
			printf("\n");
			name++;
		}
		free(ptr);
	}


}

t_col	ft_columns(char **argv, int argc, struct stat stats)
{
	int	i;
	struct passwd	uid;
	struct group	gid;
	t_col	columns;

	i = 1;
	columns.f_size = 0;
	columns.group = 0;
	columns.user = 0;
	columns.links = 0;
	while (i < argc)
	{
		lstat(ft_add_path_single(argv[0], argv[i]), &stats);
		uid = *getpwuid(stats.st_uid);
		gid = *getgrgid(stats.st_gid);
		if (ft_mylog(stats.st_nlink) > columns.links)
			columns.links = ft_mylog(stats.st_nlink);
		if (ft_strlen(uid.pw_name) > columns.user)
			columns.user = ft_strlen(uid.pw_name);
		if (ft_strlen(gid.gr_name) > columns.group)
			columns.group = ft_strlen(gid.gr_name);
		if (ft_mylog(stats.st_size) > columns.f_size)
			columns.f_size = ft_mylog(stats.st_size);
		i++;
	}
	return (columns);
}

void	ft_print_contents_simple(int argc, char **argv)
{
	int	i;
	struct stat	stats;
	t_col	columns;
	ssize_t xattr;
	acl_t acl = NULL;
	char *buffer;
	char *name;
	ssize_t s = 0;
	ssize_t test = 0;

	i = 1;
	if (g_flags.l == 1)
		columns = ft_columns(argv, argc, stats);
	while (i < argc)
	{
//		ft_get_permissions(argv[i]);
		if (ft_strcmp(argv[0], "./ft_ls") != 0)
		{
			lstat(ft_add_path_single(argv[0], argv[i]), &stats);
			xattr = listxattr(ft_add_path_single(argv[0], argv[i]), NULL, 0, 0);

			s = getxattr(ft_add_path_single(argv[0], argv[i]), name, NULL, 100, 0, 0);
			if (S_ISLNK(stats.st_mode))
			{
				buffer = ft_memalloc(sizeof(char) * 128);
				readlink(ft_add_path_single(argv[0], argv[i]), buffer, 128);
			}
			acl = acl_get_link_np(ft_add_path_single(argv[0], argv[i]), ACL_TYPE_EXTENDED);
			if ((g_flags.a == 1 && argv[i][0] == '.') || argv[i][0] != '.')
			{
				test = listxattr(ft_add_path_single(argv[0], argv[i]), NULL, 1024, 0);

				if (test > 0)
				{
				//	printf("name malloc = %d\n", test);
					name = ft_memalloc(sizeof(char) * test + 1);
					listxattr(ft_add_path_single(argv[0], argv[i]), name, test, 0);
				}
				ft_get_permissions(argv[i], stats, columns, xattr, acl, buffer,
								   test, s, name);//ft_printf("%s\n", argv[i]);
			}
//			if (argv[i][0] != '.')
//				ft_printf("%s\n", argv[i]);
		}
		else
		{
			lstat(argv[i], &stats);
			xattr = listxattr(argv[i], NULL, 0, 0);

			s = getxattr(argv[i], name, NULL, 100, 0, 0);
			if (S_ISLNK(stats.st_mode))
			{
				buffer = ft_memalloc(sizeof(char) * 128);
				readlink(argv[i], buffer, 128);

			}
			acl = acl_get_link_np(argv[i], ACL_TYPE_EXTENDED);
			if ((stats.st_mode & S_IFMT) != S_IFDIR)
			{
				if ((g_flags.a == 1 && argv[i][0] == '.') || argv[i][0] != '.')
				{
					test = listxattr(argv[i], NULL, 1024, 0);
					if (test > 0)
					{
		//				printf("name malloc = %d\n", test);

						name = ft_memalloc(sizeof(char) * test + 1);
						listxattr(argv[i], name, test, 0);
					}
					ft_get_permissions(argv[i], stats, columns, xattr, acl,
									   buffer, test, s,
									   name);//ft_printf("%s\n", argv[i]);
				}
//				if (argv[i][0] != '.')
//					ft_printf("%s\n", argv[i]);
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
	//ft_sort_time(&test, 1, count + 1);
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
//		ft_printf("%s\n", contents[i].file);
//		free(contents[i].file);
//		i++;
//	}
	//free(contents);
	//closedir(dir);
	return (0);
}



