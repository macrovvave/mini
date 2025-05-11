#include <../includes/minishell.h>

void	check_n(char **buff, int *index, int *check)
{
	int (i),	(u);
	i = 1;
	while (buff[i])
	{
		if (buff[i][0] == '-')
		{
			if (buff[i][1] == 'n')
			{
				u = 1;
				while (buff[i][u] == 'n')
					u++;
				if (buff[i][u] && buff[i][u] != 'n')
				{
					*index = i;
					return ;
				}
				*check = 1;
			}
			else
				return ;
		}
		*index = i;
		i++;
	}
	return ;
}

void	ft_echo(t_data *data, t_env *env)
{
	int (i), (check), (u);
	i = 1;
	check = 0;
	check_n(data->cmd, &i, &check);
	while (data->cmd[i])
	{
		u = i + 1;
		if (data->cmd[i][0] == '$')
			git_dollar(data->cmd[i] + 1, env);
		else
			echo_print(data->cmd[i]);
		if (data->cmd[u])
			ft_putchar_fd(32, STDOUT_FILENO);
		i++;
	}
	if (!check) //  0-[echo] 1-[-n..]/[txt]
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ft_pwd(void)
{
	char	*path;

	if(!(path = getcwd(NULL, 0)))
	{
		//free memory
		clear_container();
		perror("pwd");
	}
	else
		ft_putstr_fd(path, STDOUT_FILENO);
	free(path);
	printf("\n");
}