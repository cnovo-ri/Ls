/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:48:47 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/09/12 20:59:24 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char		**counter_a(char **tab)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * (tablen(tab) + 1))))
		return (NULL);
	while (tab[i])
	{
		if (tab[i][0] == '.')
			i++;
		else
		{
			tmp[j] = ft_strdup(tab[i]);
			i++;
			j++;
		}
	}
	tmp[j] = NULL;
	return (tmp);
}

char		**do_reverse(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (tab[j])
		j++;
	while (i < (j / 2))
	{
		tmp = tab[i];
		tab[i] = tab[j - i - 1];
		tab[j - i - 1] = tmp;
		i++;
	}
	return (tab);
}

char		**press_r(char **tab)
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

static void		str_swap(char **str, char **str2)
{
	char	*tmp;

	tmp = *str;
	*str = *str2;
	*str2 = tmp;
}
static void		class_timer(char **tab)
{
	struct stat	s;
	struct stat	s_2;
	int			i;

	i = 0;
	while (tab[i])
	{
		stat(tab[i], &s);
		stat(tab[i + 1],  &s_2);
		if (s.st_mtime == s_2.st_mtime)
		{
			if (tab[i + 1] && ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				str_swap(&tab[i], &tab[i + 1]);
				i = 0;
			}
		}
		//printf("tab[%d] : %s ----> TIME : %ld\n", i, tab[i], s.st_mtime);
		i++;
	}
}

void			timer(char **tab)
{
	struct stat	s;
	struct stat	s_2;
	int			i;

	i = 0;
	while (tab[i])
	{
		stat(tab[i], &s);
		stat(tab[i + 1],  &s_2);
		if (s.st_mtime > s_2.st_mtime)
		{
			str_swap(&tab[i], &tab[i + 1]);
			i = 0;
		}
		i++;
	}
	tab = do_reverse(tab);
	class_timer(tab);
}
