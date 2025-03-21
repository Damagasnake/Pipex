#include "pipex.h"

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

    // Aquí puedes agregar la lógica para ejecutar los comandos usando cmds y envp

    return (0);
}