/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:47:06 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/15 21:44:19 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_bool		catch_opts(char c, t_opts *opts)
{
	if (ft_strchr("lRartmA1", c))
	{
		if ('l' == c)
			opts->l = TRUE;
		if ('R' == c)
			opts->recursive = TRUE;
		if ('a' == c)
			opts->a = TRUE;
		if ('r' == c)
			opts->r = TRUE;
		if ('t' == c)
			opts->t = TRUE;
		if ('m' == c)
			opts->m = TRUE;
		if ('A' == c)
			opts->almost = TRUE;
		if ('1' == c)
			opts->one = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

void		put_error(char c)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage : ls [-lRartmA1] [file ...]\n", 2);
	exit(EXIT_FAILURE);
}

t_opts		*parsing(int argc, char **argv)
{
	t_opts	*opts;
	int		i;
	int		j;

	i = 1;
	if (!(opts = (t_opts *)malloc(sizeof(t_opts))))
		return (NULL);
	while (i < argc && argv[i][0] == '-' && !ft_strnequ("-", argv[i], 2) &&
	!ft_strnequ("--", argv[i], 3))
	{
		j = 1;
		while (argv[i][j])
		{
			if (!(catch_opts(argv[i][j], opts)))
				put_error(argv[i][j]);
			j++;
		}
		i++;
	}
	return_opts(opts);
	if (i < argc && ft_strnequ("--", argv[i], 3))
		i++;
	return (opts);
}

void		return_opts(t_opts *opts)
{
	if (opts->l == TRUE)
		ft_putendl(RED"l");
	if (opts->recursive == TRUE)
		ft_putendl(BLUE"R");
	if (opts->a == TRUE)
		ft_putendl(GREEN"a");
	if (opts->r == TRUE)
		ft_putendl(YELLOW"r");
	if (opts->t == TRUE)
		ft_putendl(CYAN"t");
	if (opts->m == TRUE)
		ft_putendl(PURPLE"m");
	if (opts->almost == TRUE)
		ft_putendl(CYAN"A");
	if (opts->one == TRUE)
		ft_putendl(GREY"1");
}
