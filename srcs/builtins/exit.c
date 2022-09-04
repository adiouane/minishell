/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 23:27:50 by omanar            #+#    #+#             */
/*   Updated: 2022/09/04 16:10:30 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	checker(char *av)
{
	int	j;

	if (ft_atoi(av) == 0)
		return (1);
	if (av[0] == 0)
		return (1);
	j = 0;
	if ((av[0] == '-' || av[0] == '+') && av[1])
		j++;
	while (av[j])
	{
		if ((av[j] < '0' || av[j] > '9'))
			return (1);
		j++;
	}
	return (0);
}

int	zero_checker(char *str)
{
	if (str[0] == '-' && str[1] == '0')
		return (0);
	else if (str[0] == '0')
		return (0);
	return (1);
}

void	is_numeric(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)g_data.cmds->content;
	if (zero_checker(cmd->args[1]) && checker(cmd->args[1]))
	{
		if (g_data.signalchild != 1)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_data.exit_status = 225;
		exit(g_data.exit_status);
	}
}

void	exit_cmd(void)
{
	int		len;
	t_cmd	*cmd;

	cmd = (t_cmd *)g_data.cmds->content;
	len = argslen(cmd->args);
	if (cmd->args[1] == NULL)
	{
		if (g_data.signalchild != 1)
			ft_putstr_fd("exit\n", 2);
		exit(g_data.exit_status);
	}
	is_numeric();
	if (len > 3)
	{
		if (g_data.signalchild != 1)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_data.exit_status = 1;
	}
	else if (len == 3)
	{
		ft_putstr_fd("exit\n", 1);
		exit(ft_atoi(cmd->args[1]));
	}
}
