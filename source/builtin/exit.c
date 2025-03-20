#include "../../include/minishell.h"

void	ft_exit(void)
{
	kill(getpid(), SIGTERM);
}
