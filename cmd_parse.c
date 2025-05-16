#include "pipex.h"

t_pipexcmd *parsing_arg_initialize()
{
    t_pipexcmd *head;

    head = malloc(sizeof(t_pipexcmd));
    if (!head)
        return NULL;
    head->nextnode = NULL;
    head->cmds = NULL;
    head->argc = 0;
    head->status = 0;
    return head;
}

t_pipexcmd *crea_comando(char *cmd)
{
    t_pipexcmd *new_cmd;

    new_cmd = malloc(sizeof(t_pipexcmd));
    if (!new_cmd)
        return NULL;
    new_cmd->nextnode = NULL;
    new_cmd->cmds = ft_split(cmd, ' ');
    if (!new_cmd->cmds)
    {
        free(new_cmd);
        return NULL;
    }
    // Contar argumentos
    int i = 0;
    while (new_cmd->cmds[i])
        i++;
    new_cmd->argc = i;
    new_cmd->status = 0;
    
    return new_cmd;
}

t_pipexcmd *parsear_entrada(int argc, char **argv)
{
    t_pipexcmd *head = NULL;
    t_pipexcmd *current = NULL;
    int i;
    
    // El primer comando es el archivo de entrada
    head = parsing_arg_initialize();
    if (!head)
        return NULL;

    head->cmds = malloc(sizeof(char*) * 3);
    if (!head->cmds)
    {
        free(head);
        return NULL;
    }
    head->cmds[0] = ft_strdup(argv[1]); // infile
    head->cmds[1] = ft_strdup(argv[argc - 1]); // outfile
    head->cmds[2] = NULL; // Add NULL termination
    head->argc = 2;
    head->status = 0;
    current = head;
    // Crear comandos
    i = 2;
    while (i < argc - 1)
    {
        t_pipexcmd *new_cmd = crea_comando(argv[i]);
        if (!new_cmd)
        {
            // Liberar memoria en caso de error
            t_pipexcmd *temp = head;
            while (temp)
            {
                t_pipexcmd *next = temp->nextnode;
                if (temp->cmds)
                {
                    int j = 0;
                    while (temp->cmds[j])
                        free(temp->cmds[j++]);
                    free(temp->cmds);
                }
                free(temp);
                temp = next;
            }
            return NULL;
        }
        current->nextnode = new_cmd;
        current = new_cmd;
        i++;
    }
    return head;
}

t_pipexcmd *parsing_arg(int argc, char **argv)
{
    return parsear_entrada(argc, argv);
}
