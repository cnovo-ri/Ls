#include "ls.h"

int			tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

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

char		**press_R(char **tab)
{
	int		i;
	int		k;
	char	**tmp;
//	char	**last;

	i = 0;
	k = 0;
	while (tab[i])
	{
		if (is_directory(tab[i]) == TRUE && tab[i][0] != '.')
			tmp = stock_directory(tab[i]);
		i++;
	}
	return(tmp);
}
