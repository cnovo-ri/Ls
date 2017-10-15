/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactoring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:49:31 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/16 01:38:22 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		do_opts(t_opts *opts, char **tab, char *path)
{
	int		i;

	i = 0;
	if (opts->a != TRUE)
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
	files = stock_files(argc, argv);
	free(var->tmp);
	args = stock_args(argc, argv, files);
	free(var->error_tab);
	//	printf(YELLOW"argc :%d\n"NORMAL, argc);
	path = NULL;
	if (opts->t == TRUE)
		args = timer(args, path);
	if (opts->r == TRUE)
		args = do_reverse(args);
/*	while (args[j])
	{
		printf(CYAN"args[%d] : %s\n"NORMAL, j, args[j]);
		j++;
	}
	j = 0;
	while (files[j])
	{
		printf(YELLOW"files[%d] : %s\n"NORMAL, j, files[j]);
		j++;
	}
	j = 0;
*/	if (ft_strcmp(files[0], ".") != 0)
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
//			printf(GREEN"\n\nargvs :%s\n\nj :%d\n"NORMAL, args[j], j);
		i = 0;
		path = get_path(argc, args[j]);
		if (j >= 1)
			ft_putstr("\n");
		if (tablen(args) > 1 || (tablen(args) == 1 && tablen(files) > 0 &&
			ft_strcmp(files[0], ".") != 0))
			ft_putstr(ft_strjoin(args[j],":\n"));
//		printf(GREEN"\npath :%s\n\n"NORMAL, path);
		tab = stock_directory(path);
		if (opts->recursive == TRUE)
			tab = press_r(tab, path);
		ft_putendl(BLUE"NOT TAB"NORMAL);
		bubble_sort(tab);
		//tab = real_sort(tab);
/*		if (ft_strcmp(path, "/dev/") == 0)
			bubble_sort(tab);
*/		if (tab != NULL)
			do_opts(opts, tab, path);
		j++;
	}
	free(var);
	return (0);
}
