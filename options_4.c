/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:06:46 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/18 08:17:14 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			press_r(char **tab, int argc, char *path, t_opts *opts)
{
	int		i;
	char	**tmp;
	char	*str;
	char	*tmp_2;
	
	i = 0;
	tmp = NULL;
	tmp_2 = NULL;
	while (tab[i])
	{
		path = get_path(argc, path);
		if (opts->a == TRUE)
		{
			if (is_directory(ft_strjoin(path, tab[i])) == TRUE &&
				(ft_strcmp(tab[i], ".") != 0) && (ft_strcmp(tab[i], "..") != 0))
			{
				str = ft_strjoin(path, get_path(argc, tab[i]));
				printf(RED"tab[%d] : %s\n"NORMAL, i, tab[i]);
				printf("directory path : %s\n", str);
				tmp = stock_directory(str);
				bubble_sort(tmp);
				do_opts(opts, tmp, path);
				press_r(tmp, argc, str, opts);
			}
		}
		else
		{
			while (tab[i][0] == '.')
			{
				if (!(tab[i + 1]))
				{
					i++;
					return ;
				}
				i++;
			}
			if (is_directory(ft_strjoin(path, tab[i])) == TRUE)
			{
				str = ft_strjoin(path, get_path(argc, tab[i]));
				printf(PURPLE"tab[%d] : %s\n"NORMAL, i, tab[i]);
				printf("directory path : %s\n", str);
				tmp = stock_directory(str);
				bubble_sort(tmp);
				do_opts(opts, tmp, path);
				press_r(tmp, argc, str, opts);
			}
		}
		i++;
	}
	ft_putchar('\n');
	return ;
}
