#include "../include/minishell.h"

int check_token(char *str)
{
    char *builtin_types[] = {"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};
    int i = 0;

    while (builtin_types[i] != NULL)
    {
        if (ft_strncmp(str, builtin_types[i], ft_strlen(builtin_types[i])) == 0)
            return 1;
        i++;
    }
    return 0;
}

void ft_execve(t_ast *node)
{
    int token_checked;

    if (!node)
    {
        ft_putstr_fd("No token provided\n", 2);
        return;
    }

    token_checked = check_token(node->args[0]);
    if (token_checked == 1)
    {
        // Es un builtin
        if (ft_strcmp(node->args[0], "cd") == 0)
            ft_cd(node->args);
        // else if (ft_strcmp(node->args[0], "echo") == 0)
        //     ft_echo(node->args);
        else if (ft_strcmp(node->args[0], "env") == 0)
            ft_env(node->args);
        else if (ft_strcmp(node->args[0], "exit") == 0)
            ft_exit(node->args);
        else if (ft_strcmp(node->args[0], "export") == 0)
            ft_export(node->args);
        else if (ft_strcmp(node->args[0], "pwd") == 0)
            ft_pwd(node->args);
        else if (ft_strcmp(node->args[0], "unset") == 0)
            ft_unset(node->args);
    }
    else if (token_checked == 0)
    {
        // Es otro tipo de comando
        if (execve(node->args[0], node->args, NULL) == -1)
            ft_error_exit("execve");
    }
    else
        ft_error_exit("Error checking token");
}