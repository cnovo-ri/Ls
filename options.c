/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:48:47 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/20 02:24:27 by cnovo-ri         ###   ########.fr       */
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

void		str_swap(char **str, char **str2)
{
	char	*tmp;

	tmp = *str;
	*str = *str2;
	*str2 = tmp;
}
/*
char		**timer(char **tab, char *path)
{
	t_timer		tim;
	char		*current;

	tim.i = 1;
	while (tim.i < tablen(tab))
	{
		tim.tmp = is_directory(tab[tim.i]) ? tab[tim.i] :
			ft_strjoin(path, tab[tim.i]);
		tim.tmp_2 = is_directory(tab[tim.i]) ? tab[tim.j - 1] :
			ft_strjoin(path, tab[tim.j - 1]);
		lstat(tim.tmp, &(tim.s));
		lstat(tim.tmp_2, &(tim.s_2));
		current = tab[tim.i];
		tim.j = tim.i;
		while (tim.j > 0 && tim.s_2.st_mtime > tim.s.st_mtime)
		{
			tab[tim.j] = tab[tim.j - 1];
			tim.j--;
		}
		tab[tim.j] = current;
		tim.i++;
	}
	tab = do_reverse(tab);
	return (tab);
}
*/
static void	timer_2(t_timer *tim, char **tab, char *path)
{
	while (tim->j < (tablen(tab) - tim->i))
	{
		tim->tmp = is_directory(tab[tim->j]) ? tab[tim->j] :
			ft_strjoin(path, tab[tim->j]);
		tim->tmp_2 = is_directory(tab[tim->j]) ? tab[tim->j + 1] :
			ft_strjoin(path, tab[tim->j + 1]);
		lstat(tim->tmp, &(tim->s));
		lstat(tim->tmp_2, &(tim->s_2));
		if (tim->s.st_mtime > tim->s_2.st_mtime)
		{
			tim->permu = TRUE;
			str_swap(&tab[tim->j], &tab[tim->j + 1]);
		}
		if (tim->s.st_mtime == tim->s_2.st_mtime && tim->tmp_2 &&
			ft_strcmp(tim->tmp, tim->tmp_2) < 0)
		{
			tim->permu = TRUE;
			str_swap(&tab[tim->j], &tab[tim->j + 1]);
		}
		tim->j++;
	}
}

char		**timer(char **tab, char *path)
{
	t_timer	tim;

	tim.i = 0;
	tim.permu = TRUE;
	while (tim.permu)
	{
		tim.permu = FALSE;
		tim.i++;
		tim.j = 0;
		timer_2(&tim, tab, path);
	}
	tab = do_reverse(tab);
	return (tab);
}
