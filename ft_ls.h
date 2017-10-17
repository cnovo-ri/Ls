/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:48:26 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/17 05:16:10 by cnovo-ri         ###   ########.fr       */
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

typedef struct		s_var
{
	struct stat	s;
	char		**tmp;
	char		**error_tab;
	int			i;
	int			j;
	int			k;
	int			dir;
	int			error;
}					t_var;

typedef struct		s_long
{
	char		*str;
	char		*ptr;
	char		**tmp;
	int			i;
}					t_long;

typedef struct		s_timer
{
	struct stat	s;
	struct stat	s_2;
	char		*tmp;
	char		*tmp_2;
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
	t_bool			file_tab;
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

char				**stock_args(int argc, char **argv, char **files);
char				**stock_files(int argc, char **argv);
char				*get_path(int argc, char *args);
int					total_block(char **tab, char *path, t_opts *opts);
char				*uid_gid(struct stat *s);
char				*get_date(struct stat *s);
void				bubble_sort(char **tab);
void				str_swap(char **str, char **str2);
char				**almost_all(char **tab);
void				do_m(char **tab, char *str, int i);
void				do_l(char **tab, char *path, t_opts *opts);
char				**timer(char **tab, char *path);
int					dir_len(char *path);
int					tablen(char **tab);
t_sort				count_it(char **tab);
char				**real_sort(char **tab);
char				**stock_tabs(t_sort *sort, char **dot, char **up,
					char **low);
char				**stock_lower(char **tab);
char				**stock_upper(char **tab);
char				**stock_dot(char **tab);
char				**press_r(char **tab, int argc);
t_bool				is_directory(char *str);
char				**do_reverse(char **tab);
char				**counter_a(char **tab);
void				return_opts(t_opts *opts);
t_opts				*parsing(int argc, char **argv);
t_bool				catch_opts(char c, t_opts *opts);
char				**create_and_fill(DIR *directory, int len);
char				**stock_directory(char *path);
void				set_perror(char *filename);
char				user_exec(struct stat *s, char c);
char				*catch_right_2(struct stat *s, char *tmp, int i, char *str);
char				*catch_rights(struct stat *s, char *str);

#endif
