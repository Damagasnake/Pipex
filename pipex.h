#ifndef PIPEX_H
# define PIPEX_H
#include <string.h>
#include <stdlib.h>
#include "../LibftDamaga/libft.h"
#include "../printf/ft_printf.h"

typedef struct s_pipexcmd
{
    pid_t pid1;
    pid_t pid2;
    int tube[2];
    int infile;
    int outfile;
    char **cmds;
    
    struct s_pipexcmd *nextnode;
}t_pipexcmd;

#endif