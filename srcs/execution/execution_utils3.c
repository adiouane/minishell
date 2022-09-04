/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:16:47 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/31 00:36:39 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_getenv(char *str)
{
	int	i;

	i = 0;
	if (!g_data.env)
		return (NULL);
	while (g_data.env[i] != NULL)
	{
		if (ft_strncmp(g_data.env[i], str, ft_strlen(str)) == 0)
			return (g_data.env[i] + ft_strlen(str));
		i++;
	}
	return (NULL);
}

void	open_outputs(void)
{
	int	j;

	j = -1;
	while (((t_cmd *)(g_data.cmds->content))->outfiles[++j])
	{
		if (((t_cmd *)(g_data.cmds->content))->append[j])
			((t_cmd *)(g_data.cmds->content))->output
				= open(((t_cmd *)(g_data.cmds->content))->outfiles[j],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			((t_cmd *)(g_data.cmds->content))->output
				= open(((t_cmd *)(g_data.cmds->content))->outfiles[j],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (((t_cmd *)(g_data.cmds->content))->output == -1)
		{
			g_data.exit_status = 1;
			error_msg(((t_cmd *)(g_data.cmds->content))->outfiles[j], errno);
			g_data.stop = 1;
			return ;
		}
	}
}

void	ft_dup(int olfd, int nfd)
{
	dup2(olfd, nfd);
	close(olfd);
}

void	ft_child_process(t_cmd *cmd, int i, int last_fd)
{
	g_data.signalchild = 1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	open_outputs();
	if (g_data.stop == 1)
		exit(g_data.exit_status);
	close(g_data.p[0]);
	if (cmd->error)
		error_infile();
	if (i != g_data.cmds_size - 1)
		ft_dup(g_data.p[1], 1);
	if (((t_cmd *)(g_data.cmds->content))->output != 1)
		ft_dup(((t_cmd *)(g_data.cmds->content))->output, 1);
	if (last_fd != -1)
		ft_dup(last_fd, 0);
	if (((t_cmd *)(g_data.cmds->content))->input != 0)
		ft_dup(((t_cmd *)(g_data.cmds->content))->input, 0);
	if (!((t_cmd *)(g_data.cmds->content))->args[0])
		exit(EXIT_SUCCESS);
	run_cmd(cmd);
}
