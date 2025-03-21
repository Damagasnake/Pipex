#include "pipex.h"

char *get_path(char **envp)
{
    int i;

    i = 0;
    while (ft_strncmp("PATH", *envp[i], 4))
    i++;
    return(envp[i] + 5);    
}

void    find_path(t_pipexcmd *cmd, char **envp)
    {
        char **paths;
        char *path;
        int i;
        char *pathdef;
        
        i = 0;
        while (ft_strnstr(envp[i], "PATH", 4) == 0)
            i++;
        paths = ft_split(envp[i] + 5, ':');
        if (!path)
            return (NULL);
    }