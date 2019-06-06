#include "ft_eval.h"

int	exec_pipeline(t_ast_node *tree, t_job *job)
{
	t_cmd_tab	*cmd_tab;
	int			ret;

	ret = 0;
	if ((!job) && (!(job = make_job(1))))
		return (MEMERR);
	if ((!(job->cmd_ln))
			&& (!(job->cmd_ln = make_cmdline(tree->start, tree->end, 0))))
		return (MEMERR);
	if (!(cmd_tab = expand_pipeline(tree->pipeline)))
		return (MEMERR);
	if (cmd_tab->next)
		ret = eval_pipe(cmd_tab, job);
	else
		ret = launch_command(cmd_tab, job);
	if (WIFEXITED(job->status))
	{
		tree->exit_status = (int)WEXITSTATUS(job->status);
		del_job(job);
	}
	g_sh.status = tree->exit_status;
	free_cmd_tab_lst(cmd_tab);
	return (ret);
}
