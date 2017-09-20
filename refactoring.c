/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactoring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:49:31 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/09/19 20:55:14 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int			main(int argc, char **argv)
{
	t_opts		*opts;
	char		**tab;
	char		*path;
	int			i;

	i = 0;
	opts = parsing(argc, argv);
	(void)argc;
	path = "/dev/";
	tab = stock_directory(path);
	if (opts->recursive == TRUE)
		tab = press_r(tab, path);
	tab = real_sort(tab);
	if (opts->almost == TRUE)
	{
		tab = almost_all(tab);
		opts->a = TRUE;
	}
	if (opts->a == FALSE)
		tab = counter_a(tab);
	if (opts->r == TRUE)
		tab = do_reverse(tab);
	if (opts->t == TRUE)
		tab = timer(tab);
	if (opts->l == TRUE && opts->m != TRUE)
		tab = do_l(tab, path);
	while (tab[i])
	{
		if (opts->m == TRUE)
			do_m(tab, tab[i], i);
		else if (opts->l == FALSE)
			ft_putendl(tab[i]);
		i++;
	}
	return (0);
}
