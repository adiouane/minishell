/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:58:20 by omanar            #+#    #+#             */
/*   Updated: 2022/08/31 22:06:51 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_pipe(void)
{
	ft_lstadd_back(&g_data.cmds, ft_lstnew((void *)g_data.cmd));
	g_data.exit_status = 0;
	cmd_init();
}

int	token_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token->value[0] == '\0' || token->value[0] == '\n')
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token->value, 2);
	ft_putstr_fd("'\n", 2);
	g_data.exit_status = 258;
	ft_lstadd_back(&(g_data.cmds), ft_lstnew((void *)g_data.cmd));
	free_token(token);
	return (1);
}

int	tokens_handler(t_lexer *lexer)
{
	t_token	*token;

	token = lexer_next_token(lexer);
	if (token->e_type == TOKEN_PIPE)
		return (token_error(token));
	while (token->e_type != TOKEN_EOF && g_data.breaker == 0)
	{
		if (token->e_type == TOKEN_ERROR)
			return (token_error(token));
		else if (token->e_type == TOKEN_WORD)
			token_word(&token);
		else if (token->e_type == TOKEN_INFILE)
			token_infile(&lexer, &token);
		else if (token->e_type == TOKEN_OUT || token->e_type == TOKEN_APP)
			token_outfile(&lexer, &token, ++g_data.cmd->app_index);
		else if (token->e_type == TOKEN_HEREDOC)
			token_heredoc(&lexer, &token);
		else if (token->e_type == TOKEN_PIPE)
			token_pipe();
		free_token(token);
		token = lexer_next_token(lexer);
	}
	ft_lstadd_back(&(g_data.cmds), ft_lstnew((void *)g_data.cmd));
	free_token(token);
	return (0);
}
