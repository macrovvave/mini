#include <../includes/minishell.h>

//#############
//
//fds = [0][1] : [0] to read frpm | [1] to write into
//
//#############

void close_fds(int *fds, int check)
{
	if (fds[0] != -1)
		close(fds[0]);
	if (fds[1] != -1)
		close(fds[1]);
	if(check)
	{
		// fds[0] = -1;
		// fds[1] = -1;
	}
}

void	child_proc(t_data *cmd, t_env *env) //new
{
	
	if (offs()->prev_fds[0] != -1)
	{
		dup2(offs()->prev_fds[0], STDIN_FILENO);
		close_fds(offs()->prev_fds, 0);
	}
	if (cmd->next)
	{
		dup2(offs()->curr_fds[1], STDOUT_FILENO);
		close_fds(offs()->curr_fds, 0);
	}
	execve(get_path(cmd->cmd[0]), cmd->cmd, env_to_array(env));
	err("execve");
}

void	execute_pipeline(t_data *cmd, t_env *env)
{
	pid_t	pid;

	if (cmd->next && pipe(offs()->curr_fds) == -1)
		err("pipe");
	pid = fork();
	if (pid == -1)
		err("fork");
	else if (pid == 0)
		child_proc(cmd, env);
	else
	{
		waitpid(pid, &cmd->status, 0);
		close_fds(offs()->prev_fds, 1);
		if (cmd->next)
		{
			offs()->prev_fds[0] = offs()->curr_fds[0];
			offs()->prev_fds[1] = offs()->curr_fds[1];
			offs()->curr_fds[0] = -1;
			offs()->curr_fds[1] = -1;
		}
		// else
			// close_fds(offs()->curr_fds, 1);
	}
}
