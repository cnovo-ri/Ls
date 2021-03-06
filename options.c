/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:48:47 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/26 03:58:56 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

static void	timer_2(t_timer *tim, char **tab, char *path)
{
	tim->i = 0;
	tim->permu = TRUE;
	while (tim->permu)
	{
		tim->permu = FALSE;
		tim->i++;
		tim->j = 0;
		while (tim->j < (tablen(tab) - tim->i))
		{
			tim->tmp = ft_strjoin(path, tab[tim->j]);
			tim->tmp_2 = ft_strjoin(path, tab[tim->j + 1]);
			lstat(tim->tmp, &(tim->s));
			lstat(tim->tmp_2, &(tim->s_2));
			if (tim->s.st_mtime == tim->s_2.st_mtime && tim->tmp_2 &&
				ft_strcmp(tim->tmp, tim->tmp_2) < 0)
			{
				tim->permu = TRUE;
				str_swap(&tab[tim->j], &tab[tim->j + 1]);
			}
			tim->j++;
		}
	}
}

static void	do_lstat(t_timer *tim, char **tab, char *path)
{
	tim->tmp_2 = ft_strjoin(path, tab[tim->j - 1]);
	lstat(tim->tmp_2, &(tim->s_2));
}

char		**timer(char **tab, char *path)
{
	t_timer		tim;
	char		*current;

	tim.i = 1;
	while (tim.i < tablen(tab))
	{
		current = tab[tim.i];
		tim.j = tim.i;
		tim.tmp = ft_strjoin(path, current);
		lstat(tim.tmp, &(tim.s));
		do_lstat(&tim, tab, path);
		while (tim.j > 0 && tim.s_2.st_mtime > tim.s.st_mtime)
		{
			tab[tim.j] = tab[tim.j - 1];
			tim.j--;
			if (tim.j > 0)
				do_lstat(&tim, tab, path);
		}
		tab[tim.j] = current;
		tim.i++;
	}
	timer_2(&tim, tab, path);
	tab = do_reverse(tab);
	return (tab);
}
