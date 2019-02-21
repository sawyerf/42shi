/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 13:58:14 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/21 17:50:28 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h" //this should be resolved differently

static char **construct_env(t_cmd_tab *cmd, char opt, int count)
{
	char 	**new_env;
	int		start;

	new_env = g_sh.env;
	if (opt == 'i')
		new_env = NULL;
	start = g_optind;
	if (!(new_env = ft_tabdup(new_env)))
		return (NULL);
	while (start < count)
	{
		if (!(new_env = ms_csetenv(new_env, cmd->av[start])))
			return (NULL);
		start++;
	}
	return (new_env);
}

static int		spawn_new_env(char **args, char **new_env)
{
	t_cmd_tab 	new_cmd;
	char		*path;

	ft_bzero(&new_cmd, sizeof(t_cmd_tab));
	new_cmd.av = args;
	new_cmd.process_env = new_env;
	if (!(path = ms_varchr(new_env, "PATH")))
		path = get_env_value("PATH");
	if (ht_getvalue(path, &new_cmd) == MEMERR)
		return (MEMERR);
	if (!new_cmd.full_path)
	{
		exec_error(BIN_NOT_FOUND, new_cmd.av[0]);
		return (BIN_NOT_FOUND);
	}
	return (spawn_command(&new_cmd));
}

static char		env_parseopt(char **args)
{
	int		flag;
	char	opt;

	flag = 0;
	g_optind = 1;
	opt = 0;
	while ((flag = ft_getopt(args, "i")) != -1)
	{
		opt = (char)flag;
		if (opt == '?')
		{
			ft_printf("usage: env [-i] [NAME=VAR] .. [BIN]\n");
			break ;
		}
	}
	return (opt);
}

int				ft_env(t_cmd_tab *cmd)
{
	int			count;
	char		**new_env;
	char		opt;
	int			ret;

	ret = 0;
	if ((opt = env_parseopt(cmd->av)) == '?')
		return (0);
	count = g_optind;
	while ((cmd->av[count] != NULL) && (valid_env_var(cmd->av[count])))
		count++;
	if ((new_env = construct_env(cmd, opt, count)) == NULL)
		return (MEMERR);
	if (cmd->av[count] == NULL)
	{
		print_env_tab(new_env);
		free_tab(new_env);
	}
	else
		ret = spawn_new_env(cmd->av + count, new_env);
	return (ret);
}
