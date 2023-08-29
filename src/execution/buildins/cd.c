/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:21:42 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/29 19:26:12 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	**update_envp2(int size, char **envp, char **tmp, t_data *g)
{
	char	**new_envp;

	new_envp = ft_malloc(&g->mem_list, sizeof(char *) * (size + 1));
	if (new_envp == NULL)
		return (NULL);
	size = -1;
	while (envp[++size])
	{
		if (!ft_strncmp(envp[size], "PWD=", ft_strlen("PWD=")))
		{
			new_envp[size] = ft_strjoin("PWD=", tmp[0], g);
			if (new_envp[size] == NULL)
				return (NULL);
		}
		else if (!ft_strncmp(envp[size], "OLDPWD=", ft_strlen("OLDPWD=")))
			new_envp[size] = ft_strjoin("OLD", tmp[1], g);
		else
		{
			new_envp[size] = ft_strdup(envp[size], g);
			if (new_envp[size] == NULL)
				return (NULL);
		}
	}
	new_envp[size] = NULL;
	return (new_envp);
}

static char	**update_envp(char	**envp, char *path, t_data *g)
{
	int		size;
	char	*tp;
	char	*tmp[2];

	size = -1;
	while (envp[++size])
	{
		if (!ft_strncmp(envp[size], "PWD=", ft_strlen("PWD=")))
		{
			tp = ft_strdup(envp[size], g);
			if (tp == NULL)
				return (NULL);
		}	
	}
	tmp[0] = path;
	tmp[1] = tp;
	return (update_envp2(size, envp, tmp, g));
}

void	bd_cd(t_exe *exe, int flag, t_data *g_data)
{
	char	cwd[1024];

	if (exe->cmd[1] == NULL)
		chdir(ms_getenv("HOME", g_data));
	else if (!ft_strncmp(exe->cmd[1], "-", 2))
		chdir(ms_getenv("OLDPWD", g_data));
	else if (chdir(exe->cmd[1]) == -1)
	{
		ft_printf("cd: %s: No such file or directory\n", exe->cmd[1]);
		g_exit_status = errno;
		if (flag)
			exit(g_exit_status);
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		g_data->envp = update_envp(g_data->envp, cwd, g_data);
	if (g_data->envp == NULL)
		g_exit_status = 1;
	else
		g_exit_status = 0;
	if (flag)
		exit(g_exit_status);
}
