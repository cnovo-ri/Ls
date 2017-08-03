#include "ls.h"
#include "./libft/libft.h"

void		set_perror(char *filename)
{
	ft_putstr_fd("ls: ", 2);
	perror(filename);
}

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

char			**stock_dot(char **tab)
{
	int		i;
	int		j;
	char	**tmp;
	
	i = 0;
	j = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * j + 1)))
		return (NULL);
	while (tab[i])
	{
		if (tab[i][0] == '.')
		{
			tmp[j] = tab[i];
			j++;
		}
		i++;
	}
	free(tab);
	tmp[j] = NULL;
	return (tmp);
}

char			**stock_upper(char **tab)
{
	int		i;
	int		j;
	char	**tmp;
	
	i = 0;
	j = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * j + 1)))
		return (NULL);
	while (tab[i])
	{
		if (tab[i][0] >= 65 && tab[i][0] <= 90)
		{
			tmp[j] = tab[i];
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
	
	i = 0;
	j = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * j + 1)))
		return (NULL);
	while (tab[i])
	{
		if (tab[i][0] >= 97 && tab[i][0] <= 122)
		{
			tmp[j] = tab[i];
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

char			**stock_tabs(t_sort *sort, char **dot, char **upper, char **lower)
{
	char	**tmp;
	int		total;

	total = 0;
	ft_putendl("before malloc");
	if (!(tmp = (char **)malloc(sizeof(char *) * total + 1)))
		return (NULL);
	ft_putendl("after malloc");
	while (dot[sort->i])
	{
		tmp[total] = dot[sort->i];
		sort->i++;
		total++;
	}
	while (upper[sort->j])
	{
		tmp[total] = upper[sort->j];
		sort->j++;
		total++;
	}
	while (lower[sort->k])
	{
		tmp[total] = lower[sort->k];
		sort->k++;
		total++;
	}
	tmp[total] = NULL;
	return (tmp);
}

char			**real_sort(char **tab)
{
	char		**dot;
	char		**upper;
	char		**lower;
	t_sort		sort;

	sort.i = 0;
	sort.j = 0;
	sort.k = 0;
//	sort.total = 0;
//	sort = NULL;
//	ft_putendl("Is dot");
	dot = stock_dot(tab);
//	ft_putendl("Not dot");
	upper = stock_upper(tab);
//	ft_putendl("Not upper");
	lower = stock_lower(tab);
//	ft_putendl("Not lower");
	return (stock_tabs(&sort, dot, upper, lower));
}
