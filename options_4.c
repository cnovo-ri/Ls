/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:06:46 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/17 06:06:57 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			**press_r(char **args, int argc)
{
	int		i;
	int		k;
	char	**tmp;
	char	*real_path;

	i = 0;
	k = 0;
	while (args[i])
	{
		real_path = get_path(argc, args[i]);
		printf (PURPLE"real_path : %s\n"NORMAL, real_path);
		if (is_directory(real_path) == TRUE && args[i][0] != '.')
			tmp = stock_directory(real_path);
		i++;
	}
	return (tmp);
}
