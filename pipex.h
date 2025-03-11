#include <string.h>
#include <stdlib.h>
#include "../LibftDamaga/libft.h"
#include "../printf/ft_printf.h"

typedef struct s_pipexcmd
{
    char **cmds;
    struct s_pipexcmd *nextnode;
}t_pipexcmd;

