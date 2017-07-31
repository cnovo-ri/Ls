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

char			**stock_tabs(t_sort *sort)
{
	while (sort->dot[sort->i])
	{
		sort->tmp[sort->total] = sort->dot[sort->i];
		sort->i++;
		sort->total++;
	}
	while (sort->upper[sort->j])
	{
		sort->tmp[sort->total] = sort->upper[sort->j];
		sort->j++;
		sort->total++;
	}
	while (sort->lower[sort->k])
	{
		sort->tmp[sort->total] = sort->lower[sort->k];
		sort->k++;
		sort->total++;
	}
	sort->tmp[sort->total] = NULL;
	return (sort->tmp);
}

char			**real_sort(char **tab)
{
	t_sort *sort;
	
	sort = NULL;
	ft_putendl("Is dot");
	sort->dot = stock_dot(tab);
	ft_putendl("Not dot");
	sort->upper = stock_upper(tab);
	ft_putendl("Not upper");
	sort->lower = stock_lower(tab);
	ft_putendl("Not lower");
	sort->i = 0;
	sort->j = 0;
	sort->k = 0;
	sort->total = 0;
	if (!(sort->tmp = (char **)malloc(sizeof(char *) * sort->total + 1)))
		return (NULL);
	return (stock_tabs(sort));
}
