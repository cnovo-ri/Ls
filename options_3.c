#include "ls.h"

char			**press_r(char **tab)
{
	int		i;
	int		k;
	char	**tmp;
/*	char	**last;*/
	i = 0;
	k = 0;
	while (tab[i])
	{
		if (is_directory(tab[i]) == FALSE)
		{
			perror(RED"Error ");
			exit(EXIT_FAILURE);
		}
		if (is_directory(tab[i]) == TRUE && tab[i][0] != '.')
			tmp = stock_directory(tab[i]);
		i++;
	}
	return (tmp);
}
