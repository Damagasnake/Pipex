#include "pipex.h"

char *get_path(char **envp)
{
    int i;

    i = 0;
    while (ft_strncmp("PATH", *envp[i], 4))
    i++;
    return(envp[i] + 5);    
}

char *find_path(char *cmd, char **envp)
{
    char **paths;
    char *path;
    int i;
    char *part_path;

    i = 0;
    while (ft_strnstr(envp[i], "PATH", 4) == 0)
        i++;
    paths = ft_split(envp[i] + 5, ':');
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, cmd);
        free(part_path);
        if (access(path, F_OK) == 0)
            return (path);
        free(path);
        i++;
    }
    i = -1;
    while (paths[++i])
        free(paths[i]);
    free(paths);
    return (0);
}