/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidma2 <davidma2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:16:59 by davidma2          #+#    #+#             */
/*   Updated: 2025/05/20 11:06:16 by davidma2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipexcmd	*parsing_arg_initialize(void)
{
	t_pipexcmd	*head;

	head = malloc(sizeof(t_pipexcmd));
	if (!head)
		return (NULL);
	head->nextnode = NULL;
	head->cmds = NULL;
	head->argc = 0;
	head->status = 0;
	head->infile_path = NULL;
	head->outfile_path = NULL;
	return (head);
}

t_pipexcmd	*crea_comando(char *cmd)
{
	t_pipexcmd	*new_cmd;
	int			i;

	new_cmd = malloc(sizeof(t_pipexcmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->nextnode = NULL;
	new_cmd->cmds = ft_split(cmd, ' ');
	if (!new_cmd->cmds)
	{
		free(new_cmd);
		return (NULL);
	}
	i = 0;
	while (new_cmd->cmds[i])
		i++;
	new_cmd->argc = i;
	new_cmd->status = 0;
	return (new_cmd);
}

t_pipexcmd	*initialize_head(int argc, char **argv)
{
	t_pipexcmd	*head;

	head = parsing_arg_initialize();
	if (!head)
		return (NULL);
	head->cmds = malloc(sizeof(char *) * 3);
	if (!head->cmds)
	{
		free(head);
		return (NULL);
	}
	head->cmds[0] = ft_strdup(argv[1]);
	head->cmds[1] = ft_strdup(argv[argc - 1]);
	head->cmds[2] = NULL;
	head->argc = 2;
	head->status = 0;
	head->infile_path = ft_strdup(argv[1]);
	head->outfile_path = ft_strdup(argv[argc - 1]);
	return (head);
}

t_pipexcmd	*add_commands_to_list(int argc, char **argv, t_pipexcmd *head)
{
	t_pipexcmd	*current;
	t_pipexcmd	*new_cmd;
	int			i;

	current = head;
	i = 2;
	while (i < argc - 1)
	{
		new_cmd = crea_comando(argv[i]);
		if (!new_cmd)
		{
			free_commands(head);
			return (NULL);
		}
		current->nextnode = new_cmd;
		current = new_cmd;
		i++;
	}
	return (head);
}

t_pipexcmd	*parsear_entrada(int argc, char **argv)
{
	t_pipexcmd	*head;

	head = initialize_head(argc, argv);
	if (!head)
		return (NULL);
	head = add_commands_to_list(argc, argv, head);
	return (head);
}
