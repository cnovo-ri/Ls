#include "ft_ls.h"

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
