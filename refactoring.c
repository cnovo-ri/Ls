/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactoring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:49:31 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/09/12 21:16:26 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*void		bubble_sort(char **tab)
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
			if (time_tmp && time_tmp > s.st_mtime)
			{
				permu = TRUE;
				tmp = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = tmp;
			}
			if (time_tmp == s.st_mtime)
			{
				if (ft_strcmp(tab[j - 1], tab[j]) > 0)
				{
					permu = TRUE;
					tmp = tab[j - 1];
					tab[j - 1] = tab[j];
					tab[j] = tmp;
				}
			}
			time_tmp = s.st_mtime;
//			printf("tab[%d] : %s\n", j, tab[j]);
			j++;
		}
	}
}*/

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
	struct stat		s;

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
		timer(tab);
	while (tab[i])
	{
		lstat(tab[i], &s);
		printf("tab[%d] : %s ----> TIME : %ld\n", i, tab[i], s.st_mtime);
		i++;
	}
/*	while (tab[i])
	{
		ft_putendl(tab[i]);
		i++;
	}
*/	return (0);
}
