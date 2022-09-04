/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:00:01 by omanar            #+#    #+#             */
/*   Updated: 2022/08/31 21:36:48 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**advanced_add(char **strs, char *arg)
{
	char	**args;
	int		wlen;
	int		i;

	if (!strs[0] || !strs)
	{
		args = (char **)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(arg);
		args[1] = NULL;
		free_loop(strs);
		return (args);
	}
	wlen = argslen(strs);
	args = (char **)malloc(sizeof(char *) * (wlen + 1));
	i = -1;
	while (strs[++i])
		args[i] = ft_strdup(strs[i]);
	args[i] = ft_strdup(arg);
	args[i + 1] = NULL;
	free_loop(strs);
	return (args);
}

char	*advanced_join(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s2)
	{
		str = ft_strdup(s1);
		free(s1);
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*expand_dollar(char *str, char **env)
{
	int		i;
	int		len;
	int		slen;
	int		tlen;
	char	*tmp;

	i = -1;
	slen = ft_strlen(str);
	while (env[++i])
	{
		tmp = get_variable_name(env[i]);
		if (!tmp)
			return (NULL);
		tlen = ft_strlen(tmp);
		len = ((tlen >= slen) * tlen) + ((tlen < slen) * slen);
		if (ft_strncmp(tmp, str, len) == 0)
		{
			free(tmp);
			return (ft_strdup(env[i] + get_char_index(env[i], '=') + 1));
		}
		free(tmp);
	}
	return (NULL);
}

char	*handle_spaces(char *value, char **new)
{
	int		i;
	char	*tmp;
	char	**strs;

	strs = ft_split(value, ' ');
	if (!strs[0])
	{
		free_loop(strs);
		free(value);
		return (NULL);
	}
	i = 0;
	*new = advanced_join(*new, strs[i++]);
	g_data.cmd->args = advanced_add(g_data.cmd->args, *new);
	if (strs[i])
		while (strs[i + 1])
			g_data.cmd->args = advanced_add(g_data.cmd->args, strs[i++]);
	tmp = ft_strdup(strs[i]);
	free(*new);
	*new = ft_calloc(1, sizeof(char));
	free(value);
	free_loop(strs);
	return (tmp);
}
