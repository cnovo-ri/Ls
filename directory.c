
#include "ls.h"

void		set_perror(char *filename)
{
	ft_putstr_fd("ls: ", 2);
	perror(filename);
}

char		**create_and_fill(DIR *directory)
{
	int				i;
	char			**tab;
	struct dirent	*ptr;
	
	i = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * i + 1)))
		return (NULL);
	while ((ptr = readdir(directory)) != NULL)
	{
		tab[i] = ptr->d_name;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char		**stock_directory(char *path)
{
	DIR				*directory;
	char			**tab;

	if ((directory = opendir(path)) == NULL)
	{
		perror(RED"Error ");
		return (0);
	}
	tab = create_and_fill(directory);
	if (closedir(directory) == -1)
	{
		perror(RED"Error ");
		return (0);
	}
	return (tab);
}

t_bool		is_directory(char *str)
{
	struct stat		st;

	if (stat(str, &st) == 0)
		if (S_ISDIR(st.st_mode))
			return (TRUE);
	return (FALSE);
}

int			main(int argc, char **argv)
{
	t_opts			*opts;
	char			**tab;
	int				i;

	i = 0;
	opts = parsing(argc, argv);
	if (argc < 1)
	{
		ft_putstr(RED"More/less than 1 argument.\n");
		return (0);
	}
	tab = stock_directory(".");
	if (opts->recursive == TRUE)
		tab = press_R(tab);
	if (opts->a == FALSE)
		tab = counter_a(tab);
	if (opts->r == TRUE)
		tab = do_reverse(tab);
	while (tab[i])
	{
		ft_putendl(tab[i]);
		i++;
	}
	return (0);
}
