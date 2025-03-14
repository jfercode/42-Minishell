#include "../../include/minishell.h"



void ft_exit()
{
    kill(getpid(),SIGTERM);
}