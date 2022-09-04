/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 23:27:17 by omanar            #+#    #+#             */
/*   Updated: 2022/08/31 23:27:20 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_pwd(char *newpwd, char *oldpwd)
{
	ft_set_env("PWD", newpwd);
	ft_set_export("PWD", newpwd, 1);
	ft_set_env("OLDPWD", oldpwd);
	ft_set_export("OLDPWD", oldpwd, 1);
}

void	*cd_only(char *path)
{
	path = ft_getenv("HOME=");
	if (path == NULL)
	{
		g_data.exit_status = 1;
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (NULL);
	}
	return (path);
}

void	getcwd_error(int err, char *path)
{
	char	*oldpwd;

	g_data.exit_status = 0;
	ft_putstr_fd("cd: error retrieving current directory: \
getcwd: cannot access parent directories: ", 2);
	ft_putendl_fd(strerror(err), 2);
	oldpwd = ft_getenv("PWD=");
	g_data.newpwd = ft_strjoin(oldpwd, "/");
	g_data.newpwd = advanced_join(g_data.newpwd, path);
}

void	change_dir(char *path, char *oldpwd)
{
	if (chdir(path) == -1 && path)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_data.exit_status = 1;
	}
	free(g_data.newpwd);
	g_data.newpwd = getcwd(NULL, 0);
	if (!g_data.newpwd)
		getcwd_error(errno, path);
	set_pwd(g_data.newpwd, oldpwd);
	free(oldpwd);
}

void	cd(void)
{
	char	*path;
	char	*oldpwd;

	path = NULL;
	oldpwd = getcwd(NULL, 0);
	if (((t_cmd *)(g_data.cmds->content))->args[1] == NULL)
		path = cd_only(path);
	else
	{
		path = ((t_cmd *)(g_data.cmds->content))->args[1];
		if (path[0] == '-' && path[1] == '\0')
		{
			path = ft_getenv("OLDPWD=");
			if (path == NULL)
			{
				g_data.exit_status = 1;
				ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
				return ;
			}
			ft_putendl_fd(path, 1);
		}
	}
	change_dir(path, oldpwd);
}
