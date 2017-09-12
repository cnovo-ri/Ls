/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactoring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:49:31 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/09/12 21:15:02 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		bubble_sort(char **tab)
{
	struct stat	s;
	int			i;
	t_bool		permu;
	int			j;
	char		*tmp;
	long		time_tmp;

	i = 0;
	permu = TRUE;
	while (permu)
	{
		permu = FALSE;
		i++;
		j = 0;
		while (j < (tablen(tab) - i))
		{
			if (lstat(tab[j], &s) == -1)
			{
				perror(RED"stat ");
				return;
			}
			if (time_tmp && s.st_ctime > time_tmp)
			{
				permu = TRUE;
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			else if (time_tmp == s.st_ctime && ft_strcmp(tab[j], tab[j + 1]) > 0)
			{
				permu = TRUE;
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			time_tmp = s.st_ctime;
			j++;
		}
	}
}

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

int			tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int			main(int argc, char **argv)
{
	t_opts			*opts;
	char			**tab;
	int				i;

	i = 0;
	opts = parsing(argc, argv);
	(void)argc;
	tab = stock_directory(".");
	if (opts->recursive == TRUE)
		tab = press_r(tab);
	tab = real_sort(tab);
	if (opts->a == FALSE)
		tab = counter_a(tab);
	if (opts->r == TRUE)
		tab = do_reverse(tab);
	if (opts->t == TRUE)
		bubble_sort(tab);
	while (tab[i])
	{
		ft_putendl(tab[i]);
		i++;
	}
	return (0);
}
