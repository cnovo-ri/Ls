/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:06:46 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/19 05:45:54 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			press_r(char **tab, int argc, char *path, t_opts *opts)
{
	static int	flag = 0;
	int			i;
	char		**tmp;
	char		*str;
	char		*tmp_2;
	
	i = 0;
	tmp = NULL;
	tmp_2 = NULL;
	tab = real_sort(tab);
	if (flag == 0)
		do_opts(opts, tab, path);
	flag = 1;
	while (tab && tab[i])
	{
	//	printf("BEFORE get_path : directory path : %s\n", path);
		if (path[ft_strlen(path) - 1] != '/')
			path = get_path(argc, path);
/*		ft_putstr(YELLOW);
		ft_putendl(path);
		ft_putstr(NORMAL);
*/		if (opts->a == TRUE)
		{
			if (is_directory(ft_strjoin(path, tab[i])) == TRUE &&
				(ft_strcmp(tab[i], ".") != 0) && (ft_strcmp(tab[i], "..") != 0))
			{
				str = ft_strjoin(path, get_path(argc, tab[i]));
/*				printf(RED"tab[%d] : %s\n"NORMAL, i, tab[i]);
				printf("directory path : %s\n", str);
*/				tmp = stock_directory(str);
				if (tmp)
				{
					tmp = real_sort(tmp);
					do_opts(opts, tmp, path);
					press_r(tmp, argc, str, opts);
				}
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
	//			printf("BEFORE JOIN : directory path : %s\n", str);
				str = ft_strjoin(path, get_path(argc, tab[i]));
				ft_putchar('\n');
				if (str[ft_strlen(str) - 1] == '/')
					ft_putstr(ft_strsub(str, 0, ft_strlen(str) - 1));
				else
					ft_putstr(ft_strsub(str, 0, ft_strlen(str)));
				ft_putstr(":\n");
/*				printf(PURPLE"tab[%d] : %s\n"NORMAL, i, tab[i]);
				printf("directory path : %s\n", str);
*/				tmp = stock_directory(str);
				if (tmp)
				{
					tmp = real_sort(tmp);
					do_opts(opts, tmp, path);
	//				ft_putchar('\n');
					press_r(tmp, argc, str, opts);
				}
/*				else
					ft_putchar('\n');
*/			}
		}
		i++;
	}
	return ;
}
