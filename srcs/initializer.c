/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:55:31 by omanar            #+#    #+#             */
/*   Updated: 2022/08/09 15:32:09 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	creat_env(char **env)
{
	int		i;

	i = -1;
	g_data.env = (char **)malloc(sizeof(char *));
	g_data.env[0] = NULL;
	while (env[++i])
		g_data.env = advanced_add(g_data.env, env[i]);
}

void	cmd_init(void)
{
	g_data.cmd = (t_cmd *)malloc(sizeof(t_cmd));
	g_data.cmd->cmd = NULL;
	g_data.cmd->args = (char **)malloc(sizeof(char *));
	g_data.cmd->args[0] = NULL;
	g_data.cmd->input = 0;
	g_data.cmd->infile = NULL;
	g_data.cmd->output = 1;
	g_data.cmd->append = 0;
	g_data.cmd->error = 0;
	g_data.cmd->exit_status = 0;
	g_data.cmd->outfiles = (char **)malloc(sizeof(char *));
	g_data.cmd->outfiles[0] = NULL;
}

void	data_init(void)
{
	g_data.error = 0;
	g_data.exit_status = 0;
	cmd_init();
}
