/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidma2 <davidma2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:05:28 by davidma2          #+#    #+#             */
/*   Updated: 2025/05/29 11:45:05 by davidma2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_commands(t_pipexcmd *cmds)
{
	t_pipexcmd	*current;
	t_pipexcmd	*next;
	int			i;

	current = cmds;
	while (current)
	{
		next = current->nextnode;
		if (current->cmds)
		{
			i = 0;
			while (current->cmds[i])
				free(current->cmds[i++]);
			free(current->cmds);
		}
		free(current->infile_path);
		free(current->outfile_path);
		free(current);
		current = next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipexcmd	*cmds;

	if (argc < 5)
	{
		ft_printf("Usage: ./pipex infile cmd1 cmd2 ... outfile\n");
		return (1);
	}
	cmds = parsear_entrada(argc, argv);
	if (!cmds)
	{
		ft_printf("Error parsing commands\n");
		return (1);
	}
	execute(cmds, envp);
	free_commands(cmds);
	return (0);
}
