/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:49:53 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/25 23:11:36 by cnovo-ri         ###   ########.fr       */
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

void		set_perror(char *filename)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	ft_putstr_fd("ls: ", 2);
	if (errno == EACCES)
	{
		i = ft_strlen(filename) - 1;
		while (filename[i] != '/')
			i--;
		tmp = ft_strsub(filename, i + 1, ft_strlen(filename) - 1);
		perror(tmp);
		free(tmp);
	}
	else
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
