/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:21:42 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/07 12:52:54 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	**update_envp(char	**envp, char *path)
{
	char	**new_envp;
	int		size;
	char	*tmp;

	size = -1;
	while (envp[++size])
	{
		if (!ft_strncmp(envp[size], "PWD=", ft_strlen("PWD=")))
		{
			tmp = ft_strdup(envp[size]);
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
			new_envp[size] = ft_strjoin("PWD=", path);
			if (new_envp[size] == NULL)
			{
				// free 
				return (NULL);
			}
		}
		else if (!ft_strncmp(envp[size], "OLDPWD=", ft_strlen("OLDPWD=")))
			new_envp[size] = ft_strjoin("OLD", tmp);
		else
		{
			new_envp[size] = ft_strdup(envp[size]);
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

void	ft_cd(t_exe *exe, int flag)
{
	char	cwd[1024];

	if (exe->cmd[1] == NULL)
	{
		// invalid nbr arg error msg
		g_data.exit_status = 1;
		if (flag)
			exit(1);
		else
			return ;
	}
	if (chdir(exe->cmd[1]) == -1)
		g_data.exit_status = errno;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		g_data.envp = update_envp(g_data.envp, cwd);
	if (g_data.envp == NULL)
	{
		// do stuff
		g_data.exit_status = 1;
		if (flag)
			exit(1);
		else
			return ;
	}
	g_data.exit_status = 0;
	if (flag)
		exit(0);
}
