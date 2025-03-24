#include "../../include/minishell.h"

int check_token(char *str)
{
    char *builtin_types[] = {"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};
    int i = 0;

    while (builtin_types[i] != NULL)
    {
        if (ft_strncmp(str, builtin_types[i], ft_strlen(builtin_types[i])) == 0)
            return i;
        i++;
    }
    return -1;
}

int ft_execve(t_ast *node)
{
    int token_checked;

    if (!node)
    {
        ft_putstr_fd("No token provided\n", 2);
        return 1;
    }

    token_checked = check_token(node->args[0]);
    printf("TOKEN CHECKED = %d\n",token_checked);
    if (token_checked >= 0)
    {
        // Es un builtin
        if (token_checked == 0)
            printf("CD");
            // ft_cd(node->args[1]);
        else if (token_checked == 1)
            printf("ECHO");
            //ft_echo(1,node->args);
        else if (token_checked == 2)
            printf("ENV");
            //ft_env();
        else if (token_checked == 3)
            ft_exit();
        else if (token_checked == 4)
            printf("EXPORT");
            //ft_export(node->args);
        else if (token_checked == 5)
            printf("PWD");
            //ft_pwd();
        else if (token_checked == 6)
            printf("UNSET");
            //ft_unset(node->args[1]);
    }
    else if (token_checked == -1)
    {
        // Es otro tipo de comando
        if (execve(node->args[0], node->args, NULL) == -1)
            ft_error_exit("execve");
        return 1;
    }
    else
    {
        ft_error_exit("Error checking token");
        return 1;
    }
    return 0;
}