/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:07:28 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/19 05:41:08 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		**between_ft(char **tab)
{
	int		i;
	int		j;
	char	**tmp;
	t_sort	sort;

	i = 0;
	j = 0;
	sort = count_it(tab);
	if (!(tmp = (char **)malloc(sizeof(char *) * (sort.nb_bet + 1))))
		return (NULL);
	while (tab[i])
	{
		if (tab[i][0] >= 58 && tab[i][0] <= 64)
		{
			tmp[j] = ft_strdup(tab[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

static char		**under_upper(char **tab)
{
	int		i;
	int		j;
	char	**tmp;
	t_sort	sort;

	i = 0;
	j = 0;
	sort = count_it(tab);
	if (!(tmp = (char **)malloc(sizeof(char *) * (sort.nb_und + 1))))
		return (NULL);
	while (tab[i])
	{
		if (tab[i][0] >= 33 && tab[i][0] <= 57)
		{
			tmp[j] = ft_strdup(tab[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

static char		**stock_tabs_2(t_sort *sort, char **tmp)
{
	while (sort->after[sort->l])
	{
		tmp[sort->total] = ft_strdup(sort->after[sort->l]);
		sort->l++;
		sort->total++;
	}
	while (sort->low[sort->m])
	{
		tmp[sort->total] = ft_strdup(sort->low[sort->m]);
		sort->m++;
		sort->total++;
	}
	while (sort->last[sort->n])
	{
		tmp[sort->total] = ft_strdup(sort->last[sort->n]);
		sort->n++;
		sort->total++;
	}
	tmp[sort->total] = NULL;
	return (tmp);
}

char			**stock_tabs(t_sort *sort)
{
	char	**tmp;

	if (!(tmp = (char **)malloc(sizeof(char *) * (sort->len_tab + 1))))
		return (NULL);
	while (sort->under[sort->i])
	{
		tmp[sort->total] = ft_strdup(sort->under[sort->i]);
		sort->i++;
		sort->total++;
	}
	while (sort->between[sort->j])
	{
		tmp[sort->total] = ft_strdup(sort->under[sort->j]);
		sort->j++;
		sort->total++;
	}
	while (sort->up[sort->k])
	{
		tmp[sort->total] = ft_strdup(sort->up[sort->k]);
		sort->k++;
		sort->total++;
	}
	return (stock_tabs_2(sort, tmp));
}

char			**real_sort(char **tab)
{
	t_sort		sort;

	sort.i = 0;
	sort.j = 0;
	sort.k = 0;
	sort.l = 0;
	sort.m = 0;
	sort.n = 0;
	sort.total = 0;
	sort.len_tab = tablen(tab);
	sort.under = under_upper(tab);
	sort.between = between_ft(tab);
	sort.up = stock_upper(tab);
	sort.after = after_upper(tab);
	sort.low = stock_lower(tab);
	sort.last = last_ft(tab);
	tab = stock_tabs(&sort);
	return (tab);
}
