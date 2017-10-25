/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:49:53 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/25 03:40:02 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		bubble_sort(char **tab)
{
	int		i;
	int		j;
	t_bool	permu;
	char	*tmp;

	i = 0;
	permu = TRUE;
	while (permu)
	{
		permu = FALSE;
		i++;
		j = 0;
		while (j < (tablen(tab) - i))
		{
			if (ft_strcmp(tab[j], tab[j + 1]) > 0)
			{
				permu = TRUE;
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
	}
}

void		insertion_sort(char **tab)
{
	int		i;
	int		j;
	char	*current;

	i = 1;
	while (i < tablen(tab))
	{
		current = tab[i];
		j = i;
		while (j > 0 && ft_strcmp(tab[j - 1], current) > 0)
		{
			tab[j] = tab[j - 1];
			j--;
		}
		tab[j] = current;
		i++;
	}
}

static int	init_count(t_sort *sort)
{
	int		i;
	
	i = 0;
	sort->nb_up = 0;
	sort->nb_low = 0;
	sort->nb_und = 0;
	sort->nb_bet = 0;
	sort->nb_aft = 0;
	sort->nb_last = 0;
	return (i);
}

t_sort		count_it(char **tab)
{
	int		i;
	t_sort	sort;

	i = init_count(&sort);
	while (tab[i])
	{
		if (tab[i][0] >= 33 && tab[i][0] <= 57)
			sort.nb_und++;
		else if (tab[i][0] >= 58 && tab[i][0] <= 64)
			sort.nb_bet++;
		else if (tab[i][0] >= 65 && tab[i][0] <= 90)
			sort.nb_up++;
		else if (tab[i][0] >= 91 && tab[i][0] <= 96)
			sort.nb_aft++;
		else if (tab[i][0] >= 97 && tab[i][0] <= 122)
			sort.nb_low++;
		else if (tab[i][0] >= 123 && tab[i][0] <= 126)
			sort.nb_last++;
		i++;
	}
	return (sort);
}

void		set_perror(char *filename)
{
	ft_putstr_fd("ls: ", 2);
	perror(filename);
}

int			tablen(char **tab)
{
	int i;
	
	i = 0;
	if (!(tab))
		return (0);
	while (tab[i])
		i++;
	return (i);
}

char		user_exec(struct stat *s, char c)
{
	if ((S_ISUID & s->st_mode) && (S_IXUSR & s->st_mode))
		c = 's';
	else if (S_ISUID & s->st_mode)
		c = 'S';
	else if (S_IXUSR & s->st_mode)
		c = 'x';
	else
		c = '-';
	return (c);
}
