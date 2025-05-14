/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:31:33 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/05/13 22:11:29 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

// Input redirection (<):
// Takes input from a file instead of the keyboard.
//---------------------------
// Output redirection (>):
// Writes output to a file instead of the terminal (overwrites file).
// ---------------------------
// Append redirection (>>):
// Appends output to the end of a file.
//------------------------
// Heredoc (<<):
// Feed multiline input directly to a command until a delimiter is reached.
// ******************************************************************************* 

int	builtin_check(char *cmd)
{
	char	**builtins;
	int		index;

	builtins = ft_split("echo env pwd cd export unset exit", ' ');
	index = 0;
	while(builtins[index])
	{
		if (ft_strcmp(cmd, builtins[index]) == 0)
		{
			builtins[0] = ft_free_array(builtins);
			return (1);
		}
		index++;
	}
	builtins[0] = ft_free_array(builtins);
	return (0);
}


void	ft_ceue(t_data *data, t_env *env)
{
	if(ft_strcmp(data->cmd[0], "cd") == 0)
		ft_cd(data, env);
	else if(ft_strcmp(data->cmd[0], "export") == 0)
		ft_export(data, &env);
	else if(ft_strcmp(data->cmd[0], "unset") == 0)
		ft_unset(data, &env);
	else if(ft_strcmp(data->cmd[0], "exit") == 0)
		ft_exit(data);
	else if(ft_strcmp(data->cmd[0], "echo") == 0)
		ft_echo(data, env);
	else if(ft_strcmp(data->cmd[0], "env") == 0)
		ft_env(env);
	else if(ft_strcmp(data->cmd[0], "pwd") == 0)
		ft_pwd();
}

void	cmd_hand(t_data *cmd, t_env *env)
{
	t_data *tmp;
	int	check;

	tmp = cmd;
	while (tmp)
	{
		if (cmd->files.infile || cmd->files.outfile)
			redirect(cmd);
		offs()->prev_fds[0] = -1;
		offs()->prev_fds[1] = -1;
		check = builtin_check(tmp->cmd[0]);
		if (check == 1)
			ft_ceue(tmp, env);
		else
			execute_pipeline(tmp, env);
		tmp = tmp->next;
	}
}
//######################################################################
//######################################################################

static char	*get_key(const char *env_str)
{
	size_t	len = 0;

	while (env_str[len] && env_str[len] != '=')
		len++;
	return (ft_strdup(env_str));
}

static char	*get_value(const char *env_str)
{
	const char	*equal_sign = ft_strchr(env_str, '=');

	if (!equal_sign)
		return (NULL);
	return (ft_strdup(equal_sign + 1));
}

t_env	*env_to_list(char **envp)
{
	t_env	*head = NULL;
	t_env	*node;
	t_env	*last = NULL;

	while (*envp)
	{
		node = safe_alloc(sizeof(t_env), 0);
		if (!node)
			return (NULL); // Add cleanup in real use

		node->key = get_key(*envp);
		node->value = get_value(*envp);
		node->next = NULL;

		if (!head)
			head = node;
		else
			last->next = node;
		last = node;
		envp++;
	}
	return (head);
}
//######################################################################
//######################################################################

void execute_commands(t_data *cmd, char **ev) //beggining
{
	// store the std out/in fds;
	// t_data *tmp;
	printf("############################## EXECUTION STARTED #################################\n");
	t_env	*env;
	// nackup 0 = dup(0);
    if (!cmd)
		return ;
	env = env_to_list(ev);
	cmd_hand(cmd, env);
	//reset
}