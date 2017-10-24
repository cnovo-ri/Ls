/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactoring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:49:31 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/24 07:35:41 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		do_opts(t_opts *opts, char **tab, char *path)
{
	int		i;

	i = 0;
	if (opts->a != TRUE && opts->file_tab != TRUE)
	{
		if (opts->almost == TRUE)
			tab = almost_all(tab);
		else
			tab = counter_a(tab);
	}
	if (opts->t == TRUE)
		tab = timer(tab, path);
	if (opts->r == TRUE)
		tab = do_reverse(tab);
	if (opts->l == TRUE && opts->m != TRUE && opts->one != TRUE)
		do_l(tab, path, opts);
	while (tab[i])
	{
		if (opts->m == TRUE)
			do_m(tab, tab[i], i);
		else if (opts->l == FALSE || opts->one == TRUE)
			ft_putendl(tab[i]);
		i++;
	}
}

int				main(int argc, char **argv)
{
	t_var		*var;
	t_opts		*opts;
	char		**tab;
	char		*path;
	char		**args;
	char		**files;
	int			i;
	int			j;

	j = 0;
	if (!(var = (t_var *)malloc(sizeof(t_var))))
		return (0);
	opts = parsing(argc, argv);
	files = stock_files(argc, argv, var);
	args = stock_args(argc, argv, files);
	path = NULL;
	if (opts->t == TRUE)
		args = timer(args, path);
	if (opts->r == TRUE)
		args = do_reverse(args);
	j = 0;
	if (ft_strcmp(files[0], ".") != 0)
	{
		i = 0;
		path = "./";
		opts->file_tab = TRUE;
		do_opts(opts, files, path);
	}
	if (tablen(args) > 0 && tablen(files) > 0 && ft_strcmp(files[0], ".") != 0)
		ft_putchar('\n');
	opts->file_tab = FALSE;
	while (args[j])
	{
		i = 0;
		path = get_path(argc, args[j]);
		if (j >= 1)
			ft_putstr("\n");
		if (tablen(args) > 1 || (tablen(args) == 1 && tablen(files) > 0 &&
			ft_strcmp(files[0], ".") != 0) || var->k > 0)
			ft_putendl(ft_strjoin(args[j], ":"));
		if (ft_strcmp(args[j], ".") == 0)
			opts->args_dot = TRUE;
		tab = stock_directory(path);
		if (opts->recursive == TRUE)
			press_r(tab, argc, path, opts);
		if (tab != NULL && opts->recursive != TRUE)
		{
			insertion_sort(tab);
			do_opts(opts, tab, path);
		}
		j++;
	}
	free(var);
	return (0);
}
