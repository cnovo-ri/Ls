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

char		**timer(char **tab)
{
	struct stat	s;
	long		*tmp;
	int			i;
//	long		stock_time;

	i = 0;
	//stock_time = 0;
	if (!(tmp = (long *)malloc(sizeof(long) * tablen(tab) + 1)))
		return (NULL);
	while (tab[i])
	{
		if (lstat(tab[i], &s) == -1)
		{
			perror(RED"stat ");
			return (NULL);
		}
		i++;

	//	tmp[i] = s.st_ctime;
		printf("tab[%d] : %s ---> st_ctime : %ld\n", i, tab[i], s.st_ctime);
	}
	return(tab);
}
