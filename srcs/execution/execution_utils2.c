/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:16:26 by adiouane          #+#    #+#             */
/*   Updated: 2022/09/01 15:57:58 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	failed_fork(void)
{
	ft_putstr_fd("minishell: ", 2);
	perror("fork");
	g_data.exit_status = 1;
}

void	waiting(int i, pid_t pid)
{
	int	status;

	i = 0;
	while (i < g_data.cmds_size)
	{
		waitpid(pid, &status, 0);
		if (pid != -1)
		{
			if (WIFEXITED(status))
				g_data.exit_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				g_data.exit_status = 128 + WTERMSIG(status);
		}
		while (wait(NULL) != -1)
			;
		i++;
	}
	signal_init();
}

void	next_cmd(int last_fd)
{
	t_list	*tmp;

	close(g_data.p[1]);
	tmp = g_data.cmds;
	g_data.cmds = g_data.cmds->next;
	ft_lstdelone(tmp, &free_cmd);
	if (last_fd != -1)
		close(last_fd);
}

void	redirect_input(void)
{
	if (((t_cmd *)(g_data.cmds->content))->input != 0)
	{
		dup2(((t_cmd *)(g_data.cmds->content))->input, 0);
		close(((t_cmd *)(g_data.cmds->content))->input);
	}
}

void	redirect_output(void)
{
	if (((t_cmd *)(g_data.cmds->content))->output != 1)
	{
		dup2(((t_cmd *)(g_data.cmds->content))->output, 1);
		close(((t_cmd *)(g_data.cmds->content))->output);
	}
}
