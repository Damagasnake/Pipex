#include "pipex.h"

void    execute_cmd(t_pipexcmd *cmd, char **envp)
{
    char *path;

    path = find_path(cmd->cmds[0], envp);
    if(!path)
    {
        ft_printf("Command not found %s\n", cmd->cmds[0]);
        exit(127);
    }
}