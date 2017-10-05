/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactoring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:49:31 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/05 22:52:55 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static char		*get_path(int argc, char *argv)
{
	char	*path;

	path = NULL;
	if (ft_strcmp(argv, "./ls/") > 0)
	{
		ft_putendl(YELLOW"ERROR");
		if (argv[ft_strlen(argv)] != '/')
		{
			path = ft_strdup(ft_strjoin(argv, "/"));
			return (path);
		}
		else
		{
			path = ft_strdup(argv);
			return (path);
		}
	}
	if (argc == 1)
		path = "./";
	return (path);
}

static char		**stock_args(int argc, char **argv)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * argc)))
		return (NULL);
	while (i < argc)
	{
		if (argv[i][0] != '-')
			tmp[j++] = argv[i];
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

int			main(int argc, char **argv)
{
	t_opts		*opts;
	char		**tab;
	char		*path;
	char		**args;
	int			i;
	int			j;

	j = 0;
	opts = parsing(argc, argv);
	args = stock_args(argc, argv);
	printf(YELLOW"argc :%d\n"NORMAL, argc);
	while (args[j])
	{
		printf(YELLOW"argv[%d] : %s\n", j, args[j]);
		j++;
	}
//	while (argv[j])
//	{
//		printf(GREEN"\n\nargv :%s\n\n"NORMAL, argv[j]);
		i = 0;
		path = get_path(argc, argv[j]);
//		printf(GREEN"\npath :%s\n\n"NORMAL, path);
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
//		j++;
//	}
	return (0);
}
