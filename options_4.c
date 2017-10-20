/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:06:46 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/20 05:05:44 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		press_r_2(char *tab, int argc, char *path, t_opts *opts)
{
	char		**tmp;
	char		*str;

	str = ft_strjoin(path, get_path(argc, tab));
	ft_putchar('\n');
	if (str[ft_strlen(str) - 1] == '/')
		ft_putstr(ft_strsub(str, 0, ft_strlen(str) - 1));
	else
	{
		str = ft_strjoin(str, "/");
		ft_putstr(ft_strsub(str, 0, ft_strlen(str) - 1));
	}
	ft_putstr(":\n");
//	printf(RED"tab[%d] : %s\n"NORMAL, i, tab[i]);
//	printf("directory path : %s\n", str);
	tmp = stock_directory(str);
	if (tmp)
	{
		insertion_sort(tmp);
		do_opts(opts, tmp, str);
		press_r(tmp, argc, str, opts);
	}
}

static int		run_tab(char **tab, int i)
{
	while (tab[i][0] == '.')
	{
		if (!(tab[i + 1]))
		{
			i++;
			return (-1);
		}
		i++;
	}
	return (i);
}

static	int		fix_flag(int flag, char **tab, char *path, t_opts *opts)
{
	if (flag == 0)
		do_opts(opts, tab, path);
	return (flag);
}

static	void	press_r_3(char *tab, int argc, char *path, t_opts *opts)
{
	if (is_directory(ft_strjoin(path, tab)) == TRUE &&
		(ft_strcmp(tab, ".") != 0) && (ft_strcmp(tab, "..") != 0))
		press_r_2(tab, argc, path, opts);
}

void			press_r(char **tab, int argc, char *path, t_opts *opts)
{
	static int	flag = 0;
	int			i;

	i = 0;
	tab = real_sort(tab);
	flag = fix_flag(flag, tab, path, opts);
//	printf("path : %s\n", path);
	while (tab && tab[i])
	{
		if (flag == 0)
			path = ft_strjoin(path, "/");
		flag = 1;
		if (path[ft_strlen(path) - 1] != '/')
			path = get_path(argc, path);
		if (opts->a == TRUE)
			press_r_3(tab[i], argc, path, opts);
		else
		{
			if ((i = run_tab(tab, i)) == -1)
				return ;
			if (is_directory(ft_strjoin(path, tab[i])) == TRUE)
				press_r_2(tab[i], argc, path, opts);
		}
		i++;
	}
	return ;
}
