/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidma2 <davidma2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:17:30 by davidma2          #+#    #+#             */
/*   Updated: 2025/05/20 10:31:51 by davidma2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_pipexcmd *cmds, t_pipexcmd *current, int fd_prepipe,
		char **envp)
{
	setup_input(cmds, current, fd_prepipe);
	setup_output(cmds, current);
	execute_cmd(current, envp);
}

void	parent_process(t_pipexcmd *current, int *fd_prepipe)
{
	if (*fd_prepipe != -1)
		close(*fd_prepipe);
	if (current->nextnode)
	{
		close(current->tube[1]);
		*fd_prepipe = current->tube[0];
	}
}

void	process_commands(t_pipexcmd *cmds, t_pipexcmd *current, int *fd_prepipe,
		char **envp)
{
	while (current)
	{
		create_pipe(current);
		current->pid1 = fork();
		if (current->pid1 == -1)
			ft_error();
		if (current->pid1 == 0)
			child_process(cmds, current, *fd_prepipe, envp);
		else
			parent_process(current, fd_prepipe);
		current = current->nextnode;
	}
}

void	wait_for_processes(t_pipexcmd *cmds)
{
	t_pipexcmd	*current;

	current = cmds;
	while (current)
	{
		if (current->pid1 > 0)
			waitpid(current->pid1, &current->status, 0);
		current = current->nextnode;
	}
}

void	execute(t_pipexcmd *cmds, char **envp)
{
	t_pipexcmd	*current;
	int			fd_prepipe;

	current = cmds->nextnode;
	fd_prepipe = -1;
	open_input_file(cmds);
	process_commands(cmds, current, &fd_prepipe, envp);
	wait_for_processes(cmds);
}

// void execute(char **argv, char ***envp)
// {
//     pid_t   pid1;
//     pid_t   pid2;
//     int     infile;
//     int     outfile;

//     int     pipefd[2];
//     pipe(pipefd);

//     infile = open(argv[1], O_RDONLY);
//     outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);

//     pid1 = fork();
//     if (pid1 < 0)
//         return (NULL);
//     if (pid1 == 0)
//     {
//         close(outfile);
//         close(pipefd[1]);
//         child_process(argv[2], envp, infile, pipefd[0]);
//     }
//     pid2 = fork();
//     if (pid2 < 0)
//         return (NULL);
//     if (pid2 == 0)
//     {
//         close(infile);
//         close(pipefd[0]);
//         child_process(argv[3], envp, outfile, pipefd[1]);
//     }
//     close (outfile);
//     close(infile);
//     close(pipefd[0]);
//     close(pipefd[1]);
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);
// }
