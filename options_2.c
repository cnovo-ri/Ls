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
		if (is_directory(tab[i]) == FALSE)
		{
			perror(RED"Error ");
			exit(EXIT_FAILURE);
		}
		if (is_directory(tab[i]) == TRUE && tab[i][0] != '.')
			tmp = stock_directory(tab[i]);
		i++;
	}
	return (tmp);
}

static char		*catch_rights_2(struct stat *s, char *tmp, int i)
{
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
	tmp[i] = '\0';
	return (tmp);
}


static char		*catch_rights(struct stat *s)
{
	char			*tmp;
	int				i;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * 11)))
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
	return (catch_rights_2(s, tmp, i));
}

char			**do_l(char **tab, char *path)
{
	struct stat	s;
	char		**tmp;
	char		*str;
	int			i;

	i = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * (tablen(tab) + 1))))
		return (NULL);
	while (tab[i])
	{
		str = ft_strjoin(path, tab[i]);
		if (lstat(str, &s) == -1)
	{
		perror(RED"ERROR LSTAT ");
		exit(EXIT_FAILURE);
	}
		tmp[i] = catch_rights(&s);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void		do_m(char **tab, char *str, int i)
{
	ft_putstr(str);
	if (tab[i + 1])
		ft_putstr(", ");
	else
		ft_putchar('\n');
}
