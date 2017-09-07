#include "ls.h"

t_sort		count_it(char **tab)
{
	int		i;
	t_sort	sort;

	i = 0;
	sort.nb_dot = 0;
	sort.nb_up = 0;
	sort.nb_low = 0;
	while (tab[i])
	{
		if (tab[i][0] == '.')
			sort.nb_dot++;
		else if (tab[i][0] >= 65 && tab[i][0] <= 90)
			sort.nb_up++;
		else if (tab[i][0] >= 97 && tab[i][0] <= 122)
			sort.nb_low++;
		i++;
	}
	return (sort);
}

void		set_perror(char *filename)
{
	ft_putstr_fd("ls: ", 2);
	perror(filename);
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
	tab = real_sort(tab);
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
