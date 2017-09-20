#include "ls.h"

void		do_m(char **tab, char *str, int i)
{
	ft_putstr(str);
	if (tab[i + 1])
		ft_putstr(", ");
	else
		ft_putchar('\n');
}

char			**almost_all(char **tab)
{
	char	**tmp;
	int		i;
	int		j;

	i = 2;
	j = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * (tablen(tab) - 1))))
		return (NULL);
	while (tab[i])
	{
		tmp[j] = tab[i];
		i++;
		j++;
	}
	tmp[j] = NULL;
	return (tmp);
}

char			**press_r(char **tab, char *path)
{
	int		i;
	int		k;
	char	**tmp;
	char	*real_path;

	i = 0;
	k = 0;
	while (tab[i])
	{
		real_path = ft_strjoin(path, tab[i]);
		if (is_directory(real_path) == TRUE && tab[i][0] != '.')
			tmp = stock_directory(real_path);
		i++;
	}
	return (tmp);
}
