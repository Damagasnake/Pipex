#include "pipex.h"

char *get_path(char **envp)
{
    int i;

    i = 0;
    while (envp[i] && ft_strncmp("PATH=", envp[i], 5))
        i++;
    if (!envp[i])
        return (NULL);
    return(envp[i] + 5);     
}

char *find_path(char *cmd, char **envp)
{
    char **paths;
    char *path;
    int i;
    char *part_path;
    char *env_path;

    // Handle absolute path
    if (cmd[0] == '/' || cmd[0] == '.')
    {
        if (access(cmd, F_OK | X_OK) == 0)  
            return (ft_strdup(cmd));
        return (NULL);
    }
    // Use get_path to get the PATH value
    env_path = get_path(envp);
    if (!env_path)
        return (NULL);
    paths = ft_split(env_path, ':');
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        if (!part_path)
        {
            // Free all paths elements and the paths array
            int j;
            
            j = 0;
            while (paths[j])
                free(paths[j++]);
            free(paths);
            return (NULL);
        }
        path = ft_strjoin(part_path, cmd);
        free(part_path);
        if (!path)
        {
            // Free all paths elements and the paths array
            int j;
            
            j = 0;
            while (paths[j])
                free(paths[j++]);
            free(paths);
            return (NULL);
        }
        if (access(path, F_OK | X_OK) == 0)
        {
            // Free paths array before returning
            int j = 0;
            while (paths[j])
                free(paths[j++]);
            free(paths);
            return (path);
        }
        free(path);
        i++;
    }
    // Free paths array if no valid path was found
    i = 0;
    while (paths[i])
        free(paths[i++]);
    free(paths);
    return (NULL);
}

void ft_error(void)
{
    perror("\033[31mError");
    exit(EXIT_FAILURE);
}
