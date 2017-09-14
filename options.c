/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:48:47 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/09/14 19:12:36 by cnovo-ri         ###   ########.fr       */
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

static void		str_swap(char **str, char **str2)

{
	char	*tmp;

	tmp = *str;
	*str = *str2;
	*str2 = tmp;
}

static void		timer_2(t_timer *tim, char **tab)
{
	while (tim->i < (tablen(tab) - tim->j))
	{
		lstat(tab[tim->i], &(tim->s));
		lstat(tab[tim->i + 1],  &(tim->s_2));
		if (tim->s.st_mtime > tim->s_2.st_mtime)
		{
			tim->permu = TRUE;
			str_swap(&tab[tim->i], &tab[tim->i + 1]);
		}
		if (tim->s.st_mtime == tim->s_2.st_mtime && tab[tim->i + 1] &&
			ft_strcmp(tab[tim->i],tab[tim->i + 1]) < 0)
		{
			tim->permu = TRUE;
			str_swap(&tab[tim->i], &tab[tim->i + 1]);
		}
		tim->i++;
	}
}

char			**timer(char **tab)
{
	t_timer		tim;
	
	tim.j = 0;
	tim.permu = TRUE;
	while (tim.permu)
	{
		tim.permu = FALSE;
		tim.j++;
		tim.i = 0;
		timer_2(&tim, tab);
	}
	tab = do_reverse(tab);
	return (tab);
}
