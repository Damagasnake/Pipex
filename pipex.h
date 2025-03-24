#ifndef PIPEX_H
# define PIPEX_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../LibftDamaga/libft.h"
# include "../printf/ft_printf.h"
# include <sys/uio.h>

typedef struct s_pipexcmd
{
    pid_t pid1;// pid from the 1º process
    pid_t pid2;// pid from the 2º process
    int tube[2];//pipe with 2 pos. 1 read fd 2. write fd 
    int infile; //fd for tje infile (open and read file)
    int outfile;//fd for the outfile (open and write file)
    char **cmds;// array for each cmd and their args
    int argc;//Nmb of args of our cmds
    int status;// checks if there is a cmd ex.
    struct s_pipexcmd *nextnode;//pointer to next node
}t_pipexcmd;

// Function prototypes
t_pipexcmd *parsing_arg_initialize();
t_pipexcmd *crea_comando(char *cmd);
t_pipexcmd *parsear_entrada(int argc, char **argv);
t_pipexcmd *parsing_arg(int argc, char **argv);
char *get_path(char **envp);
char *find_path(char *cmd, char **envp);
void ft_error(void);
void execute(t_pipexcmd *cmds, char **envp);
void execute_cmd(t_pipexcmd *cmd, char **envp);

#endif