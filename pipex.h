/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidma2 <davidma2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:18:14 by davidma2          #+#    #+#             */
/*   Updated: 2025/05/28 15:52:50 by davidma2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../LibftDamaga/libft.h"
# include "../ft_printf_davidma2/ft_printf.h"
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipexcmd
{
	pid_t				pid1;
	pid_t				pid2;
	int					tube[2];
	int					infile;
	int					outfile;
	char				*infile_path;
	char				*outfile_path;
	char				**cmds;
	int					argc;
	int					status;
	struct s_pipexcmd	*nextnode;
}						t_pipexcmd;

t_pipexcmd				*parsing_arg_initialize(void);
t_pipexcmd				*crea_comando(char *cmd);
t_pipexcmd				*parsear_entrada(int argc, char **argv);
t_pipexcmd				*parsing_arg(int argc, char **argv);
char					*get_path(char **envp);
char					*find_path(char *cmd, char **envp);
void					free_paths_array(char **paths);
char					*check_absolute_path(char *cmd);
char					*build_full_path(char *dir, char *cmd);
char					*search_in_paths(char **paths, char *cmd);
void					ft_error(void);
void					execute(t_pipexcmd *cmds, char **envp);
void					execute_cmd(t_pipexcmd *cmd, char **envp);
void					open_input_file(t_pipexcmd *cmds);
void					process_commands(t_pipexcmd *cmds, t_pipexcmd *current,
							int *fd_prepipe, char **envp);
void					create_pipe(t_pipexcmd *current);
void					child_process(t_pipexcmd *cmds, t_pipexcmd *current,
							int fd_prepipe, char **envp);
void					setup_input(t_pipexcmd *cmds, t_pipexcmd *current,
							int fd_prepipe);
void					setup_output(t_pipexcmd *cmds, t_pipexcmd *current);
void					parent_process(t_pipexcmd *current, int *fd_prepipe);
void					wait_for_processes(t_pipexcmd *cmds);
void					free_commands(t_pipexcmd *cmds);

#endif