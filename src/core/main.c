/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:07:32 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/21 16:17:32 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"

t_sh_state	g_sh;

static int	init_shell(char **env)
{
	if (!(g_sh.export_var = ms_shlvl(dup_tab(env))))
		return (MEMERR);
	if (!(g_sh.internal = ft_tabnew(0)))
		return (MEMERR);
	return (0);
}

static void		silence_ac_av(char ac, char **av)
{
	(void)ac;
	(void)av;
}

int				main(int ac, char **av, char **env)
{
	char	*line;
	int		ret;
	t_token	*tok;

	silence_ac_av(ac, av);
	if (init_shell(env))
		return (MEMERR);
	ht_init();
	ht_refreshall(get_env_value("PATH"));
	hstread(g_sh.export_var);
	while (42)
	{
		if (!(line = readline("$> ")))
			break;
		if ((*line) && (*line != '\n'))
		{
			tok = ft_tokenizer(line);
			if (tok) 
			{
				test_sh_parser(tok);
				free_token_lst(tok);
			}
		}
		else if (*line != '\n')
			write(STDOUT_FILENO, "\n", 1);
//		free(line);
	}
	hstaddfile(g_sh.export_var);
	ret = 1;
//	free(line);
//	write(1, "\n", 1);
	return (ret);
}
