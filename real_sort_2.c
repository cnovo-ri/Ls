/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_sort_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 05:34:53 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/19 05:38:00 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			**stock_upper(char **tab)
{
	int		i;
	int		j;
	char	**tmp;
	t_sort	sort;

	i = 0;
	j = 0;
	sort = count_it(tab);
	if (!(tmp = (char **)malloc(sizeof(char *) * (sort.nb_up + 1))))
		return (NULL);
	while (tab[i])
	{
		if (tab[i][0] >= 65 && tab[i][0] <= 90)
		{
			tmp[j] = ft_strdup(tab[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	bubble_sort(tmp);
	return (tmp);
}

char			**stock_lower(char **tab)
{
	int		i;
	int		j;
	char	**tmp;
	t_sort	sort;

	i = 0;
	j = 0;
	sort = count_it(tab);
	if (!(tmp = (char **)malloc(sizeof(char *) * (sort.nb_low + 1))))
		return (NULL);
	while (tab[i])
	{
		if (tab[i][0] >= 97 && tab[i][0] <= 122)
		{
			tmp[j] = ft_strdup(tab[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

char		**last_ft(char **tab)
{
	int		i;
	int		j;
		char	**tmp;
	t_sort	sort;

	i = 0;
	j = 0;
	sort = count_it(tab);
	if (!(tmp = (char **)malloc(sizeof(char *) * (sort.nb_last + 1))))
		return (NULL);
	while (tab[i])
	{
		if (tab[i][0] >= 123 && tab[i][0] <= 126)
		{
			tmp[j] = ft_strdup(tab[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

char		**after_upper(char **tab)
{
	int		i;
	int		j;
	char	**tmp;
	t_sort	sort;

	i = 0;
	j = 0;
	sort = count_it(tab);
	if (!(tmp = (char **)malloc(sizeof(char *) * (sort.nb_aft + 1))))
		return (NULL);
	while (tab[i])
	{
		if (tab[i][0] >= 91 && tab[i][0] <= 96)
		{
			tmp[j] = ft_strdup(tab[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}
