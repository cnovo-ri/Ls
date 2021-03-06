/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscntrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 16:37:31 by cnovo-ri          #+#    #+#             */
/*   Updated: 2016/12/05 16:58:46 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_iscntrl(int c)
{
	if ((c >= 0 && c <= 31) || (c == 127))
		return (1);
	else
		return (0);
}
