/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:06:46 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/16 00:06:49 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
