#include "ls.h"

/*
void		sort_insertion(char **tab)
{
	int		i;
	int		j;
	int		size;
	char	*current;

	i = 1;
	size = 0;
	while (tab[size])
		size++;
	while ( i < size)
	{
		current = tab[i];
		j = i;
		while (j > 0 && tab[j - 1] > current)
		{
			tab[j] = tab[j - 1];
			j--;
		}
		tab[j] = current;
		i++;
	}
}
*/
char			**stock_dot(char **tab)
{
	int		i;
	int		j;
	char	**tmp;
	t_sort	sort;

	i = 0;
	j = 0;
	sort = count_it(tab);
	if (!(tmp = (char **)malloc(sizeof(char *) * (sort.nb_dot + 1))))
		return (NULL);
	while (tab[i])
	{
		if (tab[i][0] == '.')
		{
			tmp[j] = ft_strdup(tab[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

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

char			**stock_tabs(t_sort *sort, char **dot, char **up, char **low)
{
	char	**tmp;
	
	if (!(tmp = (char **)malloc(sizeof(char *) * (sort->len_tab + 1))))
		return (NULL);
	while (dot[sort->i])
	{
		tmp[sort->total] = ft_strdup(dot[sort->i]);
		sort->i++;
		sort->total++;
	}
	while (up[sort->j])
	{
		tmp[sort->total] = ft_strdup(up[sort->j]);
		sort->j++;
		sort->total++;
	}
	while (low[sort->k])
	{
		tmp[sort->total] = ft_strdup(low[sort->k]);
		sort->k++;
		sort->total++;
	}
	tmp[sort->total] = NULL;
	return (tmp);
}

char			**real_sort(char **tab)
{
	char		**dot;
	char		**up;
	char		**low;
	t_sort		sort;

	sort.i = 0;
	sort.j = 0;
	sort.k = 0;
	sort.total = 0;
	sort.len_tab = tablen(tab);
	dot = stock_dot(tab);
	up = stock_upper(tab);
	low = stock_lower(tab);
	tab = stock_tabs(&sort, dot, up, low);
	return (tab);
}
