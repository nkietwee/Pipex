/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:12:35 by nkietwee          #+#    #+#             */
/*   Updated: 2023/02/26 16:41:29 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_execve_cmd(char **path, char **cmd, char **env)
{
	int i;
	char *findpath = NULL;
	i = 0;
	while (path[i] != NULL) // keep path with cmd1
	{
		findpath = ft_strjoin(path[i], cmd[0]);
		if (access(findpath, F_OK) == 0) // if find == 0
		{
			if (execve(findpath, cmd, env) == -1)
			{
				ft_freefree(path);
				free(findpath);
				ft_freefree(cmd);
				exit(errno);
			}
		}
		// free(path[i]);
		free(findpath);
		i++;
	}
	if (path[i] == NULL) // case not found command
	{
		ft_error(6, NULL, cmd[0]);
		ft_freefree(path);
		ft_freefree(cmd);
		exit(127);
	}
	ft_freefree(path);
}

// void ft_execve_path(char **path, char **cmd, char **envp) // path don't use
void ft_execve_path(char **cmd, char **env) // path don't use
{
	int i;

	i = 0;
	// If you access ,program could free
	if (access(cmd[0], F_OK) == 0) // found
	{
		if (execve(cmd[0], cmd, env) == -1)
		{
			ft_freefree(cmd); // cannot execve
			exit(errno);
		}
	}
	else if (access(cmd[0] , F_OK) == -1) //protect
	{
		ft_error(4, NULL, cmd[0]);
		ft_freefree(cmd); // cannot access
		exit (127);
	}
}

void	ft_sleep(int n)
{
	int	i;

	i = 0;
	while (i < n)
		i++;
}

void ft_error(int mode,char *argv, char *cmd)
{
	if (mode == 1)
		ft_putstr_fd("plz check your argument" ,STDOUT_FILENO);
	else if (mode == 2)
		ft_putstr_fd("Cannot create pipe or check your capacity", STDOUT_FILENO);
	else if (mode == 3)
		ft_putstr_fd("Cannot create fork or check your capacity", STDOUT_FILENO);
	else if (mode == 4)
	{
		ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (mode == 5)
	{
		ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (mode == 6)
	{
		ft_putstr_fd("zsh: command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

void ft_freefree(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}