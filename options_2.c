/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 19:41:45 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/09/19 21:11:58 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
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
/*
//////////////////////POTENTIAL -e/////////////////////////

	if (((acl = acl_get_file(str, ACL_TYPE_EXTENDED)) != NULL))
	{
		ft_putendl(str);
		ft_putstr(acl_to_text(acl, (ssize_t *)str));
	}
*/
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

static char		*uid_gid(struct stat *s)
{
	struct passwd	*pwd_uid;
	struct group	*pwd_gid;
	char			*tmp;

	pwd_uid = getpwuid(s->st_uid);
	pwd_gid = getgrgid(s->st_gid);
	tmp = ft_strjoin(pwd_uid->pw_name, "  ");
	tmp = ft_strjoin(tmp, pwd_gid->gr_name);
	return(tmp);
}

static void		total_block(char **tab, char *path)
{
	struct stat s;
	char		*tmp;
	t_opts		opts;
	int			total;
	int			i;

	i = 0;
	total = 0;
	while (tab[i])
	{
		tmp = ft_strjoin(path, tab[i]);
		lstat(tmp, &s);
		if (opts.a == FALSE)
		{
			while (tab[i][0] == '.')
				i++;
		}
		total += s.st_blocks;
		i++;
	}
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

void			do_l(char **tab, char *path)
{
	struct stat	s;
	char		**tmp;
	char		*str;
	int			i;
	ssize_t		ret;
	char		*ptr;

	i = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * (tablen(tab) + 1))))
		return ;
	if (!(ptr = (char *)malloc(sizeof(char) * 255)))
		return ;
	total_block(tab, path);
	while (tab[i])
	{
		str = ft_strjoin(path, tab[i]);
		if (lstat(str, &s) == -1)
	{
		perror(RED"ERROR LSTAT ");
		exit(EXIT_FAILURE);
	}
		tmp[i] = catch_rights(&s, ft_strjoin(path, tab[i]));
		ft_putstr(tmp[i]);
		ft_putchar(' ');
		ft_putnbr(s.st_nlink);
		ft_putchar(' ');
		ft_putstr(uid_gid(&s));
		ft_putchar(' ');
		if (!(major(s.st_rdev) && minor(s.st_rdev)))
			ft_putnbr(s.st_size);
		else
		{
			ft_putnbr(major(s.st_rdev));
			ft_putstr(", ");
			ft_putnbr(minor(s.st_rdev));
		}
		ft_putstr("  ");
		ft_putstr(get_date(&s));
		ft_putchar(' ');
		if ((ret = readlink(ft_strjoin(path, tab[i]), ptr, 255)) != -1)
		{
			ptr[ret] = '\0';
			ft_putstr(tab[i]);
			ft_putstr(" -> ");
			ft_putendl(ptr);
		}
		else
			ft_putendl(tab[i]);
		i++;
	}
	tmp[i] = NULL;
}
