/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:12:39 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/03 05:18:14 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char **path_find(char *envp[])
{
    int     i;
    char    **ch;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp("PATH=", envp[i], 5) == 0)
            break ;
        i++;
    }
    ch = ft_split(envp[i] + 5, ':');
    return (ch);
}

int	check_cmd(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", ft_strlen("cd"))
		|| !ft_strncmp(cmd, "pwd", ft_strlen("pwd"))
		|| !ft_strncmp(cmd, "export", ft_strlen("export"))	
		|| !ft_strncmp(cmd, "env", ft_strlen("env"))	
		|| !ft_strncmp(cmd, "exit", ft_strlen("exit"))
		|| !ft_strncmp(cmd, "echo", ft_strlen("echo"))	
		|| !ft_strncmp(cmd, "unset", ft_strlen("unset")))
		return (1);
	else
		return (0);
}

char	*find_path(char *cmd, t_data *g_data)
{
	char	**p_path;
	char	*tmp;
	char	*tmp_f;
	int		i;

	p_path = path_find(g_data->envp);
	i = -1;
	while (p_path[++i])
	{
		tmp = ft_strjoin("/", cmd);		
		tmp_f = ft_strjoin(p_path[i], tmp);
		if (!access(tmp_f, X_OK))
		{
			//free stuff
			return (tmp_f);
		}
	}
	printf("%s: command not found\n", cmd);
	return (NULL);
}

void    close_pipe(int *fd)
{
    close(fd[STDIN_FILENO]);
    close(fd[STDOUT_FILENO]);
}

void    dup_in_out(int *fd, int *fd_prev)
{
    dup2(fd_prev[0], STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
}
