/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 19:41:45 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/25 03:02:21 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_l3(struct stat *s)
{
	if (major(s->st_rdev) || minor(s->st_rdev))
	{
		ft_putnbr(major(s->st_rdev));
		ft_putstr(", ");
		ft_putnbr(minor(s->st_rdev));
	}
	else
		ft_putnbr(s->st_size);
}

static void		print_l2(struct stat *s, char *tab, char *path, char *ptr)
{
	ssize_t		ret;

	ft_putnbr(s->st_nlink);
	ft_putchar(' ');
	ft_putstr(ft_strjoin(uid_gid(s), " "));
	print_l3(s);
	ft_putstr(/*(ft_strjoin("  ",*/get_date(s));
	ft_putchar(' ');
	if ((ret = readlink(ft_strjoin(path, tab), ptr, 255)) != -1)
	{
		ptr[ret] = '\0';
		ft_putstr(ft_strjoin(tab, " -> "));
		ft_putendl(ptr);
	}
	else if ((ret = readlink(tab, ptr, 255) != -1))
	{
		ft_putstr(ft_strjoin(tab, " -> "));
		ft_putendl(ptr);
	}
	else
		ft_putendl(tab);
}

static void		print_l1(char **tab, char *path, t_opts *opts, struct stat *s)
{
	t_long	l;
	
	if (!(l.tmp = (char **)malloc(sizeof(char *) * (tablen(tab) + 1))))
		return ;
	if (!(l.ptr = (char *)malloc(sizeof(char) * 255)))
		return ;
	l.i = 0;
	while (tab[l.i])
	{
		l.str = ft_strjoin(path, tab[l.i]);
		if (lstat(l.str, s) == -1 && opts->file_tab == TRUE)
			l.str = tab[l.i];
		if (lstat(l.str, s) == -1)
			if (fstat(1, s) == -1 && ft_strcmp(path, "/dev/fd") == 0)
				set_perror(l.str);
		l.tmp[l.i] = catch_rights(s, ft_strjoin(path, tab[l.i]));
		ft_putstr(ft_strjoin(l.tmp[l.i], " "));
		print_l2(s, tab[l.i], path, l.ptr);
		l.i++;
	}
	free(l.tmp);
	free(l.ptr);
}

void			do_l(char **tab, char *path, t_opts *opts)
{
	struct stat	s;

	if (tab[0] && opts->file_tab != TRUE)
	{
		ft_putstr("total ");
		ft_putnbr(total_block(tab, path, opts));
		ft_putchar('\n');
	}
	print_l1(tab, path, opts, &s);
}
