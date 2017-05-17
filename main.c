
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

char	**ft_init_contents(char *argv)
{
	char	**contents;
	size_t	count;

	count = ft_count_files(argv);
	contents = ft_memalloc(sizeof(char*) * count);
	//mem = contents;
	return (contents);
}

//void	ft_parse_dir(DIR *dir, struct dirent *directory, char **contents, int count)

void	ft_directories(char **argv, DIR *dir)
{
	struct	dirent	*directory;
	char			**contents;
	int				count;
	char			*path;
	char *temp;

	count = 0;
	path = ft_add_path(argv);
	contents = ft_init_contents(path);
	if (strcmp(argv[0], "./ft_ls") == 0)
	{
		contents[0] = ft_strjoin(argv[1], "/");
	}
	else
	{
		printf("\n%s:\n", path);

		temp = ft_strjoin(argv[0], argv[1]);
		contents[0] = ft_strjoin(temp, "/");
		free(temp);
	}
	while (dir != NULL)
	{
		if((directory = readdir(dir)) != NULL)
		{
			contents[count + 1] = ft_strdup(directory->d_name);
			count++;
		}
		else
			break;
	}
	if (g_flags.t == 1)
		ft_sort_time(&contents, 1, count + 1);
	else
		g_flags.r == 1 ? ft_rsort(&contents, 1, count + 1) : ft_sort(&contents, 1, count + 1);
	free(path);
	closedir(dir);
	main((count + 1), contents);

}

void	ft_parse_contents(char **argv, int argc)
{
	DIR		*dir;
	struct stat stats;
	char	*path;

	if(ft_hidden(argv, argc) == 0)
		return ;
	path = ft_add_path(argv);
	lstat(path, &stats);
	if (!(stats.st_mode & S_IRUSR) && g_flags.R == 1)
	{
		if ((stats.st_mode & S_IFMT) == S_IFDIR)
		{
			printf("\n%s:\n", path);
			errno = 13;
			perror(ft_strjoin("ft_ls: ", argv[1]));
		}
	}
	if((stats.st_mode & S_IFMT) == S_IFDIR)
	{
		if (g_flags.R == 1 || strcmp(argv[0], "./ft_ls") == 0)
		{
			if (g_flags.start > 2 && strcmp(argv[0], "./ft_ls") == 0)
			{
				if (g_flags.first == 0)
				{
					printf("%s:\n", path);
					g_flags.first = 1;
				} else
					printf("\n%s:\n", path);
			}
			dir = opendir(path);
			ft_directories(argv, dir);
		}
	}
	//if(dir)
	free(path);
	ft_next_arg(argv, argc);
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

char	*ft_parse_time(char *file_time, char *current, char *result, int i)
{
	while (i <= 3)
	{
		if (file_time[i + 20] != current[i + 20])
		{
			i = 0;
			while (i <= 6)
			{
				result[i] = file_time[i + 4];
				i++;
			}
			while (i <= 11)
			{
				result[i] = file_time[i + 12];
				i++;
			}
			return (result);
		}
		i++;
	}
	i = 0;
	while (i <= 11)
	{
		result[i] = file_time[i + 4];
		i++;
	}
}

char	*ft_time(time_t tse)
{
	char	*file_time;
	char	*current;
	char	*result;
	time_t	now;

	time(&now);
	file_time = ft_strdup(ctime(&tse));
	current = ctime(&now);
	result = ft_memalloc(sizeof(char) * 13);
	result = ft_parse_time(file_time, current, result, 0);
	free(file_time);
	return (result);
}

void	ft_print_xattr()
{

}

void	ft_get_permissions(char *argv, t_col columns, t_attr atr)
{
	struct passwd	uid;
	struct group	gid;
	char *ptr;
	char			*file_time;

	if (g_flags.l == 1)
	{
		uid = *getpwuid(atr.stats.st_uid);
		gid = *getgrgid(atr.stats.st_gid);
		if(S_ISDIR(atr.stats.st_mode))
		printf("d");
		else if (S_ISLNK(atr.stats.st_mode))
			printf("l");
		else
			printf("-");
		(atr.stats.st_mode & S_IRUSR) ? printf("r") : printf("-");
		(atr.stats.st_mode & S_IWUSR) ? printf("w") : printf("-");
		(atr.stats.st_mode & S_IXUSR) ? printf("x") : printf("-");
		(atr.stats.st_mode & S_IRGRP) ? printf("r") : printf("-");
		(atr.stats.st_mode & S_IWGRP) ? printf("w") : printf("-");
		(atr.stats.st_mode & S_IXGRP) ? printf("x") : printf("-");
		(atr.stats.st_mode & S_IROTH) ? printf("r") : printf("-");
		(atr.stats.st_mode & S_IWOTH) ? printf("w") : printf("-");
		(atr.stats.st_mode & S_IXOTH) ? printf("x") : printf("-");
		if (atr.xattr > 0)
			printf("@ ");
		else if (atr.acl)
			printf("+ ");
		else
			printf("  ");
		printf("%*d ", columns.links, atr.stats.st_nlink);
		printf("%*-s  ", columns.user, uid.pw_name);
		printf("%*-s  ", columns.group, gid.gr_name);
		printf("%*lld ", columns.f_size, atr.stats.st_size);
		printf("%s ", file_time = ft_time(atr.stats.st_ctimespec.tv_sec));
		free(file_time);
	}
	printf("%s", argv);
	if (S_ISLNK(atr.stats.st_mode))
	{
		printf(" -> %s", atr.buffer);
		free(atr.buffer);
	}
	printf("\n");
	if (atr.xattr > 0)
	{
		ptr = atr.name;
		while (*atr.name)
		{
			printf("        ");

			while (*atr.name)
			{
				printf("%c", *atr.name);
				atr.name++;
			}
			printf("\n");
			atr.name++;
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
	char	*path;

	i = 1;
	columns.f_size = 0;
	columns.group = 0;
	columns.user = 0;
	columns.links = 0;
	while (i < argc)
	{
		path = ft_add_path_single(argv[0], argv[i]);
		lstat(path, &stats);
		free(path);
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

void	ft_init_attributes(t_attr *attributes, t_col *columns)
{
	attributes->xattr = 0;
	attributes->xattr_s = 0;
	attributes->acl = NULL;
	columns->f_size = 0;
	columns->group = 0;
	columns->links = 0;
	columns->user = 0;

}

void	ft_subsequent(char **argv, int i, t_attr atr, t_col columns)
{
	char	*path;

	path = ft_add_path_single(argv[0], argv[i]);
	lstat(path, &atr.stats);
	atr.xattr = listxattr(path, NULL, 0, 0);

	atr.xattr_s = getxattr(path, atr.name, NULL, 100, 0, 0);
	if (S_ISLNK(atr.stats.st_mode))
	{
		atr.buffer = ft_memalloc(sizeof(char) * 128);
		readlink(path, atr.buffer, 128);
	}
	atr.acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if ((g_flags.a == 1 && argv[i][0] == '.') || argv[i][0] != '.')
	{
		atr.xattr = listxattr(path, NULL, 1024, 0);

		if (atr.xattr > 0)
		{
			atr.name = ft_memalloc(sizeof(char) * atr.xattr + 1);
			listxattr(path, atr.name, atr.xattr, 0);
		}
		ft_get_permissions(argv[i], columns, atr);
	}
	free(path);
}

void	ft_initial(char **argv, int i, t_attr atr, t_col columns)
{
	lstat(argv[i], &atr.stats);
	atr.xattr = listxattr(argv[i], NULL, 0, 0);
	atr.xattr_s = getxattr(argv[i], atr.name, NULL, 100, 0, 0);
	if (S_ISLNK(atr.stats.st_mode))
	{
		atr.buffer = ft_memalloc(sizeof(char) * 128);
		readlink(argv[i], atr.buffer, 128);
	}
	atr.acl = acl_get_link_np(argv[i], ACL_TYPE_EXTENDED);
	if ((atr.stats.st_mode & S_IFMT) != S_IFDIR)
	{
		if ((g_flags.a == 1 && argv[i][0] == '.') || argv[i][0] != '.')
		{
			atr.xattr = listxattr(argv[i], NULL, 1024, 0);
			if (atr.xattr > 0)
			{
				atr.name = ft_memalloc(sizeof(char) * atr.xattr + 1);
				listxattr(argv[i], atr.name, atr.xattr, 0);
			}
			ft_get_permissions(argv[i], columns, atr);
		}
	}
}

void	ft_print_contents_simple(int argc, char **argv)
{
	int		i;
	t_col	columns;
	t_attr	atr;

	i = 1;
	ft_init_attributes(&atr, &columns);
	if (g_flags.l == 1)
		columns = ft_columns(argv, argc, atr.stats);
	while (i < argc)
	{
		if (ft_strcmp(argv[0], "./ft_ls") == 0)
			ft_initial(argv, i, atr, columns);
		else
			ft_subsequent(argv, i, atr, columns);
		i++;
	}
}

struct winsize	ft_max_width(char **argv, int argc, struct winsize win)
{
	int		i;
	size_t	width;

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
	struct	dirent	*directory;
	char			**contents;
	int				count;

	count = 0;
	dir = opendir(".");
	contents = ft_init_contents("./");
		contents[0] = ft_strdup("./");
	while (dir != NULL)
	{
		if((directory = readdir(dir)) != NULL)
		{
			contents[count + 1] = ft_strdup(directory->d_name);
			count++;
		}
		else
			break;
	}
	if (g_flags.t == 1)
		ft_sort_time(&contents, 1, count + 1);
	else
		g_flags.r == 1 ? ft_rsort(&contents, 1, count + 1) : ft_sort(&contents, 1, count + 1);
	closedir(dir);
	main((count + 1), contents);
}

int main(int argc, char **argv)
{
	printf("Test %20\n", "string");
	struct winsize	win;
	char **temp;
	if (ft_strcmp(argv[0], "./ft_ls") == 0)
	{
		temp = ft_memalloc(sizeof(char *) * argc);
		int i;
		i = 0;
		while (i < argc)
		{
			temp[i] = ft_strdup(argv[i]);
			i++;
		}
		argv = temp;
	}
	ioctl(0, TIOCGWINSZ, &win);
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
			argc = ft_remove_hidden(argv, argc);
		if (g_flags.one == 1 || g_flags.l == 1)
			ft_print_contents_simple(argc, argv);
		else
			ft_scale_window(argc, argv, ft_max_width(argv, argc, win));
	}
	if (argc >= 2)
	{
		ft_parse_contents(argv, argc);
		free(argv[1]);
	}
	free(argv[0]);
//	free(argv[1]);
	free(argv);
	//while(1);
	return (0);
}
