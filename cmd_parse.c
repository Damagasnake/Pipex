#include "pipex.h"

t_pipexcmd *parsing_arg_initialize()
{
    t_pipexcmd *head;

    head = malloc(sizeof(t_pipexcmd));
    if (!head)
        return NULL;
    head->nextnode = NULL;
    return head;
}

t_pipexcmd *crea_comando(t_pipexcmd *current, char **argv, t_pipexcmd *head, int argc)
{
    t_pipexcmd *new_cmd;
    int k;

    new_cmd = malloc(sizeof(t_pipexcmd));
    if (!new_cmd)
        return NULL;
    new_cmd->nextnode = NULL;
    new_cmd->cmds = malloc(sizeof(char *) * (2 + 1));
    if (!new_cmd->cmds)
    {
        free(new_cmd);
        return NULL;
    }
    t_pipexcmd *parsed_entrada = parsear_entrada(argc, argv);
    if (parsed_entrada == NULL)
    {
        free(new_cmd->cmds);
        free(new_cmd);
        return NULL;
    }
    k = 0; 
    new_cmd->cmds[k] = ft_strdup(parsed_entrada->cmds[0]);
    if (!new_cmd->cmds[k])
    {
        while (--k >= 0)
            free(new_cmd->cmds[k]);
        free(new_cmd->cmds);
        free(parsed_entrada);
        free(new_cmd);
        return NULL;
    }
    new_cmd->cmds[2] = NULL;

    if (!current)
    {
        current = new_cmd;
        head = current;
    } else
    {
        current->nextnode = new_cmd;
        current = new_cmd;
    }
    return head;
}

t_pipexcmd *parsear_entrada(int argc, char **argv)
{
    t_pipexcmd *head = parsing_arg_initialize();
    int i = 2;
    int j = 2;

    while (i < argc - 1)
    {
        t_pipexcmd *current = head;
        while (j < argc - 1 && ft_strcmp(argv[j], "|") != 0)
        {
            i++;
            j++;
            t_pipexcmd *new_cmd = crea_comando(current, argv, head, argc);
            if (new_cmd == NULL) 
                return NULL;
        }
        i = j + 1;
    }
    return head;
}

t_pipexcmd *parsing_arg(int argc, char **argv)
{
    int i;

    i = 2;

    while ( i < argc - 1)
    {
        t_pipexcmd *new_cmd = crea_comando(NULL, argv, NULL, argc);
        if (new_cmd == NULL)
            return NULL;
    return parsear_entrada(argc, argv);
    }
}
