#ifndef LS_H
# define LS_H

# include "./libft/libft.h"

typedef enum		e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef	struct		s_opts
{
	t_bool			l;
	t_bool			recursive;
	t_bool			a;
	t_bool			r;
	t_bool			t;
}					t_opts;

char				**press_R(char **tab);
t_bool				is_directory(char *str);
char				**do_reverse(char **tab);
char				**counter_a(char **tab);
void				return_opts(t_opts *opts);
t_opts				*parsing(int argc, char **argv);
t_bool				catch_opts(char c, t_opts *opts);
char				**create_and_fill(DIR *directory);
char				**stock_directory(char *path);

#endif
