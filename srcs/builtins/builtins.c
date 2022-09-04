/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 23:24:36 by adiouane          #+#    #+#             */
/*   Updated: 2022/09/01 06:09:00 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_builtins_in_child(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)g_data.cmds->content;
	if (!cmd->args[0])
		return ;
	redirect_input();
	open_outputs();
	if (g_data.stop == 1)
		return ;
	redirect_output();
	if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0)
		ft_env();
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
		cd();
	else if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
		ft_echo();
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
		exit_cmd();
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		ft_unset();
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
		ft_export();
	exit(0);
}

int	is_builtins_in_child(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)g_data.cmds->content;
	if (!cmd->args[0])
		return (0);
	if ((ft_strncmp(cmd->args[0], "pwd\0", 4) == 0)
		|| (ft_strncmp(cmd->args[0], "env\0", 4) == 0)
		|| (ft_strncmp(cmd->args[0], "cd\0", 4) == 0)
		|| (ft_strncmp(cmd->args[0], "echo\0", 5) == 0)
		|| (ft_strncmp(cmd->args[0], "exit\0", 5) == 0)
		|| (ft_strncmp(cmd->args[0], "unset\0", 6) == 0)
		|| (ft_strncmp(cmd->args[0], "export\0", 7) == 0))
		return (1);
	return (0);
}

int	stop(void)
{
	t_list	*tmp;

	open_outputs();
	if (g_data.stop == 1)
	{
		tmp = g_data.cmds;
		g_data.cmds = g_data.cmds->next;
		ft_lstdelone(tmp, &free_cmd);
		return (1);
	}
	if (((t_cmd *)g_data.cmds->content)->error)
	{
		error_infile();
		tmp = g_data.cmds;
		g_data.cmds = g_data.cmds->next;
		ft_lstdelone(tmp, &free_cmd);
		return (1);
	}
	return (0);
}

void	ft_builtins(void)
{
	t_list	*tmp;
	t_cmd	*cmd;

	cmd = (t_cmd *)g_data.cmds->content;
	redirect_input();
	if (stop())
		return ;
	redirect_output();
	if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0)
		ft_env();
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
		cd();
	else if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
		ft_echo();
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
		exit_cmd();
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		ft_unset();
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
		ft_export();
	tmp = g_data.cmds;
	g_data.cmds = g_data.cmds->next;
	ft_lstdelone(tmp, &free_cmd);
}

int	is_builtins(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)g_data.cmds->content;
	if (!cmd->args[0])
		return (0);
	if ((ft_strncmp(cmd->args[0], "pwd\0", 4) == 0)
		|| (ft_strncmp(cmd->args[0], "env\0", 4) == 0)
		|| (ft_strncmp(cmd->args[0], "cd\0", 4) == 0)
		|| (ft_strncmp(cmd->args[0], "echo\0", 5) == 0)
		|| (ft_strncmp(cmd->args[0], "exit\0", 5) == 0)
		|| (ft_strncmp(cmd->args[0], "unset\0", 6) == 0)
		|| (ft_strncmp(cmd->args[0], "export\0", 7) == 0))
		return (1);
	return (0);
}
