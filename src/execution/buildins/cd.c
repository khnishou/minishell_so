/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:21:42 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/17 01:48:46 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	**update_envp(char	**envp, char *path, t_data *g_data)
{
	char	**new_envp;
	int		size;
	char	*tmp;

	size = -1;
	while (envp[++size])
	{
		if (!ft_strncmp(envp[size], "PWD=", ft_strlen("PWD=")))
		{
			tmp = ft_strdup(envp[size], g_data);
			if (tmp == NULL)
			{
				// free mat 
				return (NULL);
			}
		}	
	}
	new_envp = malloc(sizeof(char *) * (size + 1));
	if (new_envp == NULL)
		return (NULL);
	size = -1;
	while (envp[++size])
	{
		if (!ft_strncmp(envp[size], "PWD=", ft_strlen("PWD=")))
		{
			new_envp[size] = ft_strjoin("PWD=", path, g_data);
			if (new_envp[size] == NULL)
			{
				// free 
				return (NULL);
			}
		}
		else if (!ft_strncmp(envp[size], "OLDPWD=", ft_strlen("OLDPWD=")))
			new_envp[size] = ft_strjoin("OLD", tmp, g_data);
		else
		{
			new_envp[size] = ft_strdup(envp[size], g_data);
			if (new_envp[size] == NULL)
			{
				// free mat
				return (NULL);
			}
		}
	}
	new_envp[size] = NULL;
	return (new_envp);
}

void	ft_cd(t_exe *exe, int flag, t_data *g_data)
{
	char	cwd[1024];

	if (exe->cmd[1] == NULL)
	{
		// invalid nbr arg error msg
		// g_data.exit_status = 1;
		// if (flag)
		// 	exit(1);
		// else
		// 	return ;
		chdir(ms_getenv("HOME", g_data));
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			g_data->envp = update_envp(g_data->envp, cwd, g_data);
		exit_status = 0;
	}
	else if (chdir(exe->cmd[1]) == -1)
	{
		ft_printf("cd: %s: No such file or directory\n", exe->cmd[1]);
		exit_status = errno;
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			g_data->envp = update_envp(g_data->envp, cwd, g_data);
		if (g_data->envp == NULL)
		{
			// do stuff
			exit_status = 1;
			if (flag)
				exit(1);
			else
				return ;
		}
		exit_status = 0;
	}
	if (flag)
		exit(0);
}
