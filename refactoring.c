/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactoring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:49:31 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/13 01:14:29 by cnovo-ri         ###   ########.fr       */
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

static char		**stock_args(int argc, char **argv)
{
//	DIR		*dir;
	char	**tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * argc + 1)))
		return (NULL);
	while (i < argc && argc > 1)
	{
		if (argv[i][0] != '-' && ft_strcmp(argv[i], "./ft_ls") != 0 &&
			is_directory(argv[i]) == TRUE)
			tmp[j++] = argv[i];
		i++;
	}
	if (argc == 1)
		tmp[j++] = argv[i];
	if (argc > 1 && argv[i - 1][0] == '-')
		tmp[j++] = ".";
	/*	while (argv[k])
	{
		if (argc > 1 && argv[k][0] == '-')
		{
			if ((dir = opendir(argv[k])) == NULL)
				set_perror(argv[k]);
		}
		k++;
	}
*/	tmp[j] = NULL;
	bubble_sort(tmp);
	return (tmp);
}

static char		**stock_files(int argc, char **argv)
{
//	DIR		*dir;
	char	**tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * argc + 1)))
		return (NULL);
	while (i < argc && argc > 1)
	{
		if (argv[i][0] != '-' && ft_strcmp(argv[i], "./ft_ls") != 0 &&
			is_directory(argv[i]) != TRUE)
			tmp[j++] = argv[i];
		i++;
	}
	if (argc == 1)
		tmp[j++] = argv[i];
/*	if (argc > 1 && argv[i - 1][0] == '-')
		tmp[j++] = ".";
*/	/*	while (argv[k])
	{
		if (argc > 1 && argv[k][0] == '-')
		{
			if ((dir = opendir(argv[k])) == NULL)
				set_perror(argv[k]);
		}
		k++;
	}
*/	tmp[j] = NULL;
	bubble_sort(tmp);
	return (tmp);
}

int			main(int argc, char **argv)
{
	t_opts		*opts;
	char		**tab;
	char		*path;
	char		**args;
	char		**files;
	int			i;
	int			j;

	j = 0;
	opts = parsing(argc, argv);
	args = stock_args(argc, argv);
	files = stock_files(argc, argv);
//	printf(YELLOW"argc :%d\n"NORMAL, argc);
	if (opts->t == TRUE)
		args = timer(args);
	if (opts->r == TRUE)
		args = do_reverse(args);
	while (args[j])
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
	if (files)
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
	if (tablen(args) > 0 && tablen(files) > 0)
		ft_putchar('\n');
	opts->file_tab = FALSE;
	while (args[j])
	{
//			printf(GREEN"\n\nargvs :%s\n\nj :%d\n"NORMAL, args[j], j);
		i = 0;
		path = get_path(argc, args[j]);
		if (j >= 1)
			ft_putstr("\n");
		if (tablen(args) > 1 || (tablen(args) == 1 && tablen(files) > 0))
			ft_putstr(ft_strjoin(args[j],":\n"));
//		printf(GREEN"\npath :%s\n\n"NORMAL, path);
		tab = stock_directory(path);
		if (opts->recursive == TRUE)
			tab = press_r(tab, path);
		bubble_sort(tab);
		//tab = real_sort(tab);
/*		if (ft_strcmp(path, "/dev/") == 0)
			bubble_sort(tab);
*/		if (opts->a == FALSE)
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
	return (0);
}
