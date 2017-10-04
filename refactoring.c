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

static char		*get_path(int argc, char *argv)
{
	char	*path;

	if (!(path = (char *)malloc(sizeof(char) * 255)))
		return (NULL);
	if (argc == 1 && ft_strcmp(argv, "./ls/") > 0)
	{
		if (argv[ft_strlen(argv)] != '/')
			path = ft_strjoin(argv, "/");
		else
			path = argv;
	}
	else
		path = "./";
	return (path);
}

int			main(int argc, char **argv)
{
	t_opts		*opts;
	char		**tab;
	char		*path;
	int			i;
	int			j;

	j = 0;
	opts = parsing(argc, argv);
//	printf(YELLOW"argc :%d\n", argc);
	while (argv[j])
	{
		i = 0;
		path = get_path(argc, argv[j]);
		tab = stock_directory(path);
		if (opts->recursive == TRUE)
			tab = press_r(tab, path);
		tab = real_sort(tab);
		if (opts->a == FALSE)
		{
			if (opts->almost == TRUE)
			{
				ft_putendl(CYAN"A");
				tab = almost_all(tab);
			}
			else
				tab = counter_a(tab);
		}
		if (opts->r == TRUE)
			tab = do_reverse(tab);
		if (opts->t == TRUE)
			tab = timer(tab);
		if (opts->l == TRUE && opts->m != TRUE)
			do_l(tab, path);
		while (tab[i])
		{
			if (opts->m == TRUE)
				do_m(tab, tab[i], i);
			else if (opts->l == FALSE)
				ft_putendl(tab[i]);
			i++;
		}
		j++;
	}
	return (0);
}
