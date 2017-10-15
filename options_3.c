/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:05:30 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/16 00:05:49 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

char			*uid_gid(struct stat *s)
{
	struct passwd	*pwd_uid;
	struct group	*pwd_gid;
	char			*tmp;

	pwd_gid = getgrgid(s->st_gid);
	if (!(pwd_uid = getpwuid(s->st_uid)))
		tmp = ft_strjoin((ft_itoa(s->st_uid)), "  ");
	else
		tmp = ft_strjoin(pwd_uid->pw_name, "  ");
	tmp = ft_strjoin(tmp, pwd_gid->gr_name);
	return (tmp);
}

int				total_block(char **tab, char *path, t_opts *opts)
{
	struct stat s;
	char		*tmp;
	int			total;
	int			i;

	i = 0;
	total = 0;
	while (tab[i])
	{
		tmp = ft_strjoin(path, tab[i]);
		lstat(tmp, &s);
		if (opts->a != TRUE)
		{
			while (tab[i][0] == '.')
				i++;
		}
		total += s.st_blocks;
		i++;
	}
	return (total);
}
