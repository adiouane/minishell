/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:43:19 by omanar            #+#    #+#             */
/*   Updated: 2022/09/04 15:46:58 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*parse_star(char *str)
{
	int		j;
	char	*new;

	j = 0;
	while (str[j] == '*')
		j++;
	if (str[j] != '\0')
	{
		new = ft_strdup(str);
		free(str);
		return (new);
	}
	else
	{
		free(str);
		new = get_list();
	}
	return (new);
}

DIR	*addvanced_opendir(void)
{
	DIR		*dir;
	char	*path;

	path = getcwd(NULL, 0);
	dir = opendir(path);
	free(path);
	return (dir);
}

char	*get_list(void)
{
	int				i;
	char			*new;
	char			**tmp;
	DIR				*dir;
	struct dirent	*entry;

	dir = addvanced_opendir();
	tmp = ft_calloc(1, sizeof(char *));
	if (dir == NULL)
		return (NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			tmp = advanced_add(tmp, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	i = 0;
	if (tmp[i])
		while (tmp[i + 1])
			g_data.cmd->args = advanced_add(g_data.cmd->args, tmp[i++]);
	new = ft_strdup(tmp[i]);
	free_loop(tmp);
	return (new);
}
