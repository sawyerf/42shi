/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:24:33 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/28 17:22:17 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		fg(t_cmd_tab *cmd)
{
	t_job *j;
	(void)cmd;

	if (!g_sh.job_lst)
	{
		ft_dprintf(STDERR_FILENO, "42sh: fg : no jobs running\n");
		return (0);
	}
	if ((!cmd->av[1]) && (g_sh.current_j))
		fg_job(g_sh.current_j, 1);
	else
	{
		j = jobs_conversion(cmd->av[1]);
		if (j)
			fg_job(j, 1);
		else
			ft_dprintf(STDERR_FILENO, "42sh: fg : '%s': no such job\n", cmd->av[1]);
	}
	return (0);
}
