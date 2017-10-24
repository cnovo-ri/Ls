/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_and_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:27:11 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/24 07:26:01 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*get_path(int argc, char *args)
{
	char		*tmp;

	if (argc != 1 && args[ft_strlen(args) - 1] != '/' &&
		is_directory(args) == TRUE)
		tmp = ft_strdup(ft_strjoin(args, "/"));
	else
		tmp = ft_strdup(args);
	if (ft_strcmp(args, "./ft_ls") == 0)
		tmp = ".";
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

char			**stock_args(int argc, char **argv, char **files)
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
	insertion_sort(var->tmp);
	return (var->tmp);
}

static void		stock_files_2(int argc, char **argv, t_var *var)
{
	while (var->i < argc && argc > 1)
	{
		if (argv[var->i][0] != '-' && ft_strcmp(argv[var->i], "./ft_ls") != 0
			&& is_directory(argv[var->i]) != TRUE &&
			lstat(argv[var->i], &var->s) != -1)
			var->tmp[var->j++] = argv[var->i];
		if (is_directory(argv[var->i]) == TRUE)
			var->dir = 1;
		if (var->j > 0 || (var->j == 0 && (var->dir == 1 || var->error_tab[0])))
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
}

char			**stock_files(int argc, char **argv, t_var *var)
{
	var = init_vars(var, argc);
	stock_files_2(argc, argv, var);
	var->error_tab[var->k] = NULL;
	insertion_sort(var->error_tab);
	var->k = 0;
	while (var->error_tab[var->k])
		set_perror(var->error_tab[var->k++]);
	if (var->j == 0 || argc == 1 || (argc == 1 && var->j == 1))
		var->tmp[var->j++] = ".";
	var->tmp[var->j] = NULL;
	insertion_sort(var->tmp);
	free(var->error_tab);
	return (var->tmp);
}
