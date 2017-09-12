/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 21:47:47 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/09/12 19:39:41 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

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
		perror(RED"Error ");
		return (-1);
	}
	while (readdir(len_dir))
		len++;
	if ((closedir(len_dir)) == -1)
	{
		perror(RED"error ");
		return (-1);
	}
	return (len);
}

char		**stock_directory(char *path)
{
	DIR		*directory;
	char	**tab;
	int		len;

	len = dir_len(path);
	if ((directory = opendir(path)) == NULL)
	{
		perror(RED"error ");
		return (NULL);
	}
	tab = create_and_fill(directory, len);
	if ((closedir(directory)) == -1)
	{
		perror(RED"error ");
		return (NULL);
	}
	return (tab);
}

t_bool		is_directory(char *str)
{
	struct stat		st;

	if (stat(str, &st) == 0)
		if (S_ISDIR(st.st_mode))
			return (TRUE);
	return (FALSE);
}
