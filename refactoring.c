/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactoring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:49:31 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/15 02:27:09 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*get_path(int argc, char *args)
{
	char		*tmp;

	if (argc != 1 && args[ft_strlen(args)] != '/' && is_directory(args) == TRUE)
		tmp = ft_strdup(ft_strjoin(args, "/"));
	else
		tmp = ft_strdup(args);
	if (ft_strcmp(args, "./ft_ls") == 0)
		tmp = "./";
	return (tmp);
}

static t_var	*init_vars(t_var *var, int argc)
{
	if (!(var->tmp = (char **)malloc(sizeof(char *) * argc + 1)))
		return (NULL);
	if (!(var->error_tab = (char **)malloc(sizeof(char *) * argc + 1)))
		return (NULL);
	var->i = 0;
	var->j = 0;
	var->k = 0;
	var->dir = 0;
	var->error = 0;

	return (var);
}

static char		**stock_args(int argc, char **argv, char **files)
{
	t_var	*var;

	if (!(var = (t_var *)malloc(sizeof(t_var))))
		return (NULL);
	var = init_vars(var, argc);
	while (var->i < argc && argc > 1)
	{
		if (argv[var->i][0] != '-' && ft_strcmp(argv[var->i], "./ft_ls") != 0 &&
			is_directory(argv[var->i]) == TRUE)
			var->tmp[var->j++] = argv[var->i];
		else if (lstat(argv[var->i], &var->s) == -1 && argv[var->i][0] != '-')
			var->error++;
		var->i++;
	}
	if (argc == 1)
		var->tmp[var->j++] = argv[var->i];
	if (var->j == 0 && ft_strcmp(files[0], ".") == 0 && var->error == 0)
		var->tmp[var->j++] = ".";
	var->tmp[var->j] = NULL;
	bubble_sort(var->tmp);
	return (var->tmp);
}

static char		**stock_files(int argc, char **argv)
{
	t_var	*var;

	if (!(var = (t_var *)malloc(sizeof(t_var))))
		return (NULL);
	var = init_vars(var, argc);
	while (var->i < argc && argc > 1)
	{
		if (argv[var->i][0] != '-' && ft_strcmp(argv[var->i], "./ft_ls") != 0
			&& is_directory(argv[var->i]) != TRUE &&
			lstat(argv[var->i], &var->s) != -1)
			var->tmp[var->j++] = argv[var->i];
		if (is_directory(argv[var->i]) == TRUE)
			var->dir = 1;
		if (var->j > 0 || (var->j == 0 && var->dir == 1))
		{
			if ((lstat(argv[var->i], &var->s) == -1 &&
				ft_strcmp(argv[var->i], "./ft_ls") != 0) ||
					(argv[var->i][0] == '-'))
				var->error_tab[var->k++] = argv[var->i];
		}
		else
			if (lstat(argv[var->i], &var->s) == -1 && argv[var->i][0] != '-' &&
				ft_strcmp(argv[var->i], "./ft_ls") != 0)
				var->error_tab[var->k++] = argv[var->i];
		var->i++;
	}
	var->error_tab[var->k] = NULL;
	bubble_sort(var->error_tab);
	var->k = 0;
	while (var->error_tab[var->k])
		set_perror(var->error_tab[var->k++]);
	if (argc == 1)
		var->tmp[var->j++] = argv[var->i];
	if (var->j == 0)
		var->tmp[var->j++] = ".";
	var->tmp[var->j] = NULL;
	free(var->error_tab);
	bubble_sort(var->tmp);
	return (var->tmp);
}

int			main(int argc, char **argv)
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
	if (opts->t == TRUE)
		args = timer(args);
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
		if (opts->a == FALSE)
		{
			if (opts->almost == TRUE)
				files = almost_all(files);
			else
				files = counter_a(files);
		}
		if (opts->t == TRUE)
			files = timer(files);
		if (opts->r == TRUE)
			files = do_reverse(files);
		if (opts->l == TRUE && opts->m != TRUE && opts->one != TRUE)
			do_l(files, path, opts);
		while (files[i])
		{
			if (opts->m == TRUE)
				do_m(files, files[i], i);
			else if (opts->l == FALSE || opts->one == TRUE)
				ft_putendl(files[i]);
			i++;
		}
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
		bubble_sort(tab);
		//tab = real_sort(tab);
/*		if (ft_strcmp(path, "/dev/") == 0)
			bubble_sort(tab);
*/		if (opts->a != TRUE)
		{
			if (opts->almost == TRUE)
				tab = almost_all(tab);
			else
				tab = counter_a(tab);
		}
		if (opts->t == TRUE)
			tab = timer(tab);
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
		j++;
	}
	free(var);
	return (0);
}
