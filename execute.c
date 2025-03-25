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
        if(current->pid1 == 0)
        {
            if(fd_prepipe != -1)
            {
                dup2(fd_prepipe,STDIN_FILENO);
                close(fd_prepipe);
            }
            else
            {
                dup2(cmds->infile,STDIN_FILENO);
                close(cmds->infile);
            }
            if(current->nextnode)
            {
                close(current->tube[0]);
                dup2(current->tube[1], STDOUT_FILENO);
                close(current->tube[1]);
            }
            else
            {
                cmds->outfile = open(cmds->cmds[1], O_RDONLY | O_CREAT | O_TRUNC, 0644);
                if(cmds->outfile == -1)
                    ft_error();
                dup2(cmds->outfile,STDOUT_FILENO);
                close(cmds->outfile);
            }
        }
        execute_cmd(current,envp);
        if(fd_prepipe != -1)
            close(fd_prepipe);
        if(current->nextnode)
            {
                close(current->tube[1]);
                fd_prepipe = current->tube[0];
            }
            current = current->nextnode;
}
