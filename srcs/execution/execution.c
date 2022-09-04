/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:54:55 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/30 17:19:03 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	piping(void)
{
	pipe(g_data.p);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	g_data.signalchild = 1;
}

void	run_execution(void)
{
	int		last_fd;
	int		i;

	last_fd = -1;
	i = 0;
	redirect_input();
	while (g_data.cmds)
	{
		piping();
		g_data.pid = fork();
		if (g_data.pid == -1)
		{
			failed_fork();
			break ;
		}
		if (g_data.pid == 0)
			ft_child_process((t_cmd *)g_data.cmds->content, i, last_fd);
		else
		{
			next_cmd(last_fd);
			last_fd = g_data.p[0];
			i++;
		}
	}
	waiting(i, g_data.pid);
}

void	execution(void)
{
	g_data.cmds_size = ft_lstsize(g_data.cmds);
	if (g_data.breaker == 1)
	{
		clean();
		return ;
	}
	g_data.tmpin = dup(0);
	g_data.tmpout = dup(1);
	if (!g_data.cmds->next && is_builtins())
		ft_builtins();
	else
		run_execution();
	g_data.signalchild = 0;
	dup2(g_data.tmpin, 0);
	dup2(g_data.tmpout, 1);
	close(g_data.tmpin);
	close(g_data.tmpout);
}
