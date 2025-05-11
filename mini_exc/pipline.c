#include <../includes/minishell.h>

void	close_pipe(int *fds)
{
	if (fds[0] != -1)
		close(fds[0]);
	if (fds[1] != -1)
		close(fds[1]);
}

void	child_proc(t_data *cmd, int *prev, int *curr, t_env *env) //new
{
	if (prev[0] != -1)
		dup2(prev[0], STDIN_FILENO);
	if (cmd->next)
		dup2(curr[1], STDOUT_FILENO);
	close_pipe(prev);
	close_pipe(curr);
	execve(get_path(cmd->cmd[0]), cmd->cmd, env_to_array(env));
	err("execve");
}

void	parent_proc(int *prev, int *curr, t_data *next_cmd) // new
{
	close_pipe(prev);

	if (next_cmd)
	{
		prev[0] = curr[0];
		prev[1] = curr[1];
		close(curr[1]);
	}
	else
		close_pipe(curr);
}

void	execute_pipeline(t_data *cmd, t_env *env, int *prev)
{
	pid_t	pid;

	if (cmd->next && pipe(cmd->fds) == -1)
		err("pipe");
	pid = fork();
	if (pid == -1)
		err("fork");
	if (pid == 0)
		child_proc(cmd, prev, cmd->fds, env);
	else
	{
		waitpid(pid, &cmd->status, 0);
		parent_proc(prev, cmd->fds, cmd->next);
	}
}
