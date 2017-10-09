#include "ls.h"

char			*get_date(struct stat *s)
{
	time_t	timestamp;
	char	*date;
	char	*final_date;

	if (!(final_date = ft_strnew(12)))
		return (NULL);
	time(&timestamp);
	date = ctime(&s->st_mtime);
	if (labs(timestamp - s->st_mtime) > 15552000)
	{
		ft_strncpy(final_date, &date[4], 7);
		ft_strncpy(&final_date[7], &date[19], 5);
	}
	else
		ft_strncpy(final_date, &date[4], 12);
	return (final_date);
}

void			do_m(char **tab, char *str, int i)
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
