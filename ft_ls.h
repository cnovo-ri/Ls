/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:48:26 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/09/14 20:30:22 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "./libft/libft.h"

typedef enum		e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef struct		s_timer
{
	struct stat	s;
	struct stat	s_2;
	int			i;
	int			j;
	t_bool		permu;
}					t_timer;

typedef	struct		s_opts
{
	t_bool			l;
	t_bool			recursive;
	t_bool			a;
	t_bool			r;
	t_bool			t;
	t_bool			m;
	t_bool			almost;
	t_bool			one;
}					t_opts;

typedef struct		s_sort
{
	int		len_tab;
	int		nb_dot;
	int		nb_up;
	int		nb_low;
	int		i;
	int		j;
	int		k;
	int		total;
}					t_sort;

int					total_block(char **tab, char *path);
char				*uid_gid(struct stat *s);
char				*get_date(struct stat *s);
void				bubble_sort(char **tab);
void				str_swap(char **str, char **str2);
char				**almost_all(char **tab);
void				do_m(char **tab, char *str, int i);
void				do_l(char **tab, char *path);
char				**timer(char **tab);
int					dir_len(char *path);
int					tablen(char **tab);
t_sort				count_it(char **tab);
char				**real_sort(char **tab);
char				**stock_tabs(t_sort *sort, char **dot, char **up,
					char **low);
char				**stock_lower(char **tab);
char				**stock_upper(char **tab);
char				**stock_dot(char **tab);
char				**press_r(char **tab, char *path);
t_bool				is_directory(char *str);
char				**do_reverse(char **tab);
char				**counter_a(char **tab);
void				return_opts(t_opts *opts);
t_opts				*parsing(int argc, char **argv);
t_bool				catch_opts(char c, t_opts *opts);
char				**create_and_fill(DIR *directory, int len);
char				**stock_directory(char *path);
void				set_perror(char *filename);

#endif
