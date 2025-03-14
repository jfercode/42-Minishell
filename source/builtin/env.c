#include "../../include/minishell.h"

extern char **environ;

void ft_env()
{
    int i;

    i = 0;
    while(environ[i])
    {
        printf("%s\n",environ[i]);
        i++;
    }
}

// int main() {
//     my_env();
//     return 0;
// }