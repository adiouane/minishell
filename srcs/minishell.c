/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:34:41 by omanar            #+#    #+#             */
/*   Updated: 2022/07/26 15:28:50 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)av;
	if (ac != 1)
		return (0);
	while (42)
	{
		line = readline(GRN "➜ " CYN " minishell$ " RST);
		if (!line)
			continue ;
		add_history(line);
		parsing(line, env);
		// system("leaks -q minishell");
		printer();
		// clean();
		free(line);
	}
	return (0);
}
