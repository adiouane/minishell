/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 23:30:17 by omanar            #+#    #+#             */
/*   Updated: 2022/09/01 06:01:55 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_ambiguous(char **new, int *i, int start)
{
	char	**tmp;

	tmp = ft_split(*new, ' ');
	if (argslen(tmp) == 2)
	{
		free(*new);
		*new = ft_strdup(tmp[0]);
		free_loop(tmp);
	}
	else if (*new == NULL || argslen(tmp) != 2)
	{
		g_data.cmd->error = 2;
		*i = start - 1;
		if (tmp)
			free_loop(tmp);
		free(*new);
		return (1);
	}
	return (0);
}

char	*parse_dollar_redirection(char *str, int *i, int quote)
{
	int		start;
	char	*new;

	start = *i + 1;
	g_data.dollar = 1;
	if (str[start] == '?')
	{
		new = ft_itoa(g_data.exit_status);
		(*i)++;
	}
	else if ((str[start] == '"' || str[start] == '\'') && !quote)
		return (NULL);
	else if (is_separator(str[start]) || !is_acceptable(str[start]))
		new = ft_strdup("$");
	else
	{
		while (str[*i] && is_acceptable(str[++(*i)]))
			;
		new = new_value(str, (*i)--, start);
	}
	if (is_ambiguous(&new, i, start))
		return (ft_strdup("$"));
	return (new);
}

char	*handle_spaces_redirection(char *value, char **new)
{
	int		i;
	char	*tmp;
	char	**strs;

	strs = ft_split(value, ' ');
	i = 0;
	*new = advanced_join(*new, strs[i++]);
	tmp = *new;
	while (strs[i])
		g_data.cmd->args = advanced_add(g_data.cmd->args, strs[i++]);
	*new = ft_calloc(1, sizeof(char));
	free(value);
	free_loop(strs);
	return (tmp);
}

char	*parse_redirection(char *str)
{
	int		i;
	char	*new;
	char	*tmp;

	i = -1;
	new = ft_calloc(1, sizeof(char));
	while (str[++i])
	{
		if (str[i] == '"')
			tmp = parse_dquote(str, &i);
		else if (str[i] == '\'')
			tmp = parse_squote(str, &i);
		else if (str[i] == '$')
			tmp = parse_dollar_redirection(str, &i, 0);
		else
			tmp = ft_substr(str, i, 1);
		new = advanced_join(new, tmp);
		free(tmp);
	}
	return (new);
}

int	token_error2(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token->value[0] == '\0' || token->value[0] == '\n')
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token->value, 2);
	ft_putstr_fd("'\n", 2);
	g_data.exit_status = 258;
	ft_lstadd_back(&(g_data.cmds), ft_lstnew((void *)g_data.cmd));
	return (1);
}
