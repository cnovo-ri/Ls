/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:47:47 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/11 20:20:46 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		**create_and_fill(DIR *directory, int len)
{
	int				i;
	char			**tab;
	struct dirent	*ptr;

	i = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while ((ptr = readdir(directory)))
	{
		tab[i] = ft_strdup(ptr->d_name);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int			dir_len(char *path)
{
	DIR		*len_dir;
	int		len;

	len = 0;
	if ((len_dir = opendir(path)) == NULL)
	{
		perror(RED"Error opendir(len_dir)");
		exit(EXIT_FAILURE);
	}
	while (readdir(len_dir))
		len++;
	if ((closedir(len_dir)) == -1)
	{
		perror(RED"Error closedir(len_dir)");
		exit(EXIT_FAILURE);
	}
	return (len);
}

char		**stock_directory(char *path)
{
	DIR			*directory;
	char		**tab;
	int			len;

	len = dir_len(path);
	if ((directory = opendir(path)) == NULL)
	{
		perror(RED"error opendir(directory)");
		exit(EXIT_FAILURE);
	}
	tab = create_and_fill(directory, len);
	if ((closedir(directory)) == -1)
	{
		perror(RED"error closedir(directory)");
		exit(EXIT_FAILURE);
	}
	return (tab);
}

t_bool		is_directory(char *str)
{
	struct stat		st;

	if (lstat(str, &st) == 0)
		if (S_ISDIR(st.st_mode))
			return (TRUE);
	return (FALSE);
}
