#include <../includes/minishell.h>

void	git_dollar(char *str, t_env *env)
{
	int (check), (len);
	len = ft_strlen(str);
	check = 1;
	while (env && check)
	{
		if (ft_strncmp(str, env->key, len) == 0)
		{
			ft_putstr_fd(env->value,  STDOUT_FILENO);
			check = 0;
		}
		env = env->next;
	}
}

void	echo_print(char *str) // i have a problem with redirectin the out put of echo
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	if(str[0] == '"' && str[len - 1] == '"') // check how i should deal with one "
		ft_putstr_fd(str, STDOUT_FILENO);
	else
	{
		while(str[i])
		{
			if(str[i] == '\\')
				i++;
			ft_putchar_fd(str[i], STDOUT_FILENO);
			i++;
		}
	}
}