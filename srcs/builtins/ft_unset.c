/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:39:40 by omanar            #+#    #+#             */
/*   Updated: 2022/08/30 18:02:54 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_remove_element(char **env, int n)
{
	int		i;
	int		j;
	char	**new;

	i = -1;
	j = -1;
	new = (char **)malloc(sizeof(char *) * (argslen(env) - 1));
	while (env[++i])
		if (i != n)
			new[++j] = ft_strdup(env[i]);
	new[j + 1] = NULL;
	free_loop(env);
	return (new);
}

void	error_unset(char *name)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	g_data.exit_status = 1;
}

void	remove_env(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_data.env[++i])
	{
		tmp = get_variable_name(g_data.env[i]);
		if (!ft_strncmp(tmp, str, big_len(ft_strlen(tmp), ft_strlen(str))))
		{
			g_data.env = ft_remove_element(g_data.env, i--);
			free(tmp);
			break ;
		}
		free(tmp);
	}
}

void	remove_export(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_data.export[++i])
	{
		tmp = get_new_line(str, NULL);
		if (!ft_strncmp(g_data.export[i], tmp,
				big_len(get_index(g_data.export[i], '='),
					get_index(tmp, '='))))
		{
			g_data.export = ft_remove_element(g_data.export, i--);
			free(tmp);
			break ;
		}
		free(tmp);
	}
}

void	ft_unset(void)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ((t_cmd *)(g_data.cmds->content))->args;
	while (tmp[++i])
	{
		if (!tmp[i] || check_error(tmp[i]))
		{
			error_unset(tmp[i]);
			continue ;
		}
		remove_env(tmp[i]);
		remove_export(tmp[i]);
	}
}
