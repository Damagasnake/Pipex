#include "pipex.h"

void    execute(t_pipexcmd *cmds, char **envp)
{
    t_pipexcmd *current;
    int fd_prepipe;

    current = cmds;
    fd_prepipe = -1;// there is no previous pipe atm
    cmds->infile = open(cmds->cmds[0], O_RDONLY);
    if(cmds->infile == -1)
    ft_error();
    while (current)
    {
        if (current->nextnode)
        {
            if(pipe(current->tube) == -1)
                ft_error();
        }
        current->pid1 = fork();
        if(current->pid1 == -1)
            ft_error();
        
    }
}

