#include "pipex.h"

void free_commands(t_pipexcmd *cmds)
{
    t_pipexcmd *current;
    t_pipexcmd *next;
    int i;

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
        free(current);
        current = next;
    }
}

int main(int argc, char **argv, char **envp)
{
    t_pipexcmd *cmds;

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
    // Clean up resources
    free_commands(cmds);
    return (0);
}
