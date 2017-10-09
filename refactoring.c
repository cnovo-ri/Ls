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

static char		*get_path(int argc, char *args)
{
	char	*tmp;

	if (argc != 1 && args[ft_strlen(args)] != '/')
		tmp = ft_strdup(ft_strjoin(args, "/"));
	else
		tmp = ft_strdup(args);
	if (ft_strcmp(args, "./ls") == 0)
		tmp = "./";
	return (tmp);
}

static char		**stock_args(int argc, char **argv)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * argc + 1)))
		return (NULL);
	while (i < argc && argc > 1)
	{
		if (argv[i][0] != '-' && ft_strcmp(argv[i], "./ls") != 0)
			tmp[j++] = argv[i];
		i++;
	}
	if (argc == 1)
		tmp[j++] = argv[i];
	if (argc > 1 && argv[i - 1][0] == '-')
		tmp[j++] = ".";
	tmp[j] = NULL;
	bubble_sort(tmp);
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
/*	printf(YELLOW"argc :%d\n"NORMAL, argc);
	while (args[j])
	{
		printf(YELLOW"args[%d] : %s\n", j, args[j]);
		j++;
	}
	j = 0;
*/	while (args[j])
	{
	//	printf(GREEN"\n\nargv :%s\n\n"NORMAL, argv[j]);
		i = 0;
		path = get_path(argc, args[j]);
		if (j >= 1)
			ft_putstr("\n");
		if (j > 0)
			ft_putstr(ft_strjoin(path,":\n"));
//	printf(GREEN"\npath :%s\n\n"NORMAL, path);
		tab = stock_directory(path);
		if (opts->recursive == TRUE)
			tab = press_r(tab, path);
		tab = real_sort(tab);
		if (ft_strcmp(path, "/dev/") == 0)
			bubble_sort(tab);
		if (opts->a == FALSE)
		{
			if (opts->almost == TRUE)
				tab = almost_all(tab);
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
