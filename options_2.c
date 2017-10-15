/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 19:41:45 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/14 23:43:23 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/acl.h>

static char		*catch_rights_2(struct stat *s, char *tmp, int i, char *str)
{
	int		xattr;
	acl_t	acl;

	tmp[i] = ((S_ISGID & s->st_mode) && (S_IXGRP & s->st_mode)) ? 's' :
		(S_ISGID & s->st_mode) ? 'S' : (S_IXGRP & s->st_mode) ? 'x' : '-';
	i++;
	tmp[i] = (S_IROTH & s->st_mode) ? 'r' : '-';
	i++;
	tmp[i] = (S_IWOTH & s->st_mode) ? 'w' : '-';
	i++;
	tmp[i] = ((S_ISVTX & s->st_mode) && (S_IXOTH & s->st_mode)) ? 't' :
		(S_ISVTX & s->st_mode) ? 'T' : (S_IXOTH & s->st_mode) ? 'x' : '-';
	i++;
	tmp[i] = ((xattr = listxattr(str, NULL, 1, XATTR_NOFOLLOW)) > 0) ? '@' :
		((acl = acl_get_file(str, ACL_TYPE_EXTENDED)) != NULL &&
		(!(S_ISLNK(s->st_mode)))) ? '+' : ' ';
	i++;
	tmp[i] = '\0';
	return (tmp);
}

static char		*catch_rights(struct stat *s, char *str)
{
	char			*tmp;
	int				i;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * 12)))
		return (NULL);
	tmp[i] = (S_ISCHR(s->st_mode)) ? 'c' : (S_ISDIR(s->st_mode)) ? 'd':
		(S_ISBLK(s->st_mode)) ? 'b' : (S_ISFIFO(s->st_mode)) ? 'p' :
		(S_ISLNK(s->st_mode)) ? 'l' : (S_ISSOCK(s->st_mode)) ? 's' : '-';
	i++;
	tmp[i] = (S_IRUSR & s->st_mode) ? 'r' : '-';
	i++;
	tmp[i] = (S_IWUSR & s->st_mode) ? 'w' : '-';
	i++;
	tmp[i] = ((S_ISUID & s->st_mode) && (S_IXUSR & s->st_mode))  ? 's' :
		(S_ISUID & s->st_mode) ? 'S' : (S_IXUSR & s->st_mode) ? 'x' : '-';
	i++;
	tmp[i] = (S_IRGRP & s->st_mode) ? 'r' : '-';
	i++;
	tmp[i] = (S_IWGRP & s->st_mode) ? 'w' : '-';
	i++;
	return (catch_rights_2(s, tmp, i, str));
}

static void		print_l2(struct stat *s, char *tab, char *path, char *ptr)
{
	ssize_t		ret;

	ft_putnbr(s->st_nlink);
	ft_putchar(' ');
	ft_putstr(ft_strjoin(uid_gid(s), " "));
	if (major(s->st_rdev) || minor(s->st_rdev))
	{
		ft_putnbr(major(s->st_rdev));
		ft_putstr(", ");
		ft_putnbr(minor(s->st_rdev));
	}
	else
		ft_putnbr(s->st_size);
	ft_putstr(ft_strjoin("  ", get_date(s)));
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

static void			print_l1(char **tab, char *path, t_opts *opts,
		struct stat *s)
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
			if ((fstat(1, s) == -1) && ft_strcmp(path, "/dev/fd") == 0)
			{
				perror(RED"ERROR LSTAT ");
				exit(EXIT_FAILURE);
			}
		l.tmp[l.i] = catch_rights(s, ft_strjoin(path, tab[l.i]));
		ft_putstr(ft_strjoin(l.tmp[l.i], " "));
		print_l2(s, tab[l.i], path, l.ptr);
		l.i++;
	}
	free(l.tmp);
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
