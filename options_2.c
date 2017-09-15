/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 19:41:45 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/09/14 20:58:57 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char			**press_r(char **tab)
{
	int		i;
	int		k;
	char	**tmp;
/*	char	**last;*/
	i = 0;
	k = 0;
	while (tab[i])
	{
		if (is_directory(tab[i]) == TRUE && tab[i][0] != '.')
			tmp = stock_directory(tab[i]);
		i++;
	}
	return (tmp);
}

static char		*catch_rights(char *tab)
{
	struct stat		s;
	char			*tmp;
	int				i;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * 11)))
		return (NULL);
	lstat(tab, &s);
	tmp[i] = (S_ISCHR(s.st_mode)) ? 'c' : (S_ISDIR(s.st_mode)) ? 'd':
		(S_ISBLK(s.st_mode)) ? 'b' : (S_ISFIFO(s.st_mode)) ? 'p' :
		(S_ISLNK(s.st_mode)) ? 'l' : (S_ISSOCK(s.st_mode)) ? 's' : '-';
	i++;
	tmp[i] = (S_IRUSR & s.st_mode) ? 'r' : '-';
	i++;
	tmp[i] = (S_IWUSR & s.st_mode) ? 'w' : '-';
	i++;
	tmp[i] = (S_IXUSR & s.st_mode) ? 'x' : (S_ISUID & s.st_mode) ? 's' : '-';
	i++;
	tmp[i] = (S_IRGRP & s.st_mode) ? 'r' : '-';
	i++;
	tmp[i] = (S_IWGRP & s.st_mode) ? 'w' : '-';
	i++;
	tmp[i] = (S_IXGRP & s.st_mode) ? 'x' : (S_ISGID & s.st_mode) ? 's' : '-';
	i++;
	tmp[i] = (S_IROTH & s.st_mode) ? 'r' : '-';
	i++;
	tmp[i] = (S_IWOTH & s.st_mode) ? 'w' : '-';
	i++;
	tmp[i] = (S_IXOTH & s.st_mode) ? 'x' : (S_ISVTX & s.st_mode) ? 't' : '-';
	i++;
	tmp[i] = '\0';
	return (tmp);
}

char			**do_l(char **tab)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * (tablen(tab) + 1))))
		return (NULL);
	while (tab[i])
	{
		tmp[i] = catch_rights(tab[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}
