/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:27:22 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/01 15:59:49 by pabalons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	add_shlvl(char **envp)
{
	char	*tmp;
	int		lvl;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			lvl = ft_atoi(envp[i] + 6);
			free(envp[i]);
			tmp = ft_itoa(++lvl);
			if (!tmp)
				ft_error("Itoa failed in add_shlvl()");
			envp[i] = ft_strjoin("SHLVL=", tmp);
			if (!envp[i])
				ft_error("Join failed in add_shlvl()");
			free(tmp);
		}
		i++;
	}
}

static void	create_envp(t_data *data)
{
	char	*tmp_pwd;
	char	*tmp_cwd;

	data->envp = malloc(sizeof(char *) * 4);
	if (data->envp == NULL)
		ft_error("Envp creation failed");
	tmp_pwd = ft_strdup("PWD=");
	if (tmp_pwd == NULL)
		ft_error("Envp creation failed");
	tmp_cwd = getcwd(NULL, 0);
	if (tmp_cwd == NULL)
		ft_error("A");
	data->envp[0] = ft_strjoin(tmp_pwd, tmp_cwd);
	free(tmp_pwd);
	free(tmp_cwd);
	if (data->envp[0] == NULL)
		ft_error("Envp creation failed");
	data->envp[1] = ft_strdup("SHLVL= 1");
	if (data->envp[1] == NULL)
		ft_error("Envp creation failed");
	data->envp[2] = ft_strdup("_=]");
	if (data->envp[2] == NULL)
		ft_error("Envp creation failed");
	data->envp[3] = NULL;
}

void	copy_envp(t_data *data, char **envp)
{
	int	i;

	if (data->envp != NULL)
		free_matrix(data->envp);
	if (envp == NULL || envp[0] == NULL || envp[0][0] == '\0')
		create_envp(data);
	else
	{
		i = 0;
		while (envp[i])
			i++;
		data->envp = malloc((i + 1) * sizeof(char *));
		if (!data->envp)
			return ;
		i = 0;
		while (envp[i])
		{
			data->envp[i] = ft_strdup(envp[i]);
			if (!data->envp[i])
				return ;
			i++;
		}
		data->envp[i] = NULL;
		add_shlvl(data->envp);
	}
}
