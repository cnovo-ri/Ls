/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 23:01:15 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/26 01:23:02 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/acl.h>

static char	group_exec(struct stat *s, char c)
{
	if ((S_ISGID & s->st_mode) && (S_IXGRP & s->st_mode))
		c = 's';
	else if (S_ISGID & s->st_mode)
		c = 'S';
	else if (S_IXGRP & s->st_mode)
		c = 'x';
	else
		c = '-';
	return (c);
}

static char	other_exec(struct stat *s, char c)
{
	if ((S_ISVTX & s->st_mode) && (S_IXOTH & s->st_mode))
		c = 't';
	else if (S_ISVTX & s->st_mode)
		c = 'T';
	else if (S_IXOTH & s->st_mode)
		c = 'x';
	else
		c = '-';
	return (c);
}

char		*catch_right_2(struct stat *s, char *tmp, int i, char *str)
{
	int		xattr;
	acl_t	acl;

	tmp[i] = group_exec(s, tmp[i]);
	i++;
	tmp[i] = (S_IROTH & s->st_mode) ? 'r' : '-';
	i++;
	tmp[i] = (S_IWOTH & s->st_mode) ? 'w' : '-';
	i++;
	tmp[i] = other_exec(s, tmp[i]);
	i++;
	if ((xattr = listxattr(str, NULL, 1, XATTR_NOFOLLOW)) > 0)
		tmp[i] = '@';
	else if ((acl = acl_get_file(str, ACL_TYPE_EXTENDED)) != NULL &&
		(!(S_ISLNK(s->st_mode))))
		tmp[i] = '+';
	else
		tmp[i] = ' ';
	i++;
	tmp[i] = '\0';
	return (tmp);
}

static char	first_right(struct stat *s, char c)
{
	if (S_ISCHR(s->st_mode))
		c = 'c';
	else if (S_ISDIR(s->st_mode))
		c = 'd';
	else if (S_ISBLK(s->st_mode))
		c = 'b';
	else if (S_ISFIFO(s->st_mode))
		c = 'p';
	else if (S_ISLNK(s->st_mode))
		c = 'l';
	else if (S_ISSOCK(s->st_mode))
		c = 's';
	else
		c = '-';
	return (c);
}

char		*catch_rights(struct stat *s, char *str)
{
	char			*tmp;
	int				i;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * 12)))
		return (NULL);
	tmp[i] = first_right(s, tmp[i]);
	i++;
	tmp[i] = (S_IRUSR & s->st_mode) ? 'r' : '-';
	i++;
	tmp[i] = (S_IWUSR & s->st_mode) ? 'w' : '-';
	i++;
	tmp[i] = user_exec(s, tmp[i]);
	i++;
	tmp[i] = (S_IRGRP & s->st_mode) ? 'r' : '-';
	i++;
	tmp[i] = (S_IWGRP & s->st_mode) ? 'w' : '-';
	i++;
	return (catch_right_2(s, tmp, i, str));
}
